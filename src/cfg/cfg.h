#pragma once

#include "../grammar/myLang.h"
#include "tokens.h"
#include "ot/ot.h"
#include "cg/cg.h"
#include <stdint.h>


#define INITIAL_CAPACITY 4

typedef enum {
    CONDITIONAL,
    UNCONDITIONAL,
    TERMINAL 
} BlockType;

typedef enum {
    TRUE_CONDITION,
    FALSE_CONDITION,
    UNCONDITIONAL_JUMP,
} EdgeType;

typedef struct {
    char *text;
    OperationTreeNode *otRoot;
} Instruction;

struct BasicBlock;

typedef struct __attribute__((packed)) Edge {
    EdgeType type;
    char *condition; // NULL for unconditional
    struct BasicBlock *fromBlock;
    struct BasicBlock *targetBlock;
    struct Edge *nextOut;
    struct Edge *nextIn;
} Edge;

typedef struct BasicBlock {
    int id;
    BlockType type;
    Instruction *instructions;
    int instructionCount;
    int instructionCapacity;
    char *name;
    bool isEmpty;
    bool isBreak;
    Edge *outEdges;
    Edge *inEdges;
    struct BasicBlock *next;
} BasicBlock;

typedef struct {
    BasicBlock *entryBlock;
    BasicBlock *blocks;
} CFG;

typedef struct __attribute__((packed)) FunctionInfo {
    char *fileName;
    char *functionName;
    TypeInfo *returnType;
    ArgumentInfo *arguments;
    CFG *cfg;
    bool isVarargs;
    bool isBuiltin;
    bool isPrivate;
    bool isStatic;
    bool isConstructor;
    bool isOverride;
    struct FunctionInfo *next;
    uint32_t line;
    uint32_t pos;
} FunctionInfo;

typedef struct FilesToAnalyze {
    uint32_t filesCount;
    char **fileName;
    MyLangResult **result;
} FilesToAnalyze;

typedef struct __attribute__((packed)) ProgramErrorInfo {
    char *message;
    struct ProgramErrorInfo *next;
} ProgramErrorInfo;

typedef struct __attribute__((packed)) ProgramWarningInfo {
    char *message;
    struct ProgramWarningInfo *next;
} ProgramWarningInfo;

typedef struct Program {
    FunctionInfo *functions;
    FunctionTable *functionTable;
    ProgramErrorInfo *errors;
    ProgramWarningInfo *warnings;
} Program;

typedef struct ClassProgram {
    ClassInfo* classes;
} ClassProgram;

BasicBlock* createBasicBlock(int id, BlockType type, const char *name);

void addInstruction(BasicBlock *block, const char *text, OperationTreeNode *otRoot);

void addEdge(BasicBlock *from, BasicBlock *to, EdgeType type, const char *condition);

void addBasicBlock(CFG *cfg, BasicBlock *block);

CFG* createCFG();

void printCFG(CFG *cfg);

void freeInstructions(BasicBlock *block);

void freeOutEdges(Edge *edge);

void freeBasicBlocks(BasicBlock *block);

void freeCFG(CFG *cfg);

TypeInfo* createTypeInfo(const char *typeName, bool custom, bool isArray, uint32_t arrayDim, uint32_t line, uint32_t pos);

void freeTypeInfo(TypeInfo *typeInfo);

ArgumentInfo* createArgumentInfo(TypeInfo *type, const char *name, uint32_t line, uint32_t pos);

void addArgument(FunctionInfo *funcInfo, ArgumentInfo *argInfo);

void freeArguments(ArgumentInfo *arg);

void addFunctionToProgram(Program *program, FunctionInfo *funcInfo);

void freeProgram(Program *program);

FunctionInfo* createFunctionInfo(const char *fileName, const char *functionName, TypeInfo *returnType, uint32_t line, uint32_t pos);

void freeFunctionInfo(FunctionInfo *funcInfo);

void printFunctionInfo(FunctionInfo *funcInfo);

ClassProgram* buildClassProgram(FilesToAnalyze *files, bool debug);

ProgramErrorInfo* createProgramErrorInfo(const char *message);

void addProgramError(Program *program, ProgramErrorInfo *errorInfo);

void freeProgramErrors(ProgramErrorInfo *error);

ProgramWarningInfo* createProgramWarningInfo(const char *message);

void addProgramWarning(Program *program, ProgramWarningInfo *errorInfo);

void freeProgramWarnings(ProgramWarningInfo *error);

void writeCFGToDotFile(CFG *cfg, const char *filename, bool drawOt);

void traverseProgramAndBuildCallGraph(Program *program, CallGraph *cg, bool debug);

ClassInfo* createClassInfo(const char* name, const char* parentName, const char** interfaceNames, int interfaceCount, MyAstNode* classBody, char* fileName, uint64_t typeId);

void freeClassInfo(ClassInfo* info);

ClassProgram* createClassProgram();

void addClassInfo(ClassProgram* program, ClassInfo* classInfo);

void freeClassProgram(ClassProgram* program);

void printAllClassesInfo(ClassInfo* head);

FieldInfo *createFieldInfo(TypeInfo *type, const char *name, uint32_t line, uint32_t pos);
  
void addField(ClassInfo *classInfo, FieldInfo *fieldInfo);

void freeField(FieldInfo *field);

ClassVtable *createVtable();

void addVtableEntry(ClassVtable *vtable, const char *functionName, const char *className, bool isBuiltin);

void freeVtable(ClassVtable *vtable);

void prepareClassVtable(ClassInfo *classInfo, ClassInfo *classes);

void prepareClassVtableHelper(ClassInfo *classInfo, ClassInfo *classes, ClassVtable *vtable);

void printVtable(const ClassVtable *vtable);

void prepareOffset(ClassVtable *vtable, size_t *outCount);