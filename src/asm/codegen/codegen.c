#include "codegen.h"
#include "../stack/stack.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void calcMaxRegs(OperationTreeNode *root, uint8_t *maxRegs) {
    if (!root) return;

    uint8_t count = 0;
    for (uint32_t i = 0; i < root->childCount; i++) {
        OperationTreeNode *child = root->children[i];
        if (child->type != NULL) {
            count++;
        }
    }

    if (count > *maxRegs) {
        *maxRegs = count;
    }

    for (uint32_t i = 0; i < root->childCount; i++) {
        calcMaxRegs(root->children[i], maxRegs);
    }
}

void prepareRegsAndTempsHelper(OperationTreeNode *root, StringStack *stack, bool stackOnly, bool debug) {
    if (strcmp(root->label, WRITE) == 0) {
        if (root->children[0]->childCount == 0) {
            root->children[0]->reg = strdup(REG_AR);
        } else {
            prepareRegsAndTempsHelper(root->children[0], stack, stackOnly, debug);
        }
        prepareRegsAndTempsHelper(root->children[1], stack, stackOnly, debug);
    } else if (strcmp(root->label, INDEX) == 0) {
        if (root->children[0]->childCount == 0) {
            root->children[0]->reg = strdup(REG_AR);
        } else {
            prepareRegsAndTempsHelper(root->children[0], stack, stackOnly, debug);
        }
        prepareRegsAndTempsHelper(root->children[1], stack, stackOnly, debug);
        pushStack(stack, root->children[1]->reg);
        if (stackOnly) {
           pushStack(stack, root->children[0]->reg);
           root->reg = strdup(root->children[0]->reg);
           root->isSpilled = true;
           root->offset = root->children[0]->offset + 8; 
        } else {
            root->reg = strdup(root->children[0]->reg);
        }        
        if (debug)
            printf("Index result in reg %s\n", root->reg);
    } else if (strcmp(root->label, OT_CALL) == 0) {
        uint8_t offset = 0;
        for (uint32_t i = 1; i < root->childCount; i++) {
            prepareRegsAndTempsHelper(root->children[i], stack, stackOnly, debug);
            if (stackOnly) {
                pushStack(stack, root->children[i]->reg);
                root->reg = root->children[i]->reg;
                root->children[i]->isSpilled = true;
                offset = offset + 8;
                root->children[i]->offset = offset; 
            } 
        }
        root->reg = strdup(REG_RT);
        if (debug)
            printf("Call result in reg %s\n", root->reg);
    } else if (strcmp(root->label, OP_PLUS) == 0 ||
                strcmp(root->label, OP_MINUS) == 0 ||
                strcmp(root->label, OP_DIV) == 0 ||
                strcmp(root->label, OP_MUL) == 0 ||
                strcmp(root->label, OP_MOD) == 0) {
        prepareRegsAndTempsHelper(root->children[0], stack, stackOnly, debug);
        prepareRegsAndTempsHelper(root->children[1], stack, stackOnly, debug);
        pushStack(stack, root->children[1]->reg);
        if (stackOnly) {
           pushStack(stack, root->children[0]->reg);
           root->reg = strdup(root->children[0]->reg);
           root->isSpilled = true;
           root->offset = root->children[0]->offset + 8; 
        } else {
            root->reg = strdup(root->children[0]->reg);
        }
        if (debug)
            printf("Binary operation '%s' result in reg %s\n", root->label, root->reg);
    }  else if (strcmp(root->label, OP_NOT) == 0 ||
                strcmp(root->label, OP_NEG) == 0) {
        prepareRegsAndTempsHelper(root->children[0], stack, stackOnly, debug);
        if (stackOnly) {
           pushStack(stack, root->children[0]->reg);
           root->reg = strdup(root->children[0]->reg);
           root->isSpilled = true;
           root->offset = root->children[0]->offset + 8; 
        } else {
            root->reg = strdup(root->children[0]->reg);
        }
        if (debug)
            printf("Unary operation '%s' result in reg %s\n", root->label, root->reg);
    } else if (strcmp(root->label, LIT_READ) == 0) {
        char *reg = popStack(stack);
        root->reg = strdup(reg);
        if (strcmp(root->children[1]->type->typeName, "string") == 0 ||
            strcmp(root->children[1]->type->typeName, "ulong") == 0 || 
            strcmp(root->children[1]->type->typeName, "long") == 0) {
                root->children[1]->reg = strdup(REG_AR);
        }
        //root->children[1]->reg = strdup(reg);
        if (debug)
            printf("Literal %s in reg %s\n", root->children[1]->label, reg);
        free(reg);
    } else if (strcmp(root->label, READ) == 0) {
        char *reg = popStack(stack);
        root->reg = strdup(reg);
        root->children[0]->reg = strdup(REG_AR);
        if (debug)
            printf("Var %s in reg %s\n", root->children[0]->label, reg);
        free(reg);
    }
}

void prepareRegsAndTemps(OperationTreeNode *root) {
    StringStack *stack = (StringStack *)malloc(sizeof(StringStack));
    initStack(stack);
    pushStack(stack, REG_R7);
    pushStack(stack, REG_R6);
    pushStack(stack, REG_R5);
    pushStack(stack, REG_R4);
    pushStack(stack, REG_R3);
    pushStack(stack, REG_R2);
    pushStack(stack, REG_R1);
    pushStack(stack, REG_R0);


    if (strcmp(root->label, DECLARE) == 0 && root->childCount == 3) {
        uint8_t maxRegs = 0;
        calcMaxRegs(root->children[2], &maxRegs);

        bool stackOnly = maxRegs > 8;
        prepareRegsAndTempsHelper(root->children[2], stack, stackOnly, true);
    } else if (strcmp(root->label, SEQ_DECLARE) == 0) {
        for (uint32_t i = 0; i < root->childCount; i++) {
            if (strcmp(root->label, DECLARE) == 0 && root->childCount == 3) {
                uint8_t maxRegs = 0;
                calcMaxRegs(root->children[i], &maxRegs);

                bool stackOnly = maxRegs > 8;
                prepareRegsAndTempsHelper(root->children[i], stack, stackOnly, true);
            } 
        }
    } else {
        uint8_t maxRegs = 0;
        calcMaxRegs(root, &maxRegs);

        bool stackOnly = maxRegs > 8;
        prepareRegsAndTempsHelper(root, stack, stackOnly, true);
    }
    

    freeStack(stack);
    free(stack);
}