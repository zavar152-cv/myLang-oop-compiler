#include "symbols.h"
#include <stdint.h>
#include <string.h>

char* concatName(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void removeQuotesName(const char *input, char *output) {
    int i = 0, j = 0;

    while (input[i] != '\0') {
        if (input[i] != '\'' && input[i] != '"') {
            output[j] = input[i];
            j++;
        }
        i++;
    }
    output[j] = '\0';
}

void scanOperationTreeForVarsHelper(FunctionEntry *entry, OperationTreeNode *root) {
    if (strcmp(root->label, DECLARE) == 0) {
        bool custom = strcmp(root->children[0]->children[1]->label, "buitin") != 0;
        bool array = root->children[0]->childCount == 3;
        uint32_t arrayDim = 0;
        if (array) {
            char *endptr;
            arrayDim = strtol(root->children[0]->children[2]->children[0]->label, &endptr, 10);
        }
        uint8_t size = getTypeSize(root->children[0]->children[0]->label, custom, array);
        LocalVar *local = createLocalVar(root->children[1]->label, root->children[0]->children[0]->label, size, custom, array, arrayDim);
        insertInHashTable(entry->locals, local->name, local);
    }
    if (strcmp(root->label, LIT_READ) == 0 && 
        (strcmp(root->type->typeName, "string") == 0 ||
            strcmp(root->type->typeName, "long") == 0 ||
            strcmp(root->type->typeName, "ulong") == 0)) {
        uint8_t size = 8;
        ConstVar *local = createConstVar(root->children[1]->label, root->type->typeName, size);
        char* name = concatName("const$", local->name);
        char output[strlen(name) + 1]; 
        removeQuotesName(name, output);
        insertInHashTable(entry->consts, output, local);
        free(name);
    }
    for (uint32_t i = 0; i < root->childCount; i++) {
        scanOperationTreeForVarsHelper(entry, root->children[i]);
    }
}

void scanOperationTreeForVars(FunctionEntry *entry, OperationTreeNode *root) {
    scanOperationTreeForVarsHelper(entry, root);
}

LocalVar *createLocalVar(const char *name, const char *typeName, uint8_t size, bool custom, bool isArray, uint32_t arrayDim) {
    LocalVar *var = (LocalVar *)malloc(sizeof(LocalVar));
    if (!var) {
        return NULL;
    }

    var->name = name ? strdup(name) : NULL;
    var->typeName = typeName ? strdup(typeName) : NULL;

    var->size = size;
    var->custom = custom;
    var->isArray = isArray;
    var->arrayDim = arrayDim;

    return var;
}

void freeLocalVar(LocalVar *var) {
    if (!var) {
        return;
    }

    if (var->name) {
        free(var->name);
    }
    if (var->typeName) {
        free(var->typeName);
    }

    free(var);
}

ConstVar *createConstVar(const char *name, const char *typeName, uint8_t size) {
    ConstVar *var = (ConstVar *)malloc(sizeof(ConstVar));
    if (!var) {
        return NULL;
    }

    var->name = name ? strdup(name) : NULL;
    var->typeName = typeName ? strdup(typeName) : NULL;

    var->size = size;

    return var;    
}

void freeConstVar(ConstVar *var) {
    if (!var) {
        return;
    }

    if (var->name) {
        free(var->name);
    }
    if (var->typeName) {
        free(var->typeName);
    }

    free(var);   
}