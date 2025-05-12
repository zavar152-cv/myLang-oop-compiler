#include "cfg.h"
#include "../grammar/ast/myAst.h"
#include "ot/ot.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../grammar/myLang.h"
#include "scope/scope.h"
#include "../asm/symbols.h"

BasicBlock *parseBlock(MyAstNode* block, Program *program, const char* filename, bool isLoop, BasicBlock* prevBlock, BasicBlock* existingBlock, BasicBlock* loopBlock, CFG *cfg, ScopeManager *sm, ClassInfo *classes, ClassInfo *currentClass, FunctionTable *functionTable, uint32_t *uid);

BasicBlock *createBasicBlock(int id, BlockType type, const char *name) {
  BasicBlock *block = (BasicBlock *)malloc(sizeof(BasicBlock));
  block->id = id;
  block->type = type;
  block->instructionCount = 0;
  block->instructionCapacity = INITIAL_CAPACITY;
  block->instructions =
      (Instruction *)malloc(sizeof(Instruction) * block->instructionCapacity);
  block->outEdges = NULL;
  block->inEdges = NULL;
  block->next = NULL;
  block->name = strdup(name);
  block->isEmpty = false;
  block->isBreak = false;
  return block;
}

BasicBlock *createEmptyBasicBlock(int id, BlockType type, const char *name) {
  BasicBlock *block = createBasicBlock(id, type, name);
  block->isEmpty = true;
  return block;
}

void addInstruction(BasicBlock *block, const char *text, OperationTreeNode *otRoot) {
  if (block->instructionCount >= block->instructionCapacity) {
    block->instructionCapacity *= 2;
    block->instructions = (Instruction *)realloc(
        block->instructions, sizeof(Instruction) * block->instructionCapacity);
  }
  block->instructions[block->instructionCount].text = strdup(text);
  block->instructions[block->instructionCount].otRoot = otRoot;
  block->instructionCount++;

  if (block->isEmpty) {
    block->isEmpty = false;
  }

}

void addEdge(BasicBlock *from, BasicBlock *to, EdgeType type,
             const char *condition) {
  if (!from->isBreak) {
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->type = type;
    if (condition != NULL) {
      edge->condition = strdup(condition);
    } else {
      edge->condition = NULL;
    }
    edge->fromBlock = from;
    edge->targetBlock = to;

    edge->nextOut = from->outEdges;
    from->outEdges = edge;

    edge->nextIn = to->inEdges;
    to->inEdges = edge;
  }
}

void addBasicBlock(CFG *cfg, BasicBlock *block) {
  block->next = cfg->blocks;
  cfg->blocks = block;
}

void printClassInfoTable(ClassInfo* head) {
  printf("%-20s %-15s %-10s %-11s %-20s %-18s %s\n", 
      "Class Name", "Parent", "IntfCount", "IsInterface", "File Name", "Type ID", "Interfaces");

  printf("---------------------------------------------------------------------------------------------------------------\n");

  for (ClassInfo* cls = head; cls != NULL; cls = cls->next) {
  printf("%-20s %-15s %-10d %-11s %-20s 0x%016llx ", 
          cls->name ? cls->name : "NULL",
          cls->parentName ? cls->parentName : "None",
          cls->interfaceCount,
          cls->isInterface ? "true" : "false",
          cls->fileName ? cls->fileName : "NULL",
          (unsigned long long)cls->typeId);

  if (cls->interfaceNames && cls->interfaceCount > 0) {
      for (int i = 0; i < cls->interfaceCount; ++i) {
          printf("%s%s", cls->interfaceNames[i], (i < cls->interfaceCount - 1) ? ", " : "");
      }
  } else {
      printf("None");
  }

  printf("\n");
  }
}

void printFunctionInfoTable(const ClassInfo* cls) {
  if (!cls->program || !cls->program->functions) {
      printf("\nNo functions found for class %s.\n", cls->name);
      return;
  }

  printf("\nFunctions of class %s:\n", cls->name);
  printf("%-20s %-15s %-10s %-10s %-10s %-10s %-10s %-11s %-9s %-9s\n", 
         "Function Name", "Return Type", "Varargs", "Builtin", "Private", "Static", "Override", "Constructor", "Line", "Pos");

  printf("------------------------------------------------------------------------------------------------------------------------\n");

  for (FunctionInfo* fn = cls->program->functions; fn != NULL; fn = fn->next) {
      printf("%-20s %-15s %-10s %-10s %-10s %-10s %-10s %-11s %-9u %-9u\n",
             fn->functionName ? fn->functionName : "NULL",
             fn->returnType && fn->returnType->typeName ? fn->returnType->typeName : "void",
             fn->isVarargs ? "true" : "false",
             fn->isBuiltin ? "true" : "false",
             fn->isPrivate ? "true" : "false",
             fn->isStatic ? "true" : "false",
             fn->isOverride ? "true" : "false",
             fn->isConstructor ? "true" : "false",
             fn->line,
             fn->pos);
  }
}


void printFieldInfoTable(const ClassInfo* cls) {
  printf("\nFields of class %s:\n", cls->name);
  printf("%-20s %-15s %-10s %-10s %-5s %-5s %-10s\n", 
         "Field Name", "Type", "Private", "Static", "Line", "Pos", "Offset");

  printf("------------------------------------------------------------------------------------------------------------------------\n");

  for (FieldInfo* field = cls->fields; field != NULL; field = field->next) {
      printf("%-20s %-15s %-10s %-10s %-5u %-5u %-10lld\n", 
             field->name ? field->name : "NULL",
             field->type && field->type->typeName ? field->type->typeName : "NULL",
             field->isPrivate ? "true" : "false",
             field->isStatic ? "true" : "false",
             field->line,
             field->pos,
             (long long)field->offset);
  }
}

void printAllClassesInfoTable(ClassInfo* head) {
  printClassInfoTable(head);

  for (ClassInfo* cls = head; cls != NULL; cls = cls->next) {
      printFieldInfoTable(cls);
      printFunctionInfoTable(cls);
      printVtable(cls->vtable);
  }
}

TypeInfo* parseTyperef(MyAstNode* typeRef) {
  assert(typeRef->childCount == 1 || typeRef->childCount == 2 || typeRef->childCount >= 3);

  if (typeRef->childCount == 1) {
    MyAstNode* type = typeRef->children[0];
    return createTypeInfo(type->children[0]->label, strcmp(type->label, CUSTOM_TYPE) == 0, false, 0, type->children[0]->line, type->children[0]->pos);
  } else if (typeRef->childCount == 2) {
    MyAstNode* type = typeRef->children[0];
    assert(strcmp(typeRef->children[1]->label, ARRAY) == 0);
    uint32_t dim = typeRef->children[1]->childCount == 1 ? typeRef->children[1]->children[0]->childCount + 1 : 1;
    return createTypeInfo(type->children[0]->label, strcmp(type->label, CUSTOM_TYPE) == 0, true, dim, type->children[0]->line, type->children[0]->pos);
  } else if (typeRef->childCount >= 3) {
    MyAstNode* type = typeRef->children[0];
    assert(strcmp(typeRef->children[1]->label, ARRAY) == 0);
    if (strcmp(typeRef->children[typeRef->childCount - 1]->label, TYPEREF) == 0) {
      uint32_t dim = 0;
      for (uint32_t i = 1; i < typeRef->childCount - 1; i++) {
        dim = dim + (typeRef->children[i]->childCount == 1 ? typeRef->children[i]->children[0]->childCount + 1 : 1);
      }
      TypeInfo *next = parseTyperef(typeRef->children[typeRef->childCount - 1]);
      TypeInfo *finalType = createTypeInfo(type->children[0]->label, strcmp(type->label, CUSTOM_TYPE) == 0, true, dim, type->children[0]->line, type->children[0]->pos);
      finalType->next = next;
      return finalType;
    } else {
      uint32_t dim = 0;
      for (uint32_t i = 1; i < typeRef->childCount; i++) {
        dim = dim + (typeRef->children[i]->childCount == 1 ? typeRef->children[i]->children[0]->childCount + 1 : 1);
      }
      TypeInfo *finalType = createTypeInfo(type->children[0]->label, strcmp(type->label, CUSTOM_TYPE) == 0, true, dim, type->children[0]->line, type->children[0]->pos);
      return finalType;      
    }
  }
}

void parseArgdefList(MyAstNode* argdefList, FunctionInfo* info, Program *program, const char* filename) {
  if (argdefList->childCount == 0) {
    return;
  } else {
    bool isVarargs = false;
    if (strcmp(argdefList->children[argdefList->childCount - 1]->label, VARARGS) == 0) {
      isVarargs = true;
    }
    ArgumentInfo* arg;
    for (uint32_t i = 0; i < argdefList->childCount - (isVarargs ? 1 : 0); i++) {
      assert(strcmp(argdefList->children[i]->children[0]->label, TYPEREF) == 0);
      assert(strcmp(argdefList->children[i]->children[1]->label, IDENTIFIER) == 0);
      TypeInfo* argType = parseTyperef(argdefList->children[i]->children[0]);
      arg = createArgumentInfo(argType, argdefList->children[i]->children[1]->children[0]->label, 
      argdefList->children[i]->children[1]->children[0]->line, argdefList->children[i]->children[1]->children[0]->pos);
      addArgument(info, arg);
    }
    if (isVarargs) {
      arg->isVarargs = true;
      arg->type->isVarargs = true;
      info->isVarargs = true;
    }
  }
}

void parseVar(MyAstNode* var, BasicBlock *currentBlock, Program *program, const char* filename, ScopeManager *sm, ClassInfo* classes, ClassInfo *currentClass, FunctionTable *functionTable) {
  OperationTreeErrorContainer *errorContainer = (OperationTreeErrorContainer*)malloc(sizeof(OperationTreeErrorContainer));
  errorContainer->error = NULL;
  TypeInfo *typeInfo = parseTyperef(var->children[0]);
  OperationTreeNode *otNode = buildVarOperationTreeFromAstNode(var, errorContainer, typeInfo, sm, functionTable, classes, currentClass, filename);
  addInstruction(currentBlock, var->label, otNode);
  freeTypeInfo(typeInfo);

  OperationTreeErrorInfo *errorInfo = errorContainer->error;
  while (errorInfo != NULL) {
    ProgramErrorInfo* error = createProgramErrorInfo(errorInfo->message);
    addProgramError(program, error);
    errorInfo = errorInfo->next;
  }
  freeOperationTreeErrors(errorContainer->error);
  free(errorContainer);
}

void parseExpr(MyAstNode* expr, BasicBlock *currentBlock, Program *program, ScopeManager *sm, FunctionTable *functionTable, ClassInfo* classes, ClassInfo *currentClass, const char* filename) {
  assert(strcmp(expr->label, EXPR) == 0);
  OperationTreeErrorContainer *errorContainer = (OperationTreeErrorContainer*)malloc(sizeof(OperationTreeErrorContainer));
  errorContainer->error = NULL;
  OperationTreeNode *otNode = buildExprOperationTreeFromAstNode(expr->children[0], false, false, false, errorContainer, sm, functionTable, classes, currentClass, filename);
  addInstruction(currentBlock, expr->children[0]->label, otNode);

  OperationTreeErrorInfo *errorInfo = errorContainer->error;
  while (errorInfo != NULL) {
    ProgramErrorInfo* error = createProgramErrorInfo(errorInfo->message);
    addProgramError(program, error);
    errorInfo = errorInfo->next;
  }
  freeOperationTreeErrors(errorContainer->error);
  free(errorContainer);
}

void mergeBasicBlocks(CFG *cfg, BasicBlock *block1, BasicBlock *block2) {
    if (block1 == NULL || block2 == NULL) {
        fprintf(stderr, "mergeBasicBlocks: One block is NULL.\n");
        return;
    }

    int originalCount = block1->instructionCount;
    block1->instructionCount += block2->instructionCount;
    block1->instructions = realloc(block1->instructions, sizeof(Instruction) * block1->instructionCount);
    if (block1->instructions == NULL) {
        fprintf(stderr, "mergeBasicBlocks: Can't realloc memory for instructions.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(block1->instructions + originalCount, block2->instructions, sizeof(Instruction) * block2->instructionCount);

    Edge *inEdge = block2->inEdges;
    while (inEdge != NULL) {
        inEdge->targetBlock = block1;
        inEdge = inEdge->nextIn;
    }

    Edge *outEdge = block2->outEdges;
    while (outEdge != NULL) {
        outEdge->fromBlock = block1;
        outEdge = outEdge->nextOut;
    }
    BasicBlock *prev = NULL;
    BasicBlock *current = cfg->blocks;
    while (current != NULL && current != block2) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        fprintf(stderr, "mergeBasicBlocks: block2 is not in CFG.\n");
        return;
    }

    if (prev == NULL) {
        cfg->blocks = block2->next;
    } else {
        prev->next = block2->next;
    }

    for (int i = 0; i < block2->instructionCount; i++) {
        free(block2->instructions[i].text);
    }
    free(block2->instructions);
    free(block2->name);
    free(block2);
}

BasicBlock* parseDoWhile(MyAstNode* doWhileBlock, Program *program, const char* filename, BasicBlock* prevBlock, BasicBlock* existingBlock, BasicBlock* loopExitBlock, CFG *cfg, ScopeManager *sm, ClassInfo *classes, ClassInfo *currentClass, FunctionTable *functionTable, uint32_t *uid) {
  assert(strcmp(doWhileBlock->label, DO_WHILE) == 0);
  BasicBlock *bodyBlock;
  if (existingBlock == NULL) {
    bodyBlock = createBasicBlock(++(*uid), UNCONDITIONAL, "Do While body");
    addBasicBlock(cfg, bodyBlock);
    addEdge(prevBlock, bodyBlock, UNCONDITIONAL_JUMP, NULL);
  } else {
    bodyBlock = existingBlock;
    free(bodyBlock->name);
    bodyBlock->name = strdup("Do While body");
  }

  BasicBlock *emptyBlock = createEmptyBasicBlock(++(*uid), UNCONDITIONAL, "Empty block");
  addBasicBlock(cfg, emptyBlock);

  BasicBlock *conditionBlock = createBasicBlock(++(*uid), CONDITIONAL, "Do While Condition");
  addBasicBlock(cfg, conditionBlock);

  OperationTreeErrorContainer *errorContainer = (OperationTreeErrorContainer*)malloc(sizeof(OperationTreeErrorContainer));
  errorContainer->error = NULL;
  OperationTreeNode *otNode = buildExprOperationTreeFromAstNode(doWhileBlock->children[1]->children[0], false, false, false, errorContainer, sm, functionTable, classes, currentClass, filename);
  addInstruction(conditionBlock, doWhileBlock->children[1]->label, otNode);

  OperationTreeErrorInfo *errorInfo = errorContainer->error;
  while (errorInfo != NULL) {
    ProgramErrorInfo* error = createProgramErrorInfo(errorInfo->message);
    addProgramError(program, error);
    errorInfo = errorInfo->next;
  }
  freeOperationTreeErrors(errorContainer->error);
  free(errorContainer);

  addEdge(conditionBlock, bodyBlock, TRUE_CONDITION, NULL);
  addEdge(conditionBlock, emptyBlock, FALSE_CONDITION, NULL);

  BasicBlock *bodyExitBlock = parseBlock(doWhileBlock->children[0], program, filename, true, conditionBlock, bodyBlock, conditionBlock, cfg, sm, classes, currentClass, functionTable, uid);

  addEdge(bodyExitBlock, conditionBlock, UNCONDITIONAL_JUMP, NULL);

  return emptyBlock;
}

BasicBlock* parseWhile(MyAstNode* whileBlock, Program *program, const char* filename, BasicBlock* prevBlock, BasicBlock* existingBlock, BasicBlock* loopExitBlock, CFG *cfg, ScopeManager *sm, ClassInfo *classes, ClassInfo *currentClass, FunctionTable *functionTable, uint32_t *uid) {
    assert(strcmp(whileBlock->label, WHILE) == 0);

    BasicBlock *conditionBlock;            
    if (existingBlock == NULL) {
      conditionBlock = createBasicBlock(++(*uid), CONDITIONAL, "While Condition");
      addBasicBlock(cfg, conditionBlock);
      addEdge(prevBlock, conditionBlock, UNCONDITIONAL_JUMP, NULL);
    } else {
      conditionBlock = existingBlock;
      free(conditionBlock->name);
      conditionBlock->name = strdup("While Condition");
      conditionBlock->type = CONDITIONAL;
    }


    BasicBlock *emptyBlock = createEmptyBasicBlock(++(*uid), UNCONDITIONAL, "Empty block");
    addBasicBlock(cfg, emptyBlock);

    OperationTreeErrorContainer *errorContainer = (OperationTreeErrorContainer*)malloc(sizeof(OperationTreeErrorContainer));
    errorContainer->error = NULL;
    OperationTreeNode *otNode = buildExprOperationTreeFromAstNode(whileBlock->children[0]->children[0], false, false, false, errorContainer, sm, functionTable, classes, currentClass, filename);
    addInstruction(conditionBlock, whileBlock->children[0]->label, otNode);

    OperationTreeErrorInfo *errorInfo = errorContainer->error;
    while (errorInfo != NULL) {
      ProgramErrorInfo* error = createProgramErrorInfo(errorInfo->message);
      addProgramError(program, error);
      errorInfo = errorInfo->next;
    }
    freeOperationTreeErrors(errorContainer->error);
    free(errorContainer);

    BasicBlock *bodyBlock = createBasicBlock(++(*uid), UNCONDITIONAL, "While Body");
    addBasicBlock(cfg, bodyBlock);

    addEdge(conditionBlock, bodyBlock, TRUE_CONDITION, NULL);
    addEdge(conditionBlock, emptyBlock, FALSE_CONDITION, NULL);

    BasicBlock *bodyExitBlock = parseBlock(whileBlock->children[1], program, filename, true, conditionBlock, bodyBlock, emptyBlock, cfg, sm, classes, currentClass, functionTable, uid);

    addEdge(bodyExitBlock, conditionBlock, UNCONDITIONAL_JUMP, NULL);

    return emptyBlock;
}

BasicBlock *parseIf(MyAstNode* ifBlock, Program *program, const char* filename, bool isLoop, BasicBlock* prevBlock, BasicBlock* existingBlock, BasicBlock* loopExitBlock, CFG *cfg, ScopeManager *sm, ClassInfo *classes, ClassInfo *currentClass, FunctionTable *functionTable, uint32_t *uid) {
    assert(strcmp(ifBlock->label, IF) == 0);

    BasicBlock *conditionBlock;
    if (existingBlock == NULL) {
      conditionBlock = createBasicBlock(++(*uid), CONDITIONAL, "If Condition");
      addBasicBlock(cfg, conditionBlock);
      addEdge(prevBlock, conditionBlock, UNCONDITIONAL_JUMP, NULL);
    } else {
      conditionBlock = existingBlock;
      free(conditionBlock->name);
      conditionBlock->name = strdup("If Condition");
      conditionBlock->type = CONDITIONAL;
    }

    BasicBlock *emptyBlock = createEmptyBasicBlock(++(*uid), UNCONDITIONAL, "Empty block");
    addBasicBlock(cfg, emptyBlock);

    OperationTreeErrorContainer *errorContainer = (OperationTreeErrorContainer*)malloc(sizeof(OperationTreeErrorContainer));
    errorContainer->error = NULL;
    OperationTreeNode *otNode = buildExprOperationTreeFromAstNode(ifBlock->children[0]->children[0], false, false, false, errorContainer, sm, functionTable, classes, currentClass, filename);
    addInstruction(conditionBlock, ifBlock->children[0]->label, otNode);

    OperationTreeErrorInfo *errorInfo = errorContainer->error;
    while (errorInfo != NULL) {
      ProgramErrorInfo* error = createProgramErrorInfo(errorInfo->message);
      addProgramError(program, error);
      errorInfo = errorInfo->next;
    }
    freeOperationTreeErrors(errorContainer->error);
    free(errorContainer);

    BasicBlock *thenBlock = createBasicBlock(++(*uid), UNCONDITIONAL, "Then Block");
    addBasicBlock(cfg, thenBlock);

    BasicBlock *elseBlock = NULL;
    if (ifBlock->childCount == 3) {
        assert(strcmp(ifBlock->children[2]->label, ELSE) == 0);
        elseBlock = createBasicBlock(++(*uid), UNCONDITIONAL, "Else Block");
        addBasicBlock(cfg, elseBlock);
    }

    addEdge(conditionBlock, thenBlock, TRUE_CONDITION, NULL);
    if (elseBlock != NULL) {
        addEdge(conditionBlock, elseBlock, FALSE_CONDITION, NULL);
    } else {
        addEdge(conditionBlock, emptyBlock, FALSE_CONDITION, NULL);
    }

    BasicBlock *thenExitBlock = parseBlock(ifBlock->children[1], program, filename, isLoop, conditionBlock, thenBlock, loopExitBlock, cfg, sm, classes, currentClass, functionTable, uid);

    addEdge(thenExitBlock, emptyBlock, UNCONDITIONAL_JUMP, NULL);

    if (elseBlock != NULL) {
        BasicBlock *elseExitBlock = parseBlock(ifBlock->children[2]->children[0], program, filename, isLoop, conditionBlock, elseBlock, loopExitBlock, cfg, sm, classes, currentClass, functionTable, uid);
        addEdge(elseExitBlock, emptyBlock, UNCONDITIONAL_JUMP, NULL);
    }
    return emptyBlock;
}

BasicBlock *parseBlock(MyAstNode* block, Program *program, const char* filename, bool isLoop, BasicBlock* prevBlock, BasicBlock* existingBlock, BasicBlock* loopExitBlock, CFG *cfg, ScopeManager *sm, ClassInfo *classes, ClassInfo *currentClass, FunctionTable *functionTable, uint32_t *uid) {
  //assert(strcmp(block->label, BLOCK) == 0);
  enterScope(sm);
  BasicBlock *currentBlock;
  if (existingBlock == NULL) {
    currentBlock = createEmptyBasicBlock(++(*uid), UNCONDITIONAL, "Empty block");
    addBasicBlock(cfg, currentBlock);
    addEdge(prevBlock, currentBlock, UNCONDITIONAL_JUMP, NULL);
  } else {
    currentBlock = existingBlock;
  }

  //bad idea! But this is to maintain back-compatibility for handling non-BLOCK cases.
  bool fakeNodeCreated = false;
  MyAstNode* fakeNode = NULL;
  if (strcmp(block->label, BLOCK) != 0) {
    fakeNode = newMyAstNode("BLOCK", 1, block->line, block->pos, true);
    fakeNode->children[0] = block;
    block = fakeNode;
    fakeNodeCreated = true;
  }

  for (uint32_t i = 0; i < block->childCount; i++) {
    if (currentBlock->isEmpty) {
      free(currentBlock->name);
      currentBlock->name = strdup("Base block");
    }
    if (strcmp(block->children[i]->label, VAR) == 0) {
      parseVar(block->children[i], currentBlock, program, filename, sm, classes, currentClass, functionTable);
    } else if (strcmp(block->children[i]->label, BLOCK) == 0) {
      BasicBlock *toExistingBlock = currentBlock->isEmpty ? currentBlock : NULL;
      BasicBlock *nestedExitBlock = parseBlock(block->children[i], program, filename, isLoop, currentBlock, toExistingBlock, loopExitBlock, cfg, sm, classes, currentClass, functionTable, uid);
      currentBlock = nestedExitBlock;
    } else if (strcmp(block->children[i]->label, IF) == 0) {
      BasicBlock *toExistingBlock = currentBlock->isEmpty ? currentBlock : NULL;
      BasicBlock *nestedExitBlock = parseIf(block->children[i], program, filename, isLoop, currentBlock, toExistingBlock, loopExitBlock, cfg, sm, classes, currentClass, functionTable, uid);
      currentBlock = nestedExitBlock;
    } else if (strcmp(block->children[i]->label, WHILE) == 0) {
      BasicBlock *toExistingBlock = currentBlock->isEmpty ? currentBlock : NULL;
      BasicBlock *nestedExitBlock = parseWhile(block->children[i], program, filename, currentBlock, toExistingBlock, loopExitBlock, cfg, sm, classes, currentClass, functionTable, uid);
      currentBlock = nestedExitBlock;
    } else if (strcmp(block->children[i]->label, DO_WHILE) == 0) {
      BasicBlock *toExistingBlock = currentBlock->isEmpty ? currentBlock : NULL;
      BasicBlock *nestedExitBlock = parseDoWhile(block->children[i], program, filename, currentBlock, toExistingBlock, loopExitBlock, cfg, sm, classes, currentClass, functionTable, uid);
      currentBlock = nestedExitBlock;      
    } else if (strcmp(block->children[i]->label, BREAK) == 0) {
      OperationTreeNode *breakOtNode = newOperationTreeNode(OT_BREAK, 0, block->children[i]->children[0]->line, block->children[i]->children[0]->pos, false);
      addInstruction(currentBlock, block->children[i]->children[0]->label, breakOtNode);
      if (isLoop) {
        addEdge(currentBlock, loopExitBlock, UNCONDITIONAL_JUMP, NULL);
        currentBlock->isBreak = true;
        if (i < block->childCount - 1) {
          char buffer[1024];

          snprintf(buffer, sizeof(buffer),
            "Control error. Unreachable code after break at %s:%d:%d\n",
            filename, block->children[i]->children[0]->line, block->children[i]->children[0]->pos + 1);
          ProgramErrorInfo* error = createProgramErrorInfo(buffer);
          addProgramError(program, error);
          break;
        }
      } else {
        char buffer[1024];

        snprintf(buffer, sizeof(buffer),
          "Control error. Break at %s:%d:%d is out of loop\n",
          filename, block->children[i]->children[0]->line, block->children[i]->children[0]->pos + 1);
        ProgramErrorInfo* error = createProgramErrorInfo(buffer);
        addProgramError(program, error);
      }
    } else if (strcmp(block->children[i]->label, EXPR) == 0) {
      parseExpr(block->children[i], currentBlock, program, sm, functionTable, classes, currentClass, filename);
    }
  }

  if (fakeNodeCreated) {
    free(fakeNode->children);
    free((void *)fakeNode->label);
    free(fakeNode);
  }

  exitScope(sm);

  return currentBlock;
}

bool prepareClassDeclaration(ClassInfo *classInfo, MyAstNode* classBody, char *fileName, bool debug, bool isInterface) {
  classInfo->program = (Program *)malloc(sizeof(Program));
  classInfo->program->functions = NULL;
  classInfo->program->functionTable = NULL;
  classInfo->program->errors = NULL;
  classInfo->program->warnings = NULL;
  FunctionTable *functionTable = createFunctionTable();
  classInfo->program->functionTable = functionTable;
  bool redef = false;

  MyAstNode** funcDefs = classBody->children;
  uint32_t childCount = classBody->childCount;
  bool constructorFound = false;
  uint32_t cLine = 0;
  uint32_t cPos = 0;
  for (uint32_t j = 0; j < childCount; j++) {
    if (strcmp(funcDefs[j]->label, FIELD) == 0) {
      assert(strcmp(funcDefs[j]->children[0]->label, ACCESS_MODIFIER) == 0);
      bool isPrivate = strcmp("private", funcDefs[j]->children[0]->children[0]->label) == 0;
      bool isStatic = funcDefs[j]->children[0]->childCount == 2 && strcmp("static", funcDefs[j]->children[0]->children[1]->label) == 0;
      assert(strcmp(funcDefs[j]->children[1]->label, VAR) == 0);
      MyAstNode* var = funcDefs[j]->children[1];

      for (uint32_t i = 1; i < var->childCount; i = i + 2) {
        TypeInfo *typeInfo = parseTyperef(var->children[0]);
        FieldInfo *fieldInfo = createFieldInfo(typeInfo, var->children[i]->children[0]->label, var->children[i]->children[0]->line, var->children[i]->children[0]->pos);
        fieldInfo->isPrivate = isPrivate;
        fieldInfo->isStatic = isStatic;
        addField(classInfo, fieldInfo);
      }

      continue;
    }

    MyAstNode* funcSignature;
    MyAstNode* accessModifier;
    bool isPrivate;
    bool isBuiltin;
    bool isStatic;
    bool isConstructor;
    if (!isInterface) {
      funcSignature = funcDefs[j]->children[1];
      accessModifier = funcDefs[j]->children[0];
      assert(strcmp(funcSignature->label, FUNC_SIGNATURE) == 0);
      assert(strcmp(accessModifier->label, ACCESS_MODIFIER) == 0);
  
      isPrivate = strcmp("private", accessModifier->children[0]->label) == 0;
      isBuiltin = false;
      isStatic = false;
      isConstructor = false;
  
      if (accessModifier->childCount == 2) {
        if (strcmp(COMPILER, accessModifier->children[1]->label) == 0) {
          isBuiltin = true;
        } else if (strcmp(STATIC, accessModifier->children[1]->label) == 0) {
          isStatic = true;
        }
      } else if (accessModifier->childCount == 3) {
        //bad but works
        isBuiltin = true;
        isStatic = true;
      }
    } else {
      funcSignature = funcDefs[j]->children[0];
      assert(strcmp(funcSignature->label, FUNC_SIGNATURE) == 0);
      isPrivate = false;
      isBuiltin = false;
      isStatic = false;
      isConstructor = false;
    }

    MyAstNode* typeRef = NULL;
    MyAstNode* name = NULL;
    MyAstNode* argdefList = NULL;

    assert(funcSignature->childCount == 3 || funcSignature->childCount == 2);

    if (funcSignature->childCount == 2) {
      name = funcSignature->children[0];
      argdefList = funcSignature->children[1];
      assert(strcmp(name->label, NAME) == 0);
      assert(strcmp(argdefList->label, ARGDEF_LIST) == 0);
    } else if (funcSignature->childCount == 3) {
      typeRef = funcSignature->children[0];
      name = funcSignature->children[1];
      argdefList = funcSignature->children[2];
      assert(strcmp(typeRef->label, TYPEREF) == 0);
      assert(strcmp(name->label, NAME) == 0);
      assert(strcmp(argdefList->label, ARGDEF_LIST) == 0);
    }

    TypeInfo* returnType;
    if (typeRef == NULL) {
      returnType = createTypeInfo("_", false, false, 0, name->line, name->pos);
    } else {
      returnType = parseTyperef(typeRef);
    }


    FunctionInfo* info = createFunctionInfo(fileName, name->children[0]->label, returnType, name->children[0]->line, name->children[0]->pos);
    parseArgdefList(argdefList, info, classInfo->program, fileName);
    
    if (typeRef == NULL && strcmp(name->children[0]->label, classInfo->name) == 0) {
      if (!constructorFound) {
        constructorFound = true;
        isConstructor = true;
        cLine = info->line;
        cPos = info->pos;
        freeTypeInfo(info->returnType);
        info->returnType = createTypeInfo(name->children[0]->label, true, false, 0, name->line, name->pos);
        if (isBuiltin || isStatic || isPrivate) {
          char buffer[1024];
          snprintf(buffer, sizeof(buffer),
            "Constructor error. Constructor of '%s' at %s:%d:%d can't be builtin, static or private\n",
            classInfo->name, info->fileName, info->line, info->pos + 1);
          ProgramErrorInfo* error = createProgramErrorInfo(buffer);
          addProgramError(classInfo->program, error);
        }
        if (isInterface) {
          char buffer[1024];
          snprintf(buffer, sizeof(buffer),
            "Constructor error. Constructor of '%s' at %s:%d:%d isn't allowed in interfaces\n",
            classInfo->name, info->fileName, info->line, info->pos + 1);
          ProgramErrorInfo* error = createProgramErrorInfo(buffer);
          addProgramError(classInfo->program, error);
        }
      } else {
        isConstructor = false;
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
          "Constructor error. Constructor of '%s' at %s:%d:%d was previously declared at %s:%d:%d\n",
          classInfo->name, info->fileName, info->line, info->pos + 1,
          info->fileName, cLine, cPos + 1);
        ProgramErrorInfo* error = createProgramErrorInfo(buffer);
        addProgramError(classInfo->program, error);
      }
    }
    
    info->isBuiltin = isBuiltin;
    info->isStatic = isStatic;
    info->isPrivate = isPrivate;
    info->isConstructor = isConstructor;

    FunctionInfo *func = classInfo->program->functions;
    while (func != NULL) {
      FunctionInfo *nextFunc = func->next;
      if (strcmp(func->functionName, info->functionName) == 0) {
        char buffer[1024];
        redef = true;
        snprintf(buffer, sizeof(buffer),
          "Redeclaration error. Function '%s' at %s:%d:%d was previously declared at %s:%d:%d\n",
          info->functionName, info->fileName, info->line, info->pos + 1,
          func->fileName, func->line, func->pos + 1);
        ProgramErrorInfo* error = createProgramErrorInfo(buffer);
        addProgramError(classInfo->program, error);
        break;
      }
      func = nextFunc;
    }

    addFunctionToProgram(classInfo->program, info);
    TypeInfo *returnTypeCopy = createTypeInfo(info->returnType->typeName, info->returnType->custom, info->returnType->isArray, info->returnType->arrayDim, info->returnType->line, info->returnType->pos);
    FunctionEntry *entry = createFunctionEntry(info->fileName, info->functionName, returnTypeCopy, copyArgumentInfo(info->arguments), info->isVarargs, info->isBuiltin, info->isStatic, info->isPrivate, info->isConstructor, argdefList->childCount - (info->isVarargs ? 1 : 0), info->line, info->pos);
    addFunctionTable(functionTable, entry);
  }

  if (!constructorFound && !classInfo->isInterface) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer),
      "Constructor error. Constructor of '%s' in %s not found\n",
      classInfo->name, classInfo->fileName);
    ProgramErrorInfo* error = createProgramErrorInfo(buffer);
    addProgramError(classInfo->program, error);
  }
  return redef;
}

void prepareClassVtable(ClassInfo *classInfo, ClassInfo *classes) {
  ClassVtable *vtable = createVtable();
  prepareClassVtableHelper(classInfo, classes, vtable);
  size_t count = 0;
  prepareOffset(vtable, &count);
  classInfo->vtable = vtable;
}

void prepareClassVtableHelper(ClassInfo *classInfo, ClassInfo *classes, ClassVtable *vtable) {

  ClassInfo *parentClass = findClassWithName(classes, classInfo->parentName);

  if (parentClass != NULL && !classInfo->isInterface) {
    prepareClassVtableHelper(parentClass, classes, vtable);
  }
  FunctionEntry *functionEntry = classInfo->program->functionTable->entry;
  while (functionEntry != NULL) {

    if (functionEntry->isOverride) {
      ClassVtableEntry *currentEntry = vtable->head;

      while (currentEntry != NULL) {
        if (strcmp(currentEntry->functionName, functionEntry->functionName) == 0) {
          free(currentEntry->className);
          currentEntry->className = strdup(classInfo->name);
          break;
        }
        currentEntry = currentEntry->next;
      }

    } else {
      addVtableEntry(vtable, functionEntry->functionName, classInfo->name, functionEntry->isBuiltin);
    }
    functionEntry = functionEntry->next;
  }
}


void prepareCFGForProgram(ClassInfo *classInfo, ClassInfo* classes, MyAstNode* classBody, char *fileName, bool debug) {
    MyAstNode **funcDefs = classBody->children;
    uint32_t childCount = classBody->childCount;
    for (uint32_t j = 0; j < childCount && funcDefs[j]->childCount != 1; j++) {
      if (strcmp(funcDefs[j]->label, FIELD) == 0)
        continue;
      MyAstNode* funcSignature = funcDefs[j]->children[1];
      assert(strcmp(funcSignature->label, FUNC_SIGNATURE) == 0);
      MyAstNode* name;
      if (funcSignature->childCount == 2) {
        name = funcSignature->children[0];
        assert(strcmp(name->label, NAME) == 0);
      } else if (funcSignature->childCount == 3) {
        name = funcSignature->children[1];
        assert(strcmp(name->label, NAME) == 0);
      }

      FunctionInfo *func = classInfo->program->functions;
      while (func != NULL) {
        if (strcmp(func->functionName, name->children[0]->label) == 0) {
          break;
        }
        func = func->next;
      }

      if (func->isBuiltin)
        continue;

      MyAstNode *block = funcDefs[j]->children[2];
      assert(strcmp(block->label, BLOCK) == 0);

      CFG *cfg = createCFG();
      uint32_t uid = 0;
      BasicBlock *startBlock = createBasicBlock(uid, UNCONDITIONAL, "START");
      cfg->entryBlock = startBlock;
      addBasicBlock(cfg, startBlock);

      ScopeManager sm = {NULL, 0, func->functionName};
      
      enterScope(&sm);
      FieldInfo *fieldInfo = classInfo->fields;
      while (fieldInfo != NULL) {
        addSymbol(&sm, fieldInfo->name, fieldInfo->type->typeName, fieldInfo->type->custom, fieldInfo->type->isArray, fieldInfo->type->arrayDim, fieldInfo->line, fieldInfo->pos);
        fieldInfo = fieldInfo->next;
      }
      enterScope(&sm);
      ArgumentInfo *funcArg = func->arguments;
      while (funcArg != NULL) {
        if (func->isVarargs) {
          funcArg->type->isArray = true;
          funcArg->type->arrayDim = 1;
        }
        addSymbol(&sm, funcArg->name, funcArg->type->typeName, funcArg->type->custom, funcArg->type->isArray, funcArg->type->arrayDim, funcArg->line, funcArg->pos);
        funcArg = funcArg->next;
      }
      BasicBlock *lastBlock = parseBlock(block, classInfo->program, fileName, false, startBlock, NULL, NULL, cfg, &sm, classes, classInfo, classInfo->program->functionTable, &uid);
      exitScope(&sm);
      BasicBlock *retCheckBlock;
      if (lastBlock->isEmpty) {
        lastBlock->type = TERMINAL;
        free(lastBlock->name);
        lastBlock->name = strdup("END");
        retCheckBlock = lastBlock;
      } else {
        BasicBlock *endBlock = createBasicBlock(++uid, TERMINAL, "END");
        addBasicBlock(cfg, endBlock);
        addEdge(lastBlock, endBlock, UNCONDITIONAL_JUMP, NULL);
        retCheckBlock = endBlock;
      }

      Edge *inEdge = retCheckBlock->inEdges;
      while (inEdge != NULL) {
          BasicBlock *incomingBlock = inEdge->fromBlock;
          if (incomingBlock->instructionCount > 0) {
            OperationTreeNode *lastOperation = incomingBlock->instructions[incomingBlock->instructionCount - 1].otRoot;
            if (incomingBlock->type == UNCONDITIONAL && (isBinaryOp(lastOperation->label) ||
                isUnaryOp(lastOperation->label) ||
                strcmp(lastOperation->label, OT_LIT_READ) == 0 ||
                strcmp(lastOperation->label, OT_READ) == 0 ||
                strcmp(lastOperation->label, OT_CALL) == 0 ||
                strcmp(lastOperation->label, OT_INDEX) == 0)) {
                OperationTreeNode *returnNode = newOperationTreeNode(OT_RETURN, 1, lastOperation->line, lastOperation->pos, false);
                returnNode->children[0] = lastOperation;
                returnNode->type = copyTypeInfo(func->returnType);
                incomingBlock->instructions[incomingBlock->instructionCount - 1].otRoot = returnNode;

                OperationTreeErrorContainer *errorContainer = (OperationTreeErrorContainer*)malloc(sizeof(OperationTreeErrorContainer));
                errorContainer->error = NULL;

                checkTypeCompatibility(returnNode, lastOperation, errorContainer, classes, fileName);
                OperationTreeErrorInfo *errorInfo = errorContainer->error;
                while (errorInfo != NULL) {
                  ProgramErrorInfo* error = createProgramErrorInfo(errorInfo->message);
                  addProgramError(classInfo->program, error);
                  errorInfo = errorInfo->next;
                }
                freeOperationTreeErrors(errorContainer->error);
                free(errorContainer);

                if (!(strcmp(returnNode->type->typeName, func->returnType->typeName) == 0 && (returnNode->type->isArray == func->returnType->isArray))) {
                    char buffer[1024];
                    
                    snprintf(buffer, sizeof(buffer), 
                  "Type error. Return type doesn't match function signature (%s and %s) at %s:%d:%d\n",
                          returnNode->type->typeName, func->returnType->typeName,
                          fileName, lastOperation->line, lastOperation->pos + 1);
                  ProgramErrorInfo* error = createProgramErrorInfo(buffer);
                  addProgramError(classInfo->program, error);
                }
            } else {
              if (!func->isConstructor) {
                char buffer[1024];
                
                snprintf(buffer, sizeof(buffer), 
                "No return warning. Can't use instruction at %s:%d:%d as a return value\n",
                fileName, lastOperation->line, lastOperation->pos + 1);
                ProgramWarningInfo* warning = createProgramWarningInfo(buffer);
                addProgramWarning(classInfo->program, warning);
              }
            }
          } else {
            if (!func->isConstructor) {
              char buffer[1024];

              snprintf(buffer, sizeof(buffer), 
              "No return warning. There is no instructions to use as a return value at %s:%d:%d in function '%s'\n",
              fileName, name->children[0]->line, name->children[0]->pos + 1, name->children[0]->label);
              ProgramWarningInfo* warning = createProgramWarningInfo(buffer);
              addProgramWarning(classInfo->program, warning);
            }
          }
          inEdge = inEdge->nextIn;
      }
      exitScope(&sm);
      func->cfg = cfg;
    }

    if (debug) {
      FunctionInfo *func = classInfo->program->functions;
      while (func != NULL) {
        printFunctionInfo(func);
        func = func->next;
      }
    }
}

bool equalsTypeInfo(TypeInfo *a, TypeInfo *b) {
  if (a == b) return true;
  if (a == NULL || b == NULL) return false;

  if ((a->typeName == NULL && b->typeName != NULL) || 
      (a->typeName != NULL && b->typeName == NULL)) {
      return false;
  }

  if (a->typeName && b->typeName && strcmp(a->typeName, b->typeName) != 0)
      return false;

  return a->custom == b->custom &&
         a->isArray == b->isArray &&
         a->isVarargs == b->isVarargs;
}

bool equalsArgumentList(ArgumentInfo *a, ArgumentInfo *b) {
  while (a != NULL && b != NULL) {
      if ((a->name == NULL && b->name != NULL) ||
          (a->name != NULL && b->name == NULL)) {
          return false;
      }

      if (a->name && b->name && strcmp(a->name, b->name) != 0) {
          return false;
      }

      if (!equalsTypeInfo(a->type, b->type)) {
          return false;
      }

      a = a->next;
      b = b->next;
  }

  return a == NULL && b == NULL;
}

ClassProgram *buildClassProgram(FilesToAnalyze *files, bool debug) {
  ClassProgram *classProgram = createClassProgram();
  uint64_t typeId = 1;
  for (uint32_t i = 0; i < files->filesCount; i++) {
    MyLangResult* result = files->result[i];
    MyAstNode** classDefs = result->tree->children;
    uint32_t childCount = result->tree->childCount;
    
    for (uint32_t j = 0; j < childCount; j++) {
      MyAstNode* class = classDefs[j];
      assert(strcmp(class->label, CLASS_DECL) == 0 || strcmp(class->label, INTERFACE_DECL) == 0);
      if (strcmp(class->label, CLASS_DECL) == 0) {
        //if 4
        //0 - NAME [value]
        //1 - EXTENDS [value]
        //2 - IMPLEMENTS [list]
        //3 - CLASS_BODY -> FIELD || METHOD

        //if 3
        //0 - NAME [value]
        //1 - EXTENDS [value] || IMPLEMENTS [list]
        //2 - CLASS_BODY -> FIELD || METHOD

        //if 2
        //0 - NAME [value]
        //1 - CLASS_BODY -> FIELD || METHOD

        //METHOD
        //0 - ACCESS_MODIFIER
        //1 - FUNC_SIGNATURE
        //2 - BLOCK
        if (class->childCount == 4) {
          MyAstNode* name = class->children[0];
          MyAstNode* extends = class->children[1];
          MyAstNode* implements = class->children[2];
          MyAstNode* classBody = class->children[3];

          assert(strcmp(name->label, NAME) == 0);
          assert(strcmp(extends->label, EXTENDS) == 0);
          assert(strcmp(implements->label, IMPLEMENTS) == 0);
          assert(strcmp(classBody->label, CLASS_BODY) == 0);

          const char **interfaces = malloc(implements->childCount * sizeof(char *));
          for (uint32_t i = 0; i < implements->childCount; i++) {
            interfaces[i] = implements->children[i]->label;
          }
          ClassInfo *classInfo = createClassInfo(name->children[0]->label, extends->children[0]->label, interfaces, implements->childCount, classBody, files->fileName[i], typeId);
          typeId++;
          addClassInfo(classProgram, classInfo);
          free(interfaces);
          prepareClassDeclaration(classInfo, classBody, files->fileName[i], debug, false);
        } else if (class->childCount == 3) {
          MyAstNode* name = class->children[0];
          MyAstNode* classBody = class->children[2];

          assert(strcmp(name->label, NAME) == 0);
          assert(strcmp(classBody->label, CLASS_BODY) == 0);

          MyAstNode* oopModifier = class->children[1];

          assert(strcmp(oopModifier->label, EXTENDS) == 0 || strcmp(oopModifier->label, IMPLEMENTS) == 0);
          ClassInfo *classInfo;
          if (strcmp(oopModifier->label, EXTENDS) == 0) {
            classInfo = createClassInfo(name->children[0]->label, oopModifier->children[0]->label, NULL, 0, classBody, files->fileName[i], typeId);
            typeId++;
            addClassInfo(classProgram, classInfo);
            prepareClassDeclaration(classInfo, classBody, files->fileName[i], debug, false);
          } else if (strcmp(oopModifier->label, IMPLEMENTS) == 0) {
            const char **interfaces = malloc(oopModifier->childCount * sizeof(char *));
            for (uint32_t i = 0; i < oopModifier->childCount; i++) {
              interfaces[i] = oopModifier->children[i]->label;
            }
            classInfo = createClassInfo(name->children[0]->label, "Object", interfaces, oopModifier->childCount, classBody, files->fileName[i], typeId);
            typeId++;
            addClassInfo(classProgram, classInfo);
            free(interfaces);
            prepareClassDeclaration(classInfo, classBody, files->fileName[i], debug, false);
          }

        } else if (class->childCount == 2) {
          MyAstNode* name = class->children[0];
          MyAstNode* classBody = class->children[1];

          assert(strcmp(name->label, NAME) == 0);
          assert(strcmp(classBody->label, CLASS_BODY) == 0);

          bool isObjectClass = strcmp(name->children[0]->label, "Object") == 0;

          ClassInfo *classInfo = createClassInfo(name->children[0]->label, isObjectClass ? NULL : "Object", NULL, 0, classBody, files->fileName[i], isObjectClass ? 0 : typeId);
          if (!isObjectClass) {
            typeId++;
          }
          addClassInfo(classProgram, classInfo);
          prepareClassDeclaration(classInfo, classBody, files->fileName[i], debug, false);
        }

      } else if (strcmp(class->label, INTERFACE_DECL) == 0) {
        //0 - NAME [value]
        //1 - INTERFACE_BODY -> METHOD

        //METHOD
        //0 - FUNC_SIGNATURE
        MyAstNode* name = class->children[0];
        MyAstNode* interfaceBody = class->children[1];

        assert(strcmp(name->label, NAME) == 0);
        assert(strcmp(interfaceBody->label, INTERFACE_BODY) == 0);
        ClassInfo *classInfo = createClassInfo(name->children[0]->label, "Object", NULL, 0, interfaceBody, files->fileName[i], typeId);
        typeId++;
        classInfo->isInterface = true;
        addClassInfo(classProgram, classInfo);
        prepareClassDeclaration(classInfo, interfaceBody, files->fileName[i], debug, true);
      }
    }
  }

  ClassInfo *classInfo = classProgram->classes;

  while (classInfo != NULL) {
    
    char *parentName = classInfo->parentName;
    ClassInfo *parentClassInfo = findClassWithName(classProgram->classes, parentName);
    uint64_t allParentFieldsCount = 0;

    while (parentClassInfo != NULL) {
      allParentFieldsCount = allParentFieldsCount + parentClassInfo->fieldsCount;
      parentClassInfo = findClassWithName(classProgram->classes, parentClassInfo->parentName);
    }

    FieldInfo *fields = classInfo->fields;

    while (fields != NULL) {
      fields->offset = fields->offset + allParentFieldsCount * 8;
      fields = fields->next;
    }
    classInfo->allParentFieldsCount = allParentFieldsCount;

    classInfo = classInfo->next;
  }

  classInfo = classProgram->classes;

  while (classInfo != NULL) {
    if (strcmp(classInfo->name, "Object") != 0) {

      bool parentFuncFound = false;
      char *parentName = classInfo->parentName;
      ClassInfo *parentClassInfo = findClassWithName(classProgram->classes, parentName);
      
      while (!parentFuncFound && strcmp(parentName, "Object") != 0) {
        if (parentClassInfo == NULL) {
          char buffer[1024];
          snprintf(buffer, sizeof(buffer),
            "Extend error. Parent '%s' of '%s' isn't exist\n", parentName, classInfo->name);
          ProgramErrorInfo* error = createProgramErrorInfo(buffer);
          addProgramError(classInfo->program, error);
          break;
        } else {
          FunctionTable *parentFuncTable = parentClassInfo->program->functionTable;
          
          FunctionEntry *parentEntry = parentFuncTable->entry;
          while (parentEntry != NULL) {
            FunctionEntry *childEntry = findFunctionEntryWithName(classInfo->program->functionTable, parentEntry->functionName);
            if (childEntry != NULL) {
              if (!(equalsArgumentList(childEntry->arguments, parentEntry->arguments) 
                    && childEntry->argumentsCount == parentEntry->argumentsCount)) {
                char buffer[1024];
                snprintf(buffer, sizeof(buffer),
                  "Override error. Parent function '%s' of '%s' has different arguments in child function '%s' of class '%s'\n", 
                  parentEntry->functionName, parentClassInfo->name, childEntry->functionName, classInfo->name);
                ProgramErrorInfo* error = createProgramErrorInfo(buffer);
                addProgramError(classInfo->program, error);
              } else if (!equalsTypeInfo(childEntry->returnType, parentEntry->returnType)) {
                char buffer[1024];
                snprintf(buffer, sizeof(buffer),
                  "Override error. Parent function '%s' of '%s' has different return type in child function '%s' of class '%s'\n", 
                  parentEntry->functionName, parentClassInfo->name, childEntry->functionName, classInfo->name);
                ProgramErrorInfo* error = createProgramErrorInfo(buffer);
                addProgramError(classInfo->program, error);
              }
              FunctionInfo *funcInfo = classInfo->program->functions;
              while (funcInfo != NULL) {
                if (strcmp(funcInfo->functionName, childEntry->functionName) == 0) {
                  funcInfo->isOverride = true;
                  parentFuncFound = true;
                  break;
                }
                funcInfo = funcInfo->next;
              }
              childEntry->isOverride = true;
            }
            parentEntry = parentEntry->next;
          }
        }
        parentClassInfo = findClassWithName(classProgram->classes, parentClassInfo->parentName);
      }

      for (int i = 0; i < classInfo->interfaceCount; i++) {
        ClassInfo *interfaceInfo = findClassWithName(classProgram->classes, classInfo->interfaceNames[i]);
        if (interfaceInfo == NULL) {
          char buffer[1024];
          snprintf(buffer, sizeof(buffer),
            "Interface error. Interface '%s' for '%s' isn't exist\n", classInfo->interfaceNames[i], classInfo->name);
          ProgramErrorInfo* error = createProgramErrorInfo(buffer);
          addProgramError(classInfo->program, error);
        } else {
          FunctionTable *interfaceFuncTable = interfaceInfo->program->functionTable;
          FunctionEntry *interfaceEntry = interfaceFuncTable->entry;
          while (interfaceEntry != NULL) {
            FunctionEntry *childEntry = findFunctionEntryWithName(classInfo->program->functionTable, interfaceEntry->functionName);
            if (childEntry != NULL) {
              if (!(equalsArgumentList(childEntry->arguments, interfaceEntry->arguments) 
              && childEntry->argumentsCount == interfaceEntry->argumentsCount)) {
                char buffer[1024];
                snprintf(buffer, sizeof(buffer),
                  "Implement error. Interface function '%s' of '%s' has different arguments in child function '%s' of class '%s'\n", 
                  interfaceEntry->functionName, interfaceInfo->name, childEntry->functionName, classInfo->name);
                ProgramErrorInfo* error = createProgramErrorInfo(buffer);
                addProgramError(classInfo->program, error);
              } else if (!equalsTypeInfo(childEntry->returnType, interfaceEntry->returnType)) {
                char buffer[1024];
                snprintf(buffer, sizeof(buffer),
                  "Implement error. Interface function '%s' of '%s' has different return type of child function '%s' in class '%s'\n", 
                  interfaceEntry->functionName, interfaceInfo->name, childEntry->functionName, classInfo->name);
                ProgramErrorInfo* error = createProgramErrorInfo(buffer);
                addProgramError(classInfo->program, error);
              }
            } else {
              char buffer[1024];
              snprintf(buffer, sizeof(buffer),
                "Implementation error. Interface '%s' function '%s' for '%s' isn't implement\n", classInfo->interfaceNames[i], interfaceEntry->functionName, classInfo->name);
              ProgramErrorInfo* error = createProgramErrorInfo(buffer);
              addProgramError(classInfo->program, error);
            }
            interfaceEntry = interfaceEntry->next;
          }
        }
      }
    }
    if (!classInfo->isInterface)
      prepareCFGForProgram(classInfo, classProgram->classes, classInfo->body, classInfo->fileName, debug);
    classInfo = classInfo->next;
  }

  classInfo = classProgram->classes;
  while (classInfo != NULL) {
    prepareClassVtable(classInfo, classProgram->classes);
    classInfo = classInfo->next;
  }

  if (debug) {
    printAllClassesInfo(classProgram->classes);
    printAllClassesInfoTable(classProgram->classes);
  }

  return classProgram;
}

CFG *createCFG() {
  CFG *cfg = (CFG *)malloc(sizeof(CFG));
  cfg->entryBlock = NULL;
  cfg->blocks = NULL;
  return cfg;
}

void printCFG(CFG *cfg) {
  BasicBlock *block = cfg->blocks;
  while (block != NULL) {
    printf("Base block %d, %s (%s):\n", block->id, block->name,
           (block->type == CONDITIONAL)     ? "conditional"
           : (block->type == UNCONDITIONAL) ? "unconditional"
                                            : "terminal");
    for (int i = 0; i < block->instructionCount; i++) {
      printf("  Instruction %d: %s\nOperation tree:\n", i, block->instructions[i].text);
      if (block->instructions[i].otRoot != NULL) {
        printOperationTree(block->instructions[i].otRoot);
      }
      printf("\n");
    }
    Edge *edge = block->outEdges;
    while (edge != NULL) {
      printf("  Jump to block %d", edge->targetBlock->id);
      switch (edge->type) {
      case TRUE_CONDITION:
        printf(" if true");
        break;
      case FALSE_CONDITION:
        printf(" if false");
        break;
      case UNCONDITIONAL_JUMP:
        printf(" unconditional");
        break;
      }
      printf("\n");
      edge = edge->nextOut;
    }
    printf("\n");
    block = block->next;
  }
}

void freeInstructions(BasicBlock *block) {
  for (int i = 0; i < block->instructionCount; i++) {
    free(block->instructions[i].text);
    if (block->instructions[i].otRoot != NULL)
      destroyOperationTreeNodeTree(block->instructions[i].otRoot);
  }
  free(block->instructions);
}

void freeOutEdges(Edge *edge) {
  while (edge != NULL) {
    Edge *nextEdge = edge->nextOut;
    if (edge->condition != NULL) {
      free(edge->condition);
    }
    free(edge);
    edge = nextEdge;
  }
}

void freeBasicBlocks(BasicBlock *block) {
  while (block != NULL) {
    BasicBlock *nextBlock = block->next;
    freeInstructions(block);
    freeOutEdges(block->outEdges);
    block->inEdges = NULL;
    free(block->name);
    free(block);
    block = nextBlock;
  }
}

void freeCFG(CFG *cfg) {
  freeBasicBlocks(cfg->blocks);
  free(cfg);
}

TypeInfo *createTypeInfo(const char *typeName, bool custom, bool isArray, uint32_t arrayDim, uint32_t line, uint32_t pos) {
  TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
  typeInfo->typeName = strdup(typeName);
  typeInfo->custom = custom;
  typeInfo->isArray = isArray;
  typeInfo->arrayDim = arrayDim;
  typeInfo->line = line;
  typeInfo->pos = pos;
  typeInfo->next = NULL;
  typeInfo->isVarargs = false;
  return typeInfo;
}

void freeTypeInfo(TypeInfo *head) {
    TypeInfo *current = head;
    while (current != NULL) {
        TypeInfo *nextNode = current->next;

        if (current->typeName != NULL) {
            free(current->typeName);
            current->typeName = NULL;
        }

        free(current);
        current = nextNode;
    }
}

FieldInfo *createFieldInfo(TypeInfo *type, const char *name, uint32_t line, uint32_t pos) {
  FieldInfo *fieldInfo = (FieldInfo *)malloc(sizeof(FieldInfo));
  fieldInfo->type = type;
  fieldInfo->name = strdup(name);
  fieldInfo->next = NULL;
  fieldInfo->line = line;
  fieldInfo->pos = pos;
  fieldInfo->offset = 0;
  fieldInfo->isPrivate = false;
  fieldInfo->isStatic = false;
  return fieldInfo;
}

void addField(ClassInfo *classInfo, FieldInfo *fieldInfo) {
  if (classInfo->fields != NULL) {
    fieldInfo->offset = classInfo->fields->offset + 8;
  }
  fieldInfo->next = classInfo->fields;
  classInfo->fields = fieldInfo;
  classInfo->fieldsCount = classInfo->fieldsCount + 1;
}

void freeField(FieldInfo *field) {
  while (field != NULL) {
    FieldInfo *nextField = field->next;
    if (field->type != NULL) {
      freeTypeInfo(field->type);
    }
    if (field->name != NULL) {
      free(field->name);
    }
    free(field);
    field = nextField;
  }
}

ArgumentInfo *createArgumentInfo(TypeInfo *type, const char *name, uint32_t line, uint32_t pos) {
  ArgumentInfo *argInfo = (ArgumentInfo *)malloc(sizeof(ArgumentInfo));
  argInfo->type = type;
  argInfo->name = strdup(name);
  argInfo->next = NULL;
  argInfo->line = line;
  argInfo->pos = pos;
  argInfo->isVarargs = false;
  argInfo->offset = 0;
  return argInfo;
}

void addArgument(FunctionInfo *funcInfo, ArgumentInfo *argInfo) {
  argInfo->next = funcInfo->arguments;
  funcInfo->arguments = argInfo;
}

void freeArguments(ArgumentInfo *arg) {
  while (arg != NULL) {
    ArgumentInfo *nextArg = arg->next;
    if (arg->type != NULL) {
      freeTypeInfo(arg->type);
    }
    if (arg->name != NULL) {
      free(arg->name);
    }
    free(arg);
    arg = nextArg;
  }
}

FunctionInfo *createFunctionInfo(const char *fileName, const char *functionName,
                                 TypeInfo *returnType, uint32_t line, uint32_t pos) {
  FunctionInfo *funcInfo = (FunctionInfo *)malloc(sizeof(FunctionInfo));
  funcInfo->fileName = strdup(fileName);
  funcInfo->functionName = strdup(functionName);
  funcInfo->returnType = returnType;
  funcInfo->arguments = NULL;
  funcInfo->cfg = NULL;
  funcInfo->next = NULL;
  funcInfo->line = line;
  funcInfo->pos = pos;
  funcInfo->isVarargs = false;
  funcInfo->isBuiltin = false;
  funcInfo->isStatic = false;
  funcInfo->isPrivate = false;
  funcInfo->isConstructor = false;
  funcInfo->isOverride = false;
  return funcInfo;
}

void addFunctionToProgram(Program *program, FunctionInfo *funcInfo) {
  funcInfo->next = program->functions;
  program->functions = funcInfo;
}

void freeFunctionInfo(FunctionInfo *funcInfo) {
  if (funcInfo != NULL) {
    if (funcInfo->fileName != NULL) {
      free(funcInfo->fileName);
    }
    if (funcInfo->functionName != NULL) {
      free(funcInfo->functionName);
    }
    if (funcInfo->returnType != NULL) {
      freeTypeInfo(funcInfo->returnType);
    }
    if (funcInfo->arguments != NULL) {
      freeArguments(funcInfo->arguments);
    }
    if (funcInfo->cfg != NULL) {
      freeCFG(funcInfo->cfg);
    }
    free(funcInfo);
  }
}

void freeProgram(Program *program) {
  FunctionInfo *func = program->functions;
  while (func != NULL) {
    FunctionInfo *nextFunc = func->next;
    freeFunctionInfo(func);
    func = nextFunc;
  }
  freeProgramErrors(program->errors);
  freeProgramWarnings(program->warnings);
  free(program);
}

ProgramErrorInfo* createProgramErrorInfo(const char *message) {
    ProgramErrorInfo *errorInfo = (ProgramErrorInfo*)malloc(sizeof(ProgramErrorInfo));
    errorInfo->message = strdup(message);
    errorInfo->next = NULL;
    return errorInfo;
}

void addProgramError(Program *program, ProgramErrorInfo *errorInfo) {
    errorInfo->next = program->errors;
    program->errors = errorInfo;
}

void freeProgramErrors(ProgramErrorInfo *error) {
    while (error != NULL) {
        ProgramErrorInfo *nextError = error->next;
        free(error->message);
        free(error);
        error = nextError;
    }
}

ProgramWarningInfo* createProgramWarningInfo(const char *message) {
    ProgramWarningInfo *warningInfo = (ProgramWarningInfo*)malloc(sizeof(ProgramWarningInfo));
    warningInfo->message = strdup(message);
    warningInfo->next = NULL;
    return warningInfo;
}

void addProgramWarning(Program *program, ProgramWarningInfo *warningInfo) {
    warningInfo->next = program->warnings;
    program->warnings = warningInfo;
}

void freeProgramWarnings(ProgramWarningInfo *warning) {
    while (warning != NULL) {
        ProgramWarningInfo *nextWarning = warning->next;
        free(warning->message);
        free(warning);
        warning = nextWarning;
    }
}

ClassInfo* createClassInfo(const char* name, const char* parentName, const char** interfaceNames, int interfaceCount, MyAstNode* classBody, char* fileName, uint64_t typeId) {
  ClassInfo* info = (ClassInfo*)malloc(sizeof(ClassInfo));
  if (!info) return NULL;

  info->name = strdup(name);
  info->parentName = parentName ? strdup(parentName) : NULL;

  if (interfaceCount > 0 && interfaceNames) {
      info->interfaceNames = (char**)malloc(interfaceCount * sizeof(char*));
      for (int i = 0; i < interfaceCount; i++) {
          info->interfaceNames[i] = strdup(interfaceNames[i]);
      }
  } else {
      info->interfaceNames = NULL;
  }

  info->interfaceCount = interfaceCount;
  info->isInterface = false;
  info->program = NULL;
  info->fields = NULL;
  info->fieldsCount = 0;
  info->allParentFieldsCount = 0;
  info->next = NULL;
  info->body = classBody;
  info->fileName = strdup(fileName);
  info->typeId = typeId;
  info->vtable = NULL;

  return info;
}

ClassProgram* createClassProgram() {
  ClassProgram* program = (ClassProgram*)malloc(sizeof(ClassProgram));
  if (!program) return NULL;
  program->classes = NULL;
  return program;
}

void addClassInfo(ClassProgram* program, ClassInfo* classInfo) {
  if (!program || !classInfo) return;

  ClassInfo *existing = findClassWithName(program->classes, classInfo->name);

  if (existing != NULL) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer),
      "Class declaration error. Class %s is exists\n", 
      existing->name);
    ProgramErrorInfo* error = createProgramErrorInfo(buffer);
    addProgramError(existing->program, error);
  }
  classInfo->next = program->classes;
  program->classes = classInfo;
}

//DO NOT FREE BODY
void freeClassInfo(ClassInfo* info) {
  if (!info) return;

  free(info->name);
  free(info->parentName);

  for (int i = 0; i < info->interfaceCount; i++) {
      free(info->interfaceNames[i]);
  }
  free(info->interfaceNames);

  if (info->program) {
      freeProgram(info->program);
  }

  if (info->vtable) {
    freeVtable(info->vtable);
  }

  freeField(info->fields);
  free(info->fileName);

  free(info);
}

void freeClassProgram(ClassProgram* program) {
  if (!program) return;

  ClassInfo* current = program->classes;
  while (current) {
      ClassInfo* next = current->next;
      freeClassInfo(current);
      current = next;
  }

  free(program);
}


ClassVtable *createVtable() {
  ClassVtable *vtable = malloc(sizeof(ClassVtable));
  vtable->head = NULL;
  vtable->tail = NULL;
  vtable->currentOffset = 0;
  return vtable;
}

void addVtableEntry(ClassVtable *vtable, const char *functionName, const char *className, bool isBuiltin) {
  ClassVtableEntry *newEntry = malloc(sizeof(*newEntry));
  newEntry->functionName = strdup(functionName);
  newEntry->className = strdup(className);
  newEntry->offset       = vtable->currentOffset;
  newEntry->next         = NULL;
  newEntry->prev         = NULL;
  newEntry->isBuiltin = isBuiltin;

  if (vtable->head == NULL) {
      vtable->head = vtable->tail = newEntry;
  } else {
      vtable->tail->next = newEntry;
      newEntry->prev     = vtable->tail;
      vtable->tail       = newEntry;
  }
}

void prepareOffset(ClassVtable *vtable, size_t *outCount) {
  size_t count = 0;
  ClassVtableEntry *cur = vtable->head;
  while (cur) {
      count++;
      cur = cur->next;
  }

  ClassVtableEntry **array = malloc(count * sizeof(ClassVtableEntry *));

  cur = vtable->head;
  for (size_t i = 0; i < count; ++i) {
      cur->offset = i * 8;
      cur = cur->next;
  }

  *outCount = count;
  free(array);
}

void freeVtable(ClassVtable *vtable) {
  ClassVtableEntry *current = vtable->head;
  while (current) {
      ClassVtableEntry *next = current->next;
      free(current->functionName);
      free(current->className);
      free(current);
      current = next;
  }
  free(vtable);
}
void printTypeInfo(TypeInfo* type) {
    while (type) {
        printf("Type: %s", type->typeName);
        if (type->isArray)
            printf(" (array, dim=%u)", type->arrayDim);
        if (type->isVarargs)
            printf(" (varargs)");
        printf("\n");
        type = type->next;
    }
}

void printFieldInfo(FieldInfo* field) {
    while (field) {
        printf("  Field: %s\n", field->name);
        if (field->type) {
            printf("    ");
            printTypeInfo(field->type);
        }
        printf("    Line: %u, Pos: %u, Offset: %ld\n", field->line, field->pos, field->offset);
        field = field->next;
    }
}

void printFunctionEntry(FunctionEntry* fn) {
    while (fn) {
        printf("  Function: %s (File: %s)\n", fn->functionName, fn->fileName);
        if (fn->returnType) {
            printf("    Return type: ");
            printTypeInfo(fn->returnType);
        }
        printf("    Arguments count: %u, IsVarargs: %s, IsBuiltin: %s, IsStatic: %s, IsPrivate: %s\n",
               fn->argumentsCount,
               fn->isVarargs ? "true" : "false",
               fn->isBuiltin ? "true" : "false",
               fn->isStatic ? "true" : "false",
               fn->isPrivate ? "true" : "false");
        fn = fn->next;
    }
}

void printProgramErrors(ProgramErrorInfo* error) {
    if (!error) return;
    printf("Errors:\n");
    while (error) {
        printf("  - %s\n", error->message);
        error = error->next;
    }
}

void printProgramWarnings(ProgramWarningInfo* warning) {
    if (!warning) return;
    printf("Warnings:\n");
    while (warning) {
        printf("  - %s\n", warning->message);
        warning = warning->next;
    }
}

void printProgramInfo(Program* program) {
    if (!program) return;

    printf("Functions:\n");
    FunctionInfo *func = program->functions;
    while (func != NULL) {
      printFunctionInfo(func);
      func = func->next;
    }

    printProgramErrors(program->errors);
    printProgramWarnings(program->warnings);
}

void printClassInfo(ClassInfo* cls) {
    printf("====================================================\n");
    printf("Class: %s\n", cls->name);
    printf("TypeID: %lu\n", cls->typeId);
    printf("Parent: %s\n", cls->parentName ? cls->parentName : "None");
    printf("Is Interface: %s\n", cls->isInterface ? "Yes" : "No");

    if (cls->interfaceCount > 0 && cls->interfaceNames) {
        printf("Implements:\n");
        for (int i = 0; i < cls->interfaceCount; i++) {
            printf("  - %s\n", cls->interfaceNames[i]);
        }
    }

    if (cls->fields) {
        printf("Fields:\n");
        printFieldInfo(cls->fields);
    }

    if (cls->program) {
        printf("Program Info:\n");
        printProgramInfo(cls->program);
    }
}

void printAllClassesInfo(ClassInfo* head) {
    ClassInfo* current = head;
    while (current) {
        printClassInfo(current);
        current = current->next;
    }
}


void printFunctionInfo(FunctionInfo *funcInfo) {
  printf("  File: %s\n", funcInfo->fileName);
  printf("  Function: %s\n", funcInfo->functionName);
  printf("  Constructor: %s\n", funcInfo->isConstructor ? "Yes" : "No");;
  printf("  Builtin: %s\n", funcInfo->isBuiltin ? "Yes" : "No");
  printf("  Static: %s\n", funcInfo->isStatic ? "Yes" : "No");
  printf("  Private: %s\n", funcInfo->isPrivate ? "Yes" : "No");
  printf("  Varargs: %s\n", funcInfo->isVarargs ? "Yes" : "No");
  printf("  Return type: %s", funcInfo->returnType->typeName);
  if (funcInfo->returnType->custom)
    printf(", custom type");
  if (funcInfo->returnType->isArray)
    printf(", array with dim %d", funcInfo->returnType->arrayDim);
  printf("\n");
  printf("  Arguments:\n");
  ArgumentInfo *arg = funcInfo->arguments;
  while (arg != NULL) {
    printf("    %s %s, varargs: %s", arg->type->typeName, arg->name, arg->isVarargs ? "Yes" : "No");
    if (arg->type->custom)
      printf(", custom type");
    if (arg->type->isArray)
      printf(", array with dim %d", arg->type->arrayDim);
    printf("\n");
    arg = arg->next;
  }
  printf("\n");

  if (funcInfo->cfg != NULL)
    printCFG(funcInfo->cfg);
}

void writeOperationTreeToDot(FILE *file, OperationTreeNode *node, int *nodeCounter) {
    if (node == NULL) {
        return;
    }

    int currentNodeId = (*nodeCounter)++;
    
    char escapedLabel[256];
    const char *src = node->label;
    char *dst = escapedLabel;
    while (*src && (dst - escapedLabel) < 255) {
        if (*src == '<') {
            *dst++ = '&';
            *dst++ = 'l';
            *dst++ = 't';
            *dst++ = ';';
        } else if (*src == '>') {
            *dst++ = '&';
            *dst++ = 'g';
            *dst++ = 't';
            *dst++ = ';';
        } else if (*src == '&') {
            *dst++ = '&';
            *dst++ = 'a';
            *dst++ = 'm';
            *dst++ = 'p';
            *dst++ = ';';
        } else if (*src == '"') {
            *dst++ = '\\';
            *dst++ = '"';
        } else {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';

    if (node->type == NULL) {
      fprintf(file, "        node%d [label=\"%s\", color=blue];\n", currentNodeId, escapedLabel);
    } else {
      fprintf(file, "        node%d [label=\"%s <%s:%d, reg: %s, spilled: %d, offset: %d>\", color=blue];\n", currentNodeId, escapedLabel, node->type->typeName, node->type->arrayDim, node->reg, node->isSpilled, node->offset);
    }

    for (uint32_t i = 0; i < node->childCount; i++) {
        int childNodeId = *nodeCounter;
        writeOperationTreeToDot(file, node->children[i], nodeCounter);
        fprintf(file, "        node%d -> node%d[color=blue];\n", currentNodeId, childNodeId);
    }
}

void writeCFGToDotFile(CFG *cfg, const char *filename, bool drawOt) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Can't open file %s to write\n", filename);
        return;
    }

    fprintf(file, "digraph CFG {\n");
    fprintf(file, "    compound=true;\n");
    fprintf(file, "    graph [splines=true];\n");
    fprintf(file, "    node [shape=rectangle];\n\n");

    if (cfg == NULL) {
      return;
    }

    BasicBlock *block = cfg->blocks;
    int nodeCounter = 0;
    int clusterCounter = 0;

    while (block != NULL) {
        fprintf(file, "    BB%d [label=<", block->id);
        fprintf(file, "<B>BB%d: %s</B><BR ALIGN=\"CENTER\"/>", block->id, block->name);

        for (int i = 0; i < block->instructionCount; i++) {
            char instruction[256];
            char *src = block->instructions[i].text;
            char *dst = instruction;
            while (*src && (dst - instruction) < 255) {
                if (*src == '<') {
                    *dst++ = '&';
                    *dst++ = 'l';
                    *dst++ = 't';
                    *dst++ = ';';
                } else if (*src == '>') {
                    *dst++ = '&';
                    *dst++ = 'g';
                    *dst++ = 't';
                    *dst++ = ';';
                } else if (*src == '&') {
                    *dst++ = '&';
                    *dst++ = 'a';
                    *dst++ = 'm';
                    *dst++ = 'p';
                    *dst++ = ';';
                } else if (*src == '"') {
                    *dst++ = '\\';
                    *dst++ = '"';
                } else {
                    *dst++ = *src;
                }
                src++;
            }
            *dst = '\0';
            fprintf(file, "%s<BR ALIGN=\"CENTER\"/>", instruction);
        }

        fprintf(file, ">];\n");

        if (drawOt) {
          for (int i = 0; i < block->instructionCount; i++) {
              if (block->instructions[i].otRoot != NULL) {
                  fprintf(file, "    subgraph cluster_instruction%d {\n", clusterCounter);
                  fprintf(file, "        label = \"OT of BB%d:%d\";\n", block->id, i);
                  fprintf(file, "        style=rounded;\n");
                  fprintf(file, "        color=blue;\n");

                  char entryNodeName[64];
                  snprintf(entryNodeName, sizeof(entryNodeName), "entry%d", clusterCounter);
                  fprintf(file, "        %s [shape=point, style=invis];\n", entryNodeName);

                  writeOperationTreeToDot(file, block->instructions[i].otRoot, &nodeCounter);

                  fprintf(file, "    }\n");

                  fprintf(file, "    BB%d -> %s [lhead=cluster_instruction%d, color=blue];\n", block->id, entryNodeName, clusterCounter);

                  clusterCounter++;
              }
          }
        }

        block = block->next;
    }

    fprintf(file, "\n");

    block = cfg->blocks;
    while (block != NULL) {
        Edge *edge = block->outEdges;
        while (edge != NULL) {
            const char *edgeLabel = "";
            switch (edge->type) {
                case TRUE_CONDITION:
                    edgeLabel = " [label=\"True\", color=green]";
                    break;
                case FALSE_CONDITION:
                    edgeLabel = " [label=\"False\", color=red]";
                    break;
                case UNCONDITIONAL_JUMP:
                    edgeLabel = "";
                    break;
            }
            fprintf(file, "    BB%d -> BB%d%s;\n", block->id, edge->targetBlock->id, edgeLabel);
            edge = edge->nextOut;
        }
        block = block->next;
    }

    fprintf(file, "}\n");

    fclose(file);
}

void traverseOperationTreeAndBuildCallGraph(OperationTreeNode *node, int depth, CallGraph *cg, const char *callerName, bool debug) {
    if (node == NULL) {
        return;
    }

    if (debug) {
      for (int i = 0; i < depth; i++) {
        printf("  ");
      }
      printf("Node Label: %s, Line: %u, Pos: %u, IsImaginary: %s\n",
             node->label, node->line, node->pos + 1,
             node->isImaginary ? "true" : "false");
    }

    if (strcmp(node->label, "call") == 0 && node->childCount >= 1 && node->children[0] != NULL && node->children[0]->childCount == 0) {
        const char *calleeName = node->children[0]->label;
        if (debug)
          printf("    Detected function call: %s -> %s\n", callerName, calleeName);
        addCallEdge(cg, callerName, calleeName);
    }

    for (uint32_t i = 0; i < node->childCount; i++) {
        traverseOperationTreeAndBuildCallGraph(node->children[i], depth + 1, cg, callerName, debug);
    }
}

void traverseInstructionAndBuildCallGraph(Instruction *instr, CallGraph *cg, const char *callerName, bool debug) {
    if (instr == NULL) {
        return;
    }

    if (debug)
      printf("    Instruction: %s\n", instr->text);

    if (instr->otRoot != NULL) {
        if (debug)
          printf("      Operation Tree:\n");
        traverseOperationTreeAndBuildCallGraph(instr->otRoot, 3, cg, callerName, debug);
    }
}

void traverseBasicBlockAndBuildCallGraph(BasicBlock *block, CallGraph *cg, const char *functionName, bool debug) {
    if (block == NULL) {
        return;
    }

    if (debug)
      printf("  BasicBlock ID: %d, Name: %s\n", block->id, block->name);

    for (int i = 0; i < block->instructionCount; i++) {
        traverseInstructionAndBuildCallGraph(&block->instructions[i], cg, functionName, debug);
    }
}

void traverseCFGAndBuildCallGraph(CFG *cfg, CallGraph *cg, const char *functionName, bool debug) {
    if (cfg == NULL) {
        return;
    }

    if (debug)
      printf("Traversing CFG for function: %s\n", functionName);

    BasicBlock *block = cfg->blocks;
    while (block != NULL) {
        traverseBasicBlockAndBuildCallGraph(block, cg, functionName, debug);
        block = block->next;
    }

    if (debug)
      printf("End of CFG Traversal for function: %s\n", functionName);
}

void traverseProgramAndBuildCallGraph(Program *program, CallGraph *cg, bool debug) {
    if (program == NULL) {
        return;
    }

    if (debug)
      printf("Starting Program Traversal and Building Call Graph.\n");

    FunctionInfo *func = program->functions;
    while (func != NULL) {
      if (debug) {
              printf("\nTraversing Function: %s in file %s (Line: %u, Pos: %u)\n",
               func->functionName,
               func->fileName,
               func->line,
               func->pos + 1);
      }


        traverseCFGAndBuildCallGraph(func->cfg, cg, func->functionName, debug);

        func = func->next;
    }

    if (debug)
      printf("\nEnd of Program Traversal.\n");
}

void printEntriesReversed(const ClassVtableEntry *e) {
  if (!e) return;
  printEntriesReversed(e->prev);
  printf("Function: %-20s | Class: %-20s | Offset: %ld\n", e->functionName, e->className, e->offset);
}

void printVtable(const ClassVtable *vtable) {
  if (!vtable) {
      printf("Vtable is NULL\n");
      return;
  }

  const ClassVtableEntry *entry = vtable->tail;

  printf("=== Class Vtable ===\n");
  printEntriesReversed(entry);
  printf("====================\n");
}
