#pragma once 

#include "../cfg/ot/ot.h"
#include <sys/types.h>

typedef struct LocalVar {
    char *name;
    char *typeName;
    uint8_t size;
    bool custom;
    bool isArray;
    uint32_t arrayDim;
    uint32_t index;
} LocalVar;

typedef struct ConstVar {
    char *name;
    char *typeName;
    uint8_t size;
    uint32_t address;
    union {
        uint64_t ulongV;
        int64_t longV;
        const char *stringV;
    } value;
} ConstVar;

void scanOperationTreeForVars(FunctionEntry *entry, OperationTreeNode *root);

LocalVar *createLocalVar(const char *name, const char *typeName, uint8_t size, bool custom, bool isArray, uint32_t arrayDim, uint32_t index);

void freeLocalVar(LocalVar *var);

ConstVar *createConstVar(const char *name, const char *typeName, uint8_t size, uint32_t index);

void freeConstVar(ConstVar *var);