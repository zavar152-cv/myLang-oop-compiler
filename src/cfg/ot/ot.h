#pragma once

#include "../../grammar/ast/myAst.h"
#include "../scope/scope.h"
#include "../../hashtable/hashtable.h"
#include <stdbool.h>
#include <stdint.h>

#define OT_LIT_READ "litRead"
#define OT_READ "read"
#define OT_WRITE "write"
#define OT_CALL "call"
#define OT_INDEX "index"
#define OT_INDEXR "indexr"
#define OT_DECLARE "declare"
#define OT_SEQ_DECLARE "seqDeclare"
#define OT_WITH_TYPE "withType"
#define OT_CUSTOM "custom"
#define OT_BUILTIN "builtin"
#define OT_ARRAY "array"
#define OT_RETURN "return"
#define OT_BREAK "break"
#define OT_NEW "new"
#define OT_METHOD "method"
#define OT_FIELD "field"

typedef struct OperationTreeNode {
  struct OperationTreeNode **children;
  uint32_t childCount;
  const char *label;
  uint32_t line;
  uint32_t pos;
  bool isImaginary;
  TypeInfo *type;
  char *reg;
  bool isSpilled;
  int32_t offset;
} OperationTreeNode;

typedef struct __attribute__((packed)) OperationTreeErrorInfo {
    char *message;
    struct OperationTreeErrorInfo *next;
} OperationTreeErrorInfo;

typedef struct OperationTreeErrorContainer {
    struct OperationTreeErrorInfo *error;
} OperationTreeErrorContainer;

typedef struct ArgumentInfo {
    TypeInfo *type;
    char *name;
    bool isVarargs;
    struct ArgumentInfo *next;
    uint32_t line;
    uint32_t pos;
    int64_t offset;
} ArgumentInfo;

typedef struct FieldInfo {
    TypeInfo *type;
    char *name;
    bool isPrivate;
    bool isStatic;
    struct FieldInfo *next;
    uint32_t line;
    uint32_t pos;
    int64_t offset;
} FieldInfo;

typedef struct ClassVtableEntry {
    char *functionName;
    char *className;
    int64_t offset;
    bool isBuiltin;
    struct ClassVtableEntry *next;
    struct ClassVtableEntry *prev;
} ClassVtableEntry;

typedef struct ClassVtable {
    ClassVtableEntry *head;
    ClassVtableEntry *tail;
    int64_t currentOffset;
} ClassVtable;

typedef struct ClassInfo {
    char *name;
    char *parentName;
    char **interfaceNames;
    int interfaceCount;
    bool isInterface;
    FieldInfo *fields;
    uint64_t fieldsCount;
    MyAstNode *body;
    char *fileName;
    uint64_t typeId;
    struct Program *program;
    ClassVtable *vtable;
    struct ClassInfo *next;
} ClassInfo;

typedef struct __attribute__((packed)) FunctionEntry {
    char *fileName;
    char *functionName;
    TypeInfo *returnType;
    ArgumentInfo *arguments;
    bool isVarargs;
    bool isBuiltin;
    bool isPrivate;
    bool isStatic;
    bool isConstructor;
    bool isOverride;
    HashTable *locals;
    HashTable *consts;
    struct FunctionEntry *next;
    uint32_t argumentsCount;
    uint32_t line;
    uint32_t pos;
} FunctionEntry;

typedef struct FunctionTable {
    FunctionEntry *entry;
} FunctionTable;

OperationTreeNode *newOperationTreeNode(const char *label, uint32_t childCount, uint32_t line, uint32_t pos, bool isImaginary);

OperationTreeNode *buildVarOperationTreeFromAstNode(MyAstNode* root, OperationTreeErrorContainer *container, TypeInfo* varType, ScopeManager *sm, FunctionTable *functionTable, ClassInfo* classes, ClassInfo *currentClass, const char* filename);

TypeInfo* parseTyperef(MyAstNode* typeRef);

void destroyOperationTreeNodeTree(OperationTreeNode *root);

OperationTreeNode *buildExprOperationTreeFromAstNode(MyAstNode* root, bool isLvalue, bool isFunctionName, bool isMethod, OperationTreeErrorContainer *error, ScopeManager *sm, FunctionTable *functionTable, ClassInfo* classes, ClassInfo *currentClass, const char* filename);

void printOperationTree(OperationTreeNode *root);

OperationTreeErrorInfo* createOperationTreeErrorInfo(const char *message);

void addOperationTreeError(OperationTreeErrorContainer *container, const char *message);

void freeOperationTreeErrors(OperationTreeErrorInfo *error);

bool isBinaryOp(const char *label);

bool isUnaryOp(const char *label);

bool isLiteral(const char *label);

ArgumentInfo *copyArgumentInfo(ArgumentInfo *argInfo);

TypeInfo *copyTypeInfo(TypeInfo *typeInfo);

FunctionEntry *createFunctionEntry(const char *fileName, const char *functionName, TypeInfo *returnType, ArgumentInfo *arguments, bool isVarargs, bool isBuiltin, bool isStatic, bool isPrivate, bool isConstructor, uint32_t argumentsCount, uint32_t line, uint32_t pos);

void freeFunctionEntry(FunctionEntry *entry, void (*freeValueLocals)(void *), void (*freeValueConsts)(void *));

FunctionTable *createFunctionTable();

void freeFunctionTable(FunctionTable *table, void (*freeValueLocals)(void *), void (*freeValueConsts)(void *));

void addFunctionTable(FunctionTable *table, FunctionEntry *entry);

FunctionEntry *findFunctionEntry(FunctionTable *table, const char *functionName);

void checkTypeCompatibility(OperationTreeNode *lValueExprNode, OperationTreeNode *rValueExprNode, OperationTreeErrorContainer *container, ClassInfo *classes, const char* filename);

uint8_t getTypeSize(const char *type, bool custom, bool array);

ClassInfo *findClassWithName(ClassInfo *classes, char *name);

FunctionEntry *findFunctionEntryWithName(FunctionTable *table, char *name);