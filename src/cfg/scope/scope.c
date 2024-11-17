#include "scope.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void enterScope(ScopeManager *sm) {
    SymbolTable *newScope = malloc(sizeof(SymbolTable));
    newScope->symbols = NULL;
    newScope->parent = sm->currentScope;
    newScope->scopeLevel = sm->currentScopeLevel++;
    sm->currentScope = newScope;
}

void exitScope(ScopeManager *sm) {
    if (sm->currentScope == NULL) return;

    SymbolTable *oldScope = sm->currentScope;
    sm->currentScope = sm->currentScope->parent;
    sm->currentScopeLevel--;

    Symbol *sym = oldScope->symbols;
    while (sym) {
        Symbol *next = sym->next;
        free(sym->name);
        free(sym->typeName);
        free(sym);
        sym = next;
    }
    free(oldScope);
}

void addSymbol(ScopeManager *sm, const char *name, const char *typeName, bool custom, bool isArray, uint32_t arrayDim, uint32_t line, uint32_t pos) {
    if (sm->currentScope == NULL) return;

    Symbol *newSym = malloc(sizeof(Symbol));
    newSym->name = strdup(name);
    newSym->typeName = strdup(typeName);
    newSym->custom = custom;
    newSym->isArray = isArray;
    newSym->arrayDim = arrayDim;
    newSym->line = line;
    newSym->pos = pos;
    newSym->next = sm->currentScope->symbols;
    sm->currentScope->symbols = newSym;
}

Symbol* findSymbol(ScopeManager *sm, const char *name) {
    SymbolTable *scope = sm->currentScope;
    while (scope) {
        Symbol *sym = scope->symbols;
        while (sym) {
            if (strcmp(sym->name, name) == 0) {
                return sym;
            }
            sym = sym->next;
        }
        scope = scope->parent;
    }
    return NULL;
}

void printScope(SymbolTable *scope, const char *functionName) {
    if (scope == NULL) return;
    printScope(scope->parent, functionName);

    printf("Scope level %d of %s:\n", scope->scopeLevel, functionName);
    Symbol *sym = scope->symbols;
    while (sym) {
        printf("  %s of %s\n", sym->name, sym->typeName);
        sym = sym->next;
    }
}

void printScopes(ScopeManager *sm) {
    printScope(sm->currentScope, sm->name);
    printf("\n\n");
}