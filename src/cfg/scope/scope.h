#pragma once

#include <stdbool.h>
#include <stdint.h>
typedef struct TypeInfo TypeInfo;

typedef struct TypeInfo {
    char *typeName;
    bool custom;
    bool isArray;
    uint32_t arrayDim;
    uint32_t line;
    uint32_t pos;
    TypeInfo *next;
} TypeInfo;

typedef struct Symbol {
    char *name;
    char *typeName;
    bool custom;
    bool isArray;
    uint32_t arrayDim;
    uint32_t line;
    uint32_t pos;
    struct Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *symbols;
    struct SymbolTable *parent;
    int scopeLevel;
} SymbolTable;

typedef struct ScopeManager {
    SymbolTable *currentScope;
    int currentScopeLevel;
    const char *name;
} ScopeManager;

void enterScope(ScopeManager *sm);

void exitScope(ScopeManager *sm);

void addSymbol(ScopeManager *sm, const char *name, const char *typeName, bool custom, bool isArray, uint32_t arrayDim, uint32_t line, uint32_t pos);

Symbol* findSymbol(ScopeManager *sm, const char *name);

void printScopes(ScopeManager *sm);