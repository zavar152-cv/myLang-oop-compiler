#include "symbols.h"
#include <stdint.h>

void scanOperationTreeForVarsHelper(FunctionEntry *entry, OperationTreeNode *root) {
    if (strcmp(root->label, DECLARE) == 0) {
        bool custom;
        bool array;
        uint8_t size = getTypeSize(root->children[0]->children[0]->label, custom, array);
        LocalVar *local = createLocalVar(root->children[1]->label, root->children[0]->children[0]->label, size, custom, array);
        insertInHashTable(entry->locals, local->name, local);
    }
    for (uint32_t i = 0; i < root->childCount; i++) {
        scanOperationTreeForVarsHelper(entry, root->children[i]);
    }
}

void scanOperationTreeForVars(FunctionEntry *entry, OperationTreeNode *root) {
    scanOperationTreeForVarsHelper(entry, root);
}

LocalVar *createLocalVar(const char *name, const char *typeName, uint8_t size, bool custom, bool isArray) {
    LocalVar *var = (LocalVar *)malloc(sizeof(LocalVar));
    if (!var) {
        return NULL;
    }

    var->name = name ? strdup(name) : NULL;
    var->typeName = typeName ? strdup(typeName) : NULL;

    var->size = size;
    var->custom = custom;
    var->isArray = isArray;

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