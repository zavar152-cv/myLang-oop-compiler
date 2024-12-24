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
        LocalVar *local = createLocalVar(root->children[1]->label, root->children[0]->children[0]->label, size, custom, array, arrayDim, entry->locals->count);
        char name[1024];
        snprintf(name, sizeof(name), "var%d", entry->locals->count);
        insertInHashTable(entry->locals, name, local);
    }
    if (strcmp(root->label, LIT_READ) == 0 && 
        (strcmp(root->type->typeName, "string") == 0 ||
            strcmp(root->type->typeName, "long") == 0 ||
            strcmp(root->type->typeName, "ulong") == 0)) {
        uint8_t size = 8;
        
        ConstVar *constVar = createConstVar(root->children[1]->label, root->type->typeName, size, 0);
        char name[1024];
        snprintf(name, sizeof(name), "const%d", entry->consts->count);
        if (strcmp(root->type->typeName, "string") == 0) {
            constVar->size = strlen(constVar->name) + 1 - 2;
        }

        bool exists = false;
        for (int i = 0; i < entry->consts->size; i++) {
            HashNode *node = entry->consts->buckets[i];
            while (node) {
                if (strcmp(((ConstVar *)node->value)->name, constVar->name) == 0) {
                    exists = true;
                    break;
                }
                node = node->next;
            }
        }

        if (!exists) {
            insertInHashTable(entry->consts, name, constVar);
        } else {
            freeConstVar(constVar);
        }
    }
    for (uint32_t i = 0; i < root->childCount; i++) {
        scanOperationTreeForVarsHelper(entry, root->children[i]);
    }
}

void scanOperationTreeForVars(FunctionEntry *entry, OperationTreeNode *root) {
    scanOperationTreeForVarsHelper(entry, root);
}

LocalVar *createLocalVar(const char *name, const char *typeName, uint8_t size, bool custom, bool isArray, uint32_t arrayDim, uint32_t index) {
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
    var->index = index;

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

ConstVar *createConstVar(const char *name, const char *typeName, uint8_t size, uint32_t address) {
    ConstVar *var = (ConstVar *)malloc(sizeof(ConstVar));
    if (!var) {
        return NULL;
    }

    var->name = name ? strdup(name) : NULL;
    var->typeName = typeName ? strdup(typeName) : NULL;

    var->size = size;
    var->address = address;

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