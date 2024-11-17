#pragma once

#include "../../grammar/ast/myAst.h"
#include "../scope/scope.h"
#include <stdbool.h>
#include <stdint.h>

#define LIT_READ "litRead"
#define READ "read"
#define WRITE "write"
#define OT_CALL "call"
#define INDEX "index"
#define DECLARE "declare"
#define SEQ_DECLARE "seqDeclare"
#define WITH_TYPE "withType"
#define CUSTOM "custom"
#define BUILTIN "builtin"
#define OT_ARRAY "array"
#define RETURN "return"
#define OT_BREAK "break"

typedef struct OperationTreeNode {
  struct OperationTreeNode **children;
  uint32_t childCount;
  const char *label;
  uint32_t line;
  uint32_t pos;
  bool isImaginary;
  TypeInfo *type;
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
    struct ArgumentInfo *next;
    uint32_t line;
    uint32_t pos;
} ArgumentInfo;

typedef struct FunctionEntry {
    char *fileName;
    char *functionName;
    TypeInfo *returnType;
    ArgumentInfo *arguments;
    struct FunctionEntry *next;
    uint32_t argumentsCount;
    uint32_t line;
    uint32_t pos;
} FunctionEntry;

typedef struct FunctionTable {
    FunctionEntry *entry;
} FunctionTable;

OperationTreeNode *newOperationTreeNode(const char *label, uint32_t childCount, uint32_t line, uint32_t pos, bool isImaginary);

OperationTreeNode *buildVarOperationTreeFromAstNode(MyAstNode* root, OperationTreeErrorContainer *container, TypeInfo* varType, ScopeManager *sm, FunctionTable *functionTable, const char* filename);

TypeInfo* parseTyperef(MyAstNode* typeRef);

void destroyOperationTreeNodeTree(OperationTreeNode *root);

OperationTreeNode *buildExprOperationTreeFromAstNode(MyAstNode* root, bool isLvalue, bool isFunctionName, OperationTreeErrorContainer *error, ScopeManager *sm, FunctionTable *functionTable, const char* filename);

void printOperationTree(OperationTreeNode *root);

OperationTreeErrorInfo* createOperationTreeErrorInfo(const char *message);

void addOperationTreeError(OperationTreeErrorContainer *container, const char *message);

void freeOperationTreeErrors(OperationTreeErrorInfo *error);

bool isBinaryOp(const char *label);

bool isUnaryOp(const char *label);

bool isLiteral(const char *label);

ArgumentInfo *copyArgumentInfo(ArgumentInfo *argInfo);

TypeInfo *copyTypeInfo(TypeInfo *typeInfo);

FunctionEntry *createFunctionEntry(const char *fileName, const char *functionName, TypeInfo *returnType, ArgumentInfo *arguments, uint32_t argumentsCount, uint32_t line, uint32_t pos);

void freeFunctionEntry(FunctionEntry *entry);

FunctionTable *createFunctionTable();

void freeFunctionTable(FunctionTable *table);

void addFunctionTable(FunctionTable *table, FunctionEntry *entry);

FunctionEntry *findFunctionEntry(FunctionTable *table, const char *functionName);

void checkTypeCompatibility(OperationTreeNode *lValueExprNode, OperationTreeNode *rValueExprNode, OperationTreeErrorContainer *container, const char* filename);