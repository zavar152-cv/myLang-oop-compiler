#include "codegen.h"
#include "../stack/stack.h"
#include "../symbols.h"
#include <stdbool.h>
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
            char *reg = popStack(stack);
            root->children[0]->reg = reg;
            prepareRegsAndTempsHelper(root->children[0], stack, stackOnly, debug);
            free(reg);
        }
        prepareRegsAndTempsHelper(root->children[1], stack, stackOnly, debug);
    } else if (strcmp(root->label, INDEX) == 0 || strcmp(root->label, INDEXR) == 0) {
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
        StringStack *stackForCall = (StringStack *)malloc(sizeof(StringStack));
        initStack(stackForCall);
        // pushStack(stackForCall, REG_R7);
        // pushStack(stackForCall, REG_R6);
        // pushStack(stackForCall, REG_R5);
        // pushStack(stackForCall, REG_R4);
        // pushStack(stackForCall, REG_R3);
        // pushStack(stackForCall, REG_R2);
        // pushStack(stackForCall, REG_R1);
        // pushStack(stackForCall, REG_R0);
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
        freeStack(stackForCall);
        free(stackForCall);

        char *reg = popStack(stack);
        root->reg = reg;
        if (debug)
            printf("Call result in reg %s\n", root->reg);
    } else if (strcmp(root->label, OP_PLUS) == 0 ||
                strcmp(root->label, OP_MINUS) == 0 ||
                strcmp(root->label, OP_DIV) == 0 ||
                strcmp(root->label, OP_MUL) == 0 ||
                strcmp(root->label, OP_MOD) == 0 ||
                strcmp(root->label, OP_EQ) == 0 ||
                strcmp(root->label, OP_NEQ) == 0 ||
                strcmp(root->label, OP_GR) == 0 ||
                strcmp(root->label, OP_LE) == 0 ||
                strcmp(root->label, OP_GREQ) == 0 ||
                strcmp(root->label, OP_LEEQ) == 0 ||
                strcmp(root->label, OP_AND) == 0 ||
                strcmp(root->label, OP_OR) == 0) {
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
    } else if (strcmp(root->label, OP_NOT) == 0 ||
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
    } else if (strcmp(root->label, RETURN) == 0) {
        prepareRegsAndTempsHelper(root->children[0], stack, stackOnly, debug);
        root->reg = strdup(REG_RT);
        if (debug)
            printf("Return value %s in reg %s\n", root->children[0]->label, root->reg);
    }
}

void prepareRegsAndTemps(OperationTreeNode *root, bool debug) {
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
        prepareRegsAndTempsHelper(root->children[2], stack, stackOnly, debug);
    } else if (strcmp(root->label, SEQ_DECLARE) == 0) {
        for (uint32_t i = 0; i < root->childCount; i++) {
            if (strcmp(root->label, DECLARE) == 0 && root->childCount == 3) {
                uint8_t maxRegs = 0;
                calcMaxRegs(root->children[i], &maxRegs);

                bool stackOnly = maxRegs > 8;
                prepareRegsAndTempsHelper(root->children[i], stack, stackOnly, debug);
            } 
        }
    } else {
        uint8_t maxRegs = 0;
        calcMaxRegs(root, &maxRegs);

        bool stackOnly = maxRegs > 8;
        prepareRegsAndTempsHelper(root, stack, stackOnly, debug);
    }
    

    freeStack(stack);
    free(stack);
}

char* getSizeValueByType(const char* type, uint32_t arrayDim) {
    if (arrayDim > 0) {
        return "q";
    }
    if (strcmp(type, "char") == 0 || strcmp(type, "byte") == 0 || strcmp(type, "boolean") == 0) {
        return "b";
    } else if (strcmp(type, "int") == 0 || strcmp(type, "uint") == 0 || strcmp(type, "ref") == 0) {
        return "d";
    } else {
        return "q";
    }   
}

uint8_t getSizeByType(const char* type) {
    if (strcmp(type, "char") == 0 || strcmp(type, "byte") == 0 || strcmp(type, "boolean") == 0) {
        return 8;
    } else if (strcmp(type, "int") == 0 || strcmp(type, "uint") == 0 || strcmp(type, "ref") == 0) {
        return 32;
    } else {
        return 64;
    }   
}

bool contains(const char *str, const char *substr) {
    return strstr(str, substr) != NULL;
}

void generateBuiltin(const char *name, FunctionEntry *entry, OperationTreeNode *root, struct StringBuffer *buffer) {
    commandENTER(buffer, "0");
    if (strcmp(name, "__write") == 0) {
        commandLDoffset(buffer, "q", REG_R0, REG_BP, "8");
        commandMOV(buffer, REG_OUT, REG_R0);
        commandLDI32(buffer, REG_RT, "0");
    } else if (strcmp(name, "__read") == 0) {
        commandMOV(buffer, REG_RT, REG_IN);
    } else if (strcmp(name, "__writeChar") == 0) {
        commandLDoffset(buffer, "q", REG_R0, REG_BP, "8");
        commandMOV(buffer, REG_OUT, REG_R0);
        commandLDI32(buffer, REG_RT, "0");
    } else if (strcmp(name, "__readChar") == 0) {
        commandMOV(buffer, REG_RT, REG_IN);
    } else if (contains(name, "__toByteFrom")) {
        commandLDoffset(buffer, "q", REG_R0, REG_BP, "8");
        commandMOVT(buffer, "b", REG_RT, REG_R0);
    } else if (strcmp(name, "__toIntFromByte") == 0) {
        commandLDoffset(buffer, "b", REG_R0, REG_BP, "8");
        commandCBD(buffer, REG_RT, REG_R0);
    } else if (contains(name, "__toIntFrom")) {
        commandLDoffset(buffer, "q", REG_R0, REG_BP, "8");
        commandMOVT(buffer, "d", REG_RT, REG_R0);
    } else if (strcmp(name, "__toUintFromByte") == 0) {
        commandLDoffset(buffer, "b", REG_R0, REG_BP, "8");
        commandMOVZX(buffer, "d", REG_RT, REG_R0);
    } else if (contains(name, "__toUintFrom")) {
        commandLDoffset(buffer, "q", REG_R0, REG_BP, "8");
        commandMOVT(buffer, "d", REG_RT, REG_R0);
    } else if (strcmp(name, "__toLongFromByte") == 0) {
        commandLDoffset(buffer, "b", REG_R0, REG_BP, "8");
        commandCBQ(buffer, REG_RT, REG_R0);
    } else if (strcmp(name, "__toLongFromInt") == 0) {
        commandLDoffset(buffer, "d", REG_R0, REG_BP, "8");
        commandCDQ(buffer, REG_RT, REG_R0);
    } else if (strcmp(name, "__toLongFromUint") == 0) {
        commandLDoffset(buffer, "d", REG_R0, REG_BP, "8");
        commandMOVZX(buffer, "q", REG_RT, REG_R0);
    } else if (strcmp(name, "__toLongFromUlong") == 0) {
        commandLDoffset(buffer, "q", REG_R0, REG_BP, "8");
        commandMOVT(buffer, "q", REG_RT, REG_R0);
    } else if (strcmp(name, "__toUlongFromLong") == 0) {
        commandLDoffset(buffer, "q", REG_R0, REG_BP, "8");
        commandMOVT(buffer, "q", REG_RT, REG_R0);
    } else if (contains(name, "__toUlongFrom")) {
        commandLDoffset(buffer, "q", REG_R0, REG_BP, "8");
        commandMOVZX(buffer, "q", REG_RT, REG_R0);
    } else if (strcmp(name, "__allocRef") == 0) {
        commandLDoffset(buffer, "q", REG_R0, REG_BP, "8");
        commandMOV(buffer, REG_RT, REG_ALR);
        commandADD(buffer, "q", REG_ALR, REG_R0);  
    } else if (strcmp(name, "__cmpRef") == 0) {
        commandLDoffset(buffer, "d", REG_R0, REG_BP, "8");
        commandLDoffset(buffer, "d", REG_R1, REG_BP, "16");
        commandCMP(buffer, "d", REG_R0, REG_R1);
        commandEQ(buffer, REG_RT);
    } else if (strcmp(name, "__lastALR") == 0) {
        commandMOV(buffer, REG_RT, REG_ALR);
    } else if (strcmp(name, "__lastSP") == 0) {
        commandMOV(buffer, REG_RT, REG_SP);
    }
    commandLEAVE(buffer, "0");
}

char parseEscapedChar(const char *str) {
    if (str[1] != '\\') {
        return str[1];
    }
    switch (str[2]) {
        case 'n':  return '\n';
        case 't':  return '\t';
        case 'r':  return '\r';
        case '0':  return '\0';
        case '\\': return '\\';
        default:   return str[2];
    }
}

void generateASMForOTHelper(FunctionEntry *entry, OperationTreeNode *root, struct StringBuffer *buffer) {
    if (strcmp(root->label, WRITE) == 0) {
        if (root->children[0]->childCount == 0) {
            generateASMForOTHelper(entry, root->children[1], buffer);
            bool found = false;
            for (int i = 0; i < entry->locals->size; i++) {
                HashNode *node = entry->locals->buckets[i];
                while (node) {
                    if (strcmp(((LocalVar *)node->value)->name, root->children[0]->label) == 0) {
                        uint32_t index = ((LocalVar *)node->value)->index;
                        int64_t offset = ((int32_t)index + 1) * -8;
                        char offsetBuffer[1024];
                        snprintf(offsetBuffer, sizeof(offsetBuffer), "%ld", offset);
                        //commandLD(buffer, getSizeValueByType(root->children[0]->type->typeName), root->children[0]->reg, REG_BP);
                        commentVar(buffer, root->children[0]->label);
                        commandSToffset(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->children[1]->reg, REG_BP, offsetBuffer);
                        found = true;
                        break;
                    }
                    if(found)
                        break;
                    node = node->next;
                }
            }
        } else {
            generateASMForOTHelper(entry, root->children[0], buffer);
            generateASMForOTHelper(entry, root->children[1], buffer);
            commandST(buffer, "q", root->children[1]->reg, root->children[0]->reg);
        }
    } else if (strcmp(root->label, INDEX) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandLDI32(buffer, REG_BR2, "8");
        commandMUL(buffer, "q", root->children[1]->reg, REG_BR2);
        commandADD(buffer, "q", root->children[0]->reg, root->children[1]->reg);
        // if (strcmp(root->children[0]->type->typeName, "string") == 0) {
        //     commandLDC64(buffer, root->children[0]->reg, root->children[0]->reg);
        // } else {
        //     commandLD(buffer, "q", root->children[0]->reg, root->children[0]->reg);
        // }
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, INDEXR) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandLDI32(buffer, REG_BR2, "8");
        commandMUL(buffer, "q", root->children[1]->reg, REG_BR2);
        commandADD(buffer, "q", root->children[0]->reg, root->children[1]->reg);
        if (strcmp(root->children[0]->type->typeName, "string") == 0) {
            commandLDC64(buffer, root->children[0]->reg, root->children[0]->reg);
        } else {
            commandLD(buffer, "q", root->children[0]->reg, root->children[0]->reg);
        }
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OT_CALL) == 0) {
        for (uint32_t i = 1; i <= root->childCount - 1; i++) {
            generateASMForOTHelper(entry, root->children[i], buffer);
        }

        commandMOV(buffer, REG_BR1, REG_SP);
        commandPUSH(buffer, REG_R0);
        commandPUSH(buffer, REG_R1);
        commandPUSH(buffer, REG_R2);
        commandPUSH(buffer, REG_R3);
        commandPUSH(buffer, REG_R4);
        commandPUSH(buffer, REG_R5);
        commandPUSH(buffer, REG_R6);
        commandPUSH(buffer, REG_R7);

        bool wasSpilled = false;
        for (uint32_t i = root->childCount - 1; i > 0; i--) {
            if(root->children[i]->isSpilled) {
                wasSpilled = true;
                char offsetBuffer[1024];
                snprintf(offsetBuffer, sizeof(offsetBuffer), "%d", root->children[i]->offset - 8);
                commandLDoffset(buffer, getSizeValueByType(root->children[i]->type->typeName, root->children[i]->type->arrayDim), root->children[i]->reg, REG_BR1, offsetBuffer);                
                commentVar(buffer, root->children[i]->children[0]->label);
                commandPUSH(buffer, root->children[i]->reg);
            } else {
                commentVar(buffer, root->children[i]->children[0]->label);
                commandPUSH(buffer, root->children[i]->reg);
            }
        }

        if ((root->children[0]->label[0] == '_') && (root->children[0]->label[1] == '_')) {
            generateBuiltin(root->children[0]->label, entry, root, buffer);
        } else {
            commandCALL(buffer, root->children[0]->label);
        }

        for (uint32_t i = 1; i <= root->childCount - 1; i++) {
            commentVar(buffer, root->children[i]->children[0]->label);
            commandPOP(buffer, root->children[i]->reg);
        }

        if (wasSpilled) {
            char countBuffer[1024];
            snprintf(countBuffer, sizeof(countBuffer), "%u", (root->childCount - 1) * 8);
            commandLDI32(buffer, REG_BR1, countBuffer);
            commandADD(buffer, "q", REG_SP, REG_BR1);
        }
            

        commandPOP(buffer, REG_R7);
        commandPOP(buffer, REG_R6);
        commandPOP(buffer, REG_R5);
        commandPOP(buffer, REG_R4);
        commandPOP(buffer, REG_R3);
        commandPOP(buffer, REG_R2);
        commandPOP(buffer, REG_R1);
        commandPOP(buffer, REG_R0);

        commandMOV(buffer, root->reg, REG_RT);

        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_PLUS) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandADD(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_MINUS) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandSUB(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_DIV) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandDIV(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_MUL) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandMUL(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_MOD) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandMOD(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_EQ) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandCMP(buffer, getSizeValueByType(root->children[0]->type->typeName, root->children[0]->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        commandEQ(buffer, root->children[0]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_NEQ) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandCMP(buffer, getSizeValueByType(root->children[0]->type->typeName, root->children[0]->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        commandNEQ(buffer, root->children[0]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_GR) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandCMP(buffer, getSizeValueByType(root->children[0]->type->typeName, root->children[0]->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        commandGR(buffer, root->children[0]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_LE) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandCMP(buffer, getSizeValueByType(root->children[0]->type->typeName, root->children[0]->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        commandLE(buffer, root->children[0]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_GREQ) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandCMP(buffer, getSizeValueByType(root->children[0]->type->typeName, root->children[0]->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        commandGREQ(buffer, root->children[0]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_LEEQ) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandCMP(buffer, getSizeValueByType(root->children[0]->type->typeName, root->children[0]->type->arrayDim), root->children[0]->reg, root->children[1]->reg);
        commandLEEQ(buffer, root->children[0]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_AND) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandAND(buffer, "q", root->children[0]->reg, root->children[1]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_OR) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        generateASMForOTHelper(entry, root->children[1], buffer);
        commandOR(buffer, "q", root->children[0]->reg, root->children[1]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_NOT) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        commandNOT(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->children[0]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, OP_NEG) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        commandNEG(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->children[0]->reg);
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, LIT_READ) == 0) {
        if (strcmp(root->children[1]->type->typeName, "ulong") == 0 || 
            strcmp(root->children[1]->type->typeName, "long") == 0) {
            for (int i = 0; i < entry->consts->size; i++) {
                HashNode *node = entry->consts->buckets[i];
                while (node) {
                    if (strcmp(((ConstVar *)node->value)->name, root->children[1]->label) == 0) {
                        commandLDI32(buffer, REG_AR, node->key);
                        commandLDC64(buffer, root->reg, REG_AR);  
                        break;
                    }
                    node = node->next;
                }
            }   
        } else if (strcmp(root->children[1]->type->typeName, "string") == 0) {
            for (int i = 0; i < entry->consts->size; i++) {
                HashNode *node = entry->consts->buckets[i];
                while (node) {
                    if (strcmp(((ConstVar *)node->value)->name, root->children[1]->label) == 0) {
                        commandLDI32(buffer, root->reg, node->key);  
                        break;
                    }
                    node = node->next;
                }
            }   
        } else {
            if (strcmp(root->children[1]->type->typeName, "bool") == 0) {
                if (strcmp(root->children[1]->label, "true") == 0) {
                    commandLDI32(buffer, root->reg, "1");
                } else {
                    commandLDI32(buffer, root->reg, "0");
                }
            } else if (strcmp(root->children[1]->type->typeName, "char") == 0) {
                unsigned char value = parseEscapedChar(root->children[1]->label);
                char output[6]; 
                sprintf(output, "0x%02X", value);
                commandLDI32(buffer, root->reg, output);
            } else {
                commandLDI32(buffer, root->reg, root->children[1]->label);
            } 
        }

        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, READ) == 0) {
        bool found = false;
        for (int i = 0; i < entry->locals->size; i++) {
            HashNode *node = entry->locals->buckets[i];
            while (node) {
                if (strcmp(((LocalVar *)node->value)->name, root->children[0]->label) == 0) {
                    uint32_t index = ((LocalVar *)node->value)->index;
                    int64_t offset = ((int32_t)index + 1) * -8;
                    char offsetBuffer[1024];
                    snprintf(offsetBuffer, sizeof(offsetBuffer), "%ld", offset);
                    //commandLD(buffer, getSizeValueByType(root->children[0]->type->typeName), root->children[0]->reg, REG_BP);
                    commentVar(buffer, root->children[0]->label);
                    if (strcmp(((LocalVar *)node->value)->typeName, "string") == 0) {
                        commandLDoffset(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->reg, REG_BP, offsetBuffer);
                        //commandLDC64(buffer, root->reg, root->reg);
                    } else {
                        commandLDoffset(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->reg, REG_BP, offsetBuffer);
                    }
                    found = true;
                    break;
                }
                node = node->next;
            }
            if (found)
                break;
        }

        if (!found) {
            for (int i = 0; i < entry->argumentsCount; i++) {
                ArgumentInfo *arg = entry->arguments;
                while (arg) {
                    if (strcmp(arg->name, root->children[0]->label) == 0) {
                        char offsetBuffer[1024];
                        snprintf(offsetBuffer, sizeof(offsetBuffer), "%ld", arg->offset);
                        //commandLD(buffer, getSizeValueByType(root->children[0]->type->typeName), root->children[0]->reg, REG_BP);
                        commentVar(buffer, root->children[0]->label);
                        commandLDoffset(buffer, getSizeValueByType(root->type->typeName, root->type->arrayDim), root->reg, REG_BP, offsetBuffer);
                        found = true;
                        break;
                    }
                    arg = arg->next;
                }
                if (found)
                    break;
            }            
        }
        if (root->isSpilled) {
            commandPUSH(buffer, root->reg);
        }
    } else if (strcmp(root->label, RETURN) == 0) {
        generateASMForOTHelper(entry, root->children[0], buffer);
        commandMOV(buffer, root->reg, root->children[0]->reg);
    }
}

void generateASMForOT(FunctionEntry *entry, OperationTreeNode *root, struct StringBuffer *buffer) {
    commentOTPosition(buffer, root->line, root->pos);
    if (strcmp(root->label, DECLARE) == 0 && root->childCount == 3) {
        generateASMForOTHelper(entry, root->children[2], buffer);
    } else if (strcmp(root->label, SEQ_DECLARE) == 0) {
        for (uint32_t i = 0; i < root->childCount; i++) {
            if (strcmp(root->label, DECLARE) == 0 && root->childCount == 3) {
                generateASMForOTHelper(entry, root->children[i], buffer);
            } 
        }
    } else {
        generateASMForOTHelper(entry, root, buffer);
    }
}

void generateASMForUnconditionalBlock(struct StringBuffer *buffer, BasicBlock *block, FunctionEntry *entry, char *nextLabel) {
    stringbuffer_append_string(buffer, ".BB");
    stringbuffer_append_long(buffer, block->id);
    stringbuffer_append_string(buffer, ":\n");
    for (int i = 0; i < block->instructionCount; i++) {
        generateASMForOT(entry, block->instructions[i].otRoot, buffer);
    }
    commandJMP(buffer, nextLabel);    
}

void generateASMForConditionalBlock(struct StringBuffer *buffer, BasicBlock *block, FunctionEntry *entry, char *trueLabel, char *falseLabel) {
    stringbuffer_append_string(buffer, ".BB");
    stringbuffer_append_long(buffer, block->id);
    stringbuffer_append_string(buffer, ":\n");
    for (int i = 0; i < block->instructionCount; i++) {
        generateASMForOT(entry, block->instructions[i].otRoot, buffer);
    }
    commandJZ(buffer, trueLabel); 
    commandJNZ(buffer, falseLabel);   
}

size_t countBlocks(const BasicBlock *head) {
    size_t count = 0;
    while (head != NULL) {
        ++count;
        head = head->next;
    }
    return count;
}

BasicBlock *convertListToArray(const BasicBlock *head, size_t *size) {
    *size = countBlocks(head);
    if (*size == 0) {
        return NULL;
    }

    BasicBlock *array = malloc(*size * sizeof(BasicBlock));
    if (!array) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    size_t i = 0;
    while (head != NULL) {
        array[i++] = *head;
        head = head->next;
    }

    return array;
}

int compareBlocks(const void *a, const void *b) {
    const BasicBlock *blockA = (const BasicBlock *)a;
    const BasicBlock *blockB = (const BasicBlock *)b;
    
    // Compare blocks by id
    return (blockA->id - blockB->id);
}

void generateASMForFunction(struct StringBuffer *buffer, FunctionInfo *func, FunctionEntry *funcE, bool main, bool debug) {
    stringbuffer_append_string(buffer, func->functionName);
    stringbuffer_append_string(buffer, ":\n\n");

    BasicBlock *b = func->cfg->blocks;
    size_t size = 0;
    BasicBlock *array = convertListToArray(b, &size);

    qsort(array, size, sizeof(BasicBlock), compareBlocks);

    char localsNumberBuffer[1024];
    snprintf(localsNumberBuffer, sizeof(localsNumberBuffer), "%d", funcE->locals->count);
    stringbuffer_append_string(buffer, ".BB");
    stringbuffer_append_long(buffer, array[0].id);
    stringbuffer_append_string(buffer, ":\n");
    commandENTER(buffer, localsNumberBuffer);

    for (size_t i = 1; i < size - 1; ++i) {

        if (array[i].type == CONDITIONAL) {
            struct StringBuffer *falseBlockBuffer = stringbuffer_new_with_options(1024, true);
            stringbuffer_append_string(falseBlockBuffer, ".BB");
            stringbuffer_append_long(falseBlockBuffer, array[i].outEdges->targetBlock->id);
            char *falseOut = stringbuffer_to_string(falseBlockBuffer);  
            
            struct StringBuffer *trueBlockBuffer = stringbuffer_new_with_options(1024, true);
            stringbuffer_append_string(trueBlockBuffer, ".BB");
            stringbuffer_append_long(trueBlockBuffer, array[i].outEdges->nextOut->targetBlock->id);
            char *trueOut = stringbuffer_to_string(trueBlockBuffer); 

            generateASMForConditionalBlock(buffer, &array[i], funcE, trueOut, falseOut);

            free(falseOut);
            free(trueOut);
            stringbuffer_release(falseBlockBuffer);
            stringbuffer_release(trueBlockBuffer);
        } else if (array[i].type == UNCONDITIONAL) {
            struct StringBuffer *blockBuffer = stringbuffer_new_with_options(1024, true);
            stringbuffer_append_string(blockBuffer, ".BB");
            stringbuffer_append_long(blockBuffer, array[i].outEdges->targetBlock->id);
            char *out = stringbuffer_to_string(blockBuffer);
            
            generateASMForUnconditionalBlock(buffer, &array[i], funcE, out);
            
            free(out);
            stringbuffer_release(blockBuffer);
        }

        stringbuffer_append_string(buffer, "\n");
    }

    stringbuffer_append_string(buffer, ".BB");
    stringbuffer_append_long(buffer, array[size - 1].id);
    stringbuffer_append_string(buffer, ":\n");
    commandLEAVE(buffer, localsNumberBuffer);
    if(!main)
        commandRET(buffer);
    else
        commandHLT(buffer);
    stringbuffer_append_string(buffer, "\n");
    free(array);
}