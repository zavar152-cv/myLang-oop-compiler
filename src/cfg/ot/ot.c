#include "ot.h"
#include "../tokens.h"
#include "cfg/cfg.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

OperationTreeNode *newOperationTreeNode(const char *label, uint32_t childCount, uint32_t line, uint32_t pos, bool isImaginary) {
  OperationTreeNode *node = (OperationTreeNode *)malloc(sizeof(OperationTreeNode));
  node->label = strdup(label);
  node->childCount = childCount;
  node->children = (OperationTreeNode **)malloc(childCount * sizeof(OperationTreeNode *));
  node->line = line;
  node->pos = pos;
  node->isImaginary = isImaginary;
  node->type = NULL;
  return node;
}

void destroyOperationTreeNodeTree(OperationTreeNode *root) {
  if (root == NULL) {
    return;
  }
  for (uint32_t i = 0; i < root->childCount; i++) {
    destroyOperationTreeNodeTree(root->children[i]);
  }
  if (root->type != NULL) {
    freeTypeInfo(root->type);
  }
  free(root->children);
  free((void *)root->label);
  free(root);
}

bool isBinaryOp(const char *label) {
  return strcmp(label, PLUS) == 0 |
          strcmp(label, MINUS) == 0 |
          strcmp(label, MUL) == 0 |
          strcmp(label, DIV) == 0 |
          strcmp(label, MOD) == 0 |
          strcmp(label, LE) == 0 |
          strcmp(label, GR) == 0 |
          strcmp(label, LE_EQ) == 0 |
          strcmp(label, GR_EQ) == 0 |
          strcmp(label, EQ) == 0 |
          strcmp(label, NEQ) == 0 |
          strcmp(label, AND) == 0 |
          strcmp(label, OR) == 0;
}

bool isCmpOp(const char *label) {
  return  strcmp(label, LE) == 0 |
          strcmp(label, GR) == 0 |
          strcmp(label, LE_EQ) == 0 |
          strcmp(label, GR_EQ) == 0 |
          strcmp(label, EQ) == 0 |
          strcmp(label, NEQ) == 0;
}

bool isUnaryOp(const char *label) {
  return strcmp(label, NEG) == 0 |
          strcmp(label, NOT) == 0;
}

bool isLiteral(const char *label) {
  return strcmp(label, BOOL) == 0 |
          strcmp(label, STR) == 0 |
          strcmp(label, SYMB) == 0 |
          strcmp(label, HEX) == 0 |
          strcmp(label, BITS) == 0 |
          strcmp(label, DEC) == 0;
}

bool isCanBeByte(const char *str) {
  char *endptr;
  errno = 0;
  long val = strtol(str, &endptr, 10);
  if (errno == 0 && *endptr == '\0' && val >= -128 && val <= 127) {
      return true;
  }
  return false;
}

bool isCanBeInt(const char *str) {
  char *endptr;
  errno = 0;
  long val = strtol(str, &endptr, 10);
  if (errno == 0 && *endptr == '\0' && val >= INT_MIN && val <= INT_MAX) {
    return true;
  }
  return false;
}

bool isCanBeUnsignedInt(const char *str) {
  char *endptr;
  errno = 0;
  unsigned long uval = strtoul(str, &endptr, 10);
  if (errno == 0 && *endptr == '\0' && uval <= UINT_MAX) {
    return true;
  }
  return false;
}

bool isCanBeLong(const char *str) {
  char *endptr;
  errno = 0;
  long val = strtol(str, &endptr, 10);
  if (errno == 0 && *endptr == '\0' && val >= LONG_MIN && val <= LONG_MAX) {
    return true;
  }
  return false;
}

bool isCanBeUnsignedLong(const char *str) {
  char *endptr;
  errno = 0;
  if (*str == '-') {
    return false;
  }

  unsigned long uval = strtoul(str, &endptr, 10);
  if (errno == 0 && *endptr == '\0' && uval <= ULONG_MAX) {
    return true;
  }
  return false;
}

OperationTreeNode *buildExprOperationTreeFromAstNode(MyAstNode* root, bool isLvalue, bool isFunctionName, OperationTreeErrorContainer *container, ScopeManager *sm, const char* filename) {
  if (strcmp(root->label, ASSIGN) == 0) {
    //left - EXPR
    //right - EXPR
    OperationTreeNode *writeOpNode = newOperationTreeNode(WRITE, 2, root->line, root->pos, root->isImaginary);
    OperationTreeNode *lValueExprNode = buildExprOperationTreeFromAstNode(root->children[0], true, false, container, sm, filename);
    OperationTreeNode *rValueExprNode = buildExprOperationTreeFromAstNode(root->children[1], false, false, container, sm, filename);
    
    if (strcmp(lValueExprNode->type->typeName, "byte") == 0) {
      if (strcmp(rValueExprNode->label, LIT_READ) == 0 && isCanBeByte(rValueExprNode->children[1]->label)) {
        TypeInfo* newTypeParent = createTypeInfo("byte", false, false, 0, rValueExprNode->type->line, rValueExprNode->type->pos);
        TypeInfo* newTypeChild = createTypeInfo("byte", false, false, 0, rValueExprNode->children[1]->type->line, rValueExprNode->children[1]->type->pos);
        freeTypeInfo(rValueExprNode->type);
        freeTypeInfo(rValueExprNode->children[1]->type);
        rValueExprNode->type = newTypeParent;
        rValueExprNode->children[1]->type = newTypeChild;
      } else if (strcmp(rValueExprNode->type->typeName, "byte") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Type error. Can't cast value at %s:%d:%d to byte\n",
                filename, rValueExprNode->line,
                rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }        
      }
    } else if (strcmp(lValueExprNode->type->typeName, "int") == 0) {
      if (strcmp(rValueExprNode->type->typeName, "byte") != 0 && strcmp(rValueExprNode->type->typeName, "int") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Type error. Can't cast value at %s:%d:%d to int\n",
                filename, rValueExprNode->line,
                rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }        
      }
    } else if (strcmp(lValueExprNode->type->typeName, "uint") == 0) {
      if (strcmp(rValueExprNode->label, LIT_READ) == 0 && isCanBeUnsignedInt(rValueExprNode->children[1]->label)) {
        TypeInfo* newTypeParent = createTypeInfo("uint", false, false, 0, rValueExprNode->type->line, rValueExprNode->type->pos);
        TypeInfo* newTypeChild = createTypeInfo("uint", false, false, 0, rValueExprNode->children[1]->type->line, rValueExprNode->children[1]->type->pos);
        freeTypeInfo(rValueExprNode->type);
        freeTypeInfo(rValueExprNode->children[1]->type);
        rValueExprNode->type = newTypeParent;
        rValueExprNode->children[1]->type = newTypeChild;        
      } else if (strcmp(rValueExprNode->type->typeName, "uint") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Type error. Can't cast value at %s:%d:%d to uint\n",
                filename, rValueExprNode->line,
                rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }        
      }      
    } else if (strcmp(lValueExprNode->type->typeName, "long") == 0) {
      if (strcmp(rValueExprNode->label, LIT_READ) == 0 && isCanBeLong(rValueExprNode->children[1]->label)) {
        TypeInfo* newTypeParent = createTypeInfo("long", false, false, 0, rValueExprNode->type->line, rValueExprNode->type->pos);
        TypeInfo* newTypeChild = createTypeInfo("long", false, false, 0, rValueExprNode->children[1]->type->line, rValueExprNode->children[1]->type->pos);
        freeTypeInfo(rValueExprNode->type);
        freeTypeInfo(rValueExprNode->children[1]->type);
        rValueExprNode->type = newTypeParent;
        rValueExprNode->children[1]->type = newTypeChild;   
      } else if (strcmp(rValueExprNode->type->typeName, "byte") != 0 && strcmp(rValueExprNode->type->typeName, "int") != 0
          && strcmp(rValueExprNode->type->typeName, "uint") != 0 && strcmp(rValueExprNode->type->typeName, "long") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Type error. Can't cast value at %s:%d:%d to long\n",
                filename, rValueExprNode->line,
                rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }        
      }       
    } else if (strcmp(lValueExprNode->type->typeName, "ulong") == 0) {
      if (strcmp(rValueExprNode->label, LIT_READ) == 0 && isCanBeUnsignedLong(rValueExprNode->children[1]->label)) {
        TypeInfo* newTypeParent = createTypeInfo("ulong", false, false, 0, rValueExprNode->type->line, rValueExprNode->type->pos);
        TypeInfo* newTypeChild = createTypeInfo("ulong", false, false, 0, rValueExprNode->children[1]->type->line, rValueExprNode->children[1]->type->pos);
        freeTypeInfo(rValueExprNode->type);
        freeTypeInfo(rValueExprNode->children[1]->type);
        rValueExprNode->type = newTypeParent;
        rValueExprNode->children[1]->type = newTypeChild;   
      } else if (strcmp(rValueExprNode->type->typeName, "uint") != 0 && strcmp(rValueExprNode->type->typeName, "ulong") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Type error. Can't cast value at %s:%d:%d to ulong\n",
                filename, rValueExprNode->line,
                rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }        
      }     
    }
    //TODO for bool, char, string?
    
    writeOpNode->children[0] = lValueExprNode;
    writeOpNode->children[1] = rValueExprNode;
    writeOpNode->type = createTypeInfo(lValueExprNode->type->typeName, lValueExprNode->type->custom, lValueExprNode->type->isArray, lValueExprNode->type->arrayDim, lValueExprNode->type->line, lValueExprNode->type->pos);
    return writeOpNode;
  } else if (strcmp(root->label, FUNC_CALL) == 0) {
    //if count == 2
    //left - EXPR_LIST
    //right - EXPR

    //if count == 1
    //child - EXPR
    if (root->childCount == 2) {
      OperationTreeNode *funcNameNode = buildExprOperationTreeFromAstNode(root->children[1], false, true, container, sm, filename);
      OperationTreeNode *callNode = newOperationTreeNode(OT_CALL, 1 + root->children[0]->childCount, funcNameNode->line, funcNameNode->pos, funcNameNode->isImaginary);
      callNode->children[0] = funcNameNode;
      for (uint32_t i = 0; i < root->children[0]->childCount; i++) {
        OperationTreeNode *argNode = buildExprOperationTreeFromAstNode(root->children[0]->children[i], false, false, container, sm, filename);
        callNode->children[1 + i] = argNode;
      }
      if (isLvalue) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Assign error. Can't use function calling to assign at %s:%d:%d\n",
                filename, callNode->line,
                callNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
      return callNode;
    } else if (root->childCount == 1) {
      OperationTreeNode *funcNameNode = buildExprOperationTreeFromAstNode(root->children[0], false, true, container, sm, filename);
      OperationTreeNode *callNode = newOperationTreeNode(OT_CALL, 1, funcNameNode->line, funcNameNode->pos, funcNameNode->isImaginary);
      callNode->children[0] = funcNameNode;
      if (isLvalue) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Assign error. Can't use function calling to assign at %s:%d:%d\n",
                filename, callNode->line,
                callNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
      return callNode;
    }
  } else if (strcmp(root->label, INDEXING) == 0) {
    //left - EXPR_LISR
    //right - EXPR
    if (root->childCount == 1) {
      OperationTreeNode *indexNameNode = buildExprOperationTreeFromAstNode(root->children[0], false, false, container, sm, filename);
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
               "Index error. Missing index value at %s:%d:%d\n",
               filename, indexNameNode->line,
               indexNameNode->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }
      return indexNameNode;
    } else {
      OperationTreeNode *indexNameNode = buildExprOperationTreeFromAstNode(root->children[1], false, false, container, sm, filename);
      OperationTreeNode *indexNode = newOperationTreeNode(INDEX, 1 + root->children[0]->childCount, indexNameNode->line, indexNameNode->pos, indexNameNode->isImaginary);
      indexNode->children[0] = indexNameNode;
      for (uint32_t i = 0; i < root->children[0]->childCount; i++) {
        OperationTreeNode *iNode = buildExprOperationTreeFromAstNode(root->children[0]->children[i], false, false, container, sm, filename);
        indexNode->children[1 + i] = iNode;
      }
      return indexNode;
    }
  } else if (isBinaryOp(root->label)) {
    //left - EXPR
    //right - EXPR 
    if (isLvalue) {
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
               "Assign error. Can't use binary operation result to assign at %s:%d:%d\n",
               filename, root->line,
               root->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }
    }
    if (isFunctionName) {
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
              "Call error. Can't use binary operation to call function at %s:%d:%d\n",
              filename, root->line,
              root->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }        
    }
    OperationTreeNode *binaryOpNode = newOperationTreeNode(root->label, 2, root->line, root->pos, root->isImaginary);
    OperationTreeNode *leftExprNode = buildExprOperationTreeFromAstNode(root->children[0], false, false, container, sm, filename);
    OperationTreeNode *rightExprNode = buildExprOperationTreeFromAstNode(root->children[1], false, false, container, sm, filename);

    if (isCmpOp(root->label)) {

      if (isCmpOp(leftExprNode->label)) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Compare error. Can't use result of comapre operation as "
                 "operands at %s:%d:%d\n",
                 filename, leftExprNode->line, leftExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
      if (isCmpOp(rightExprNode->label)) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Compare error. Can't use result of comapre operation as "
                 "operands at %s:%d:%d\n",
                 filename, rightExprNode->line, rightExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }      
    }

    binaryOpNode->children[0] = leftExprNode;
    binaryOpNode->children[1] = rightExprNode;
    return binaryOpNode;
  } else if (isUnaryOp(root->label)) {
    //child - EXPR 
    if (isLvalue) {
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
               "Assign error. Can't use unary operation result to assign at %s:%d:%d\n",
               filename, root->line,
               root->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }
    }
    if (isFunctionName) {
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
              "Call error. Can't use unary operation to call function at %s:%d:%d\n",
              filename, root->line,
              root->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }        
    }
    OperationTreeNode *unaryOpNode = newOperationTreeNode(root->label, 1, root->line, root->pos, root->isImaginary);
    OperationTreeNode *exprNode = buildExprOperationTreeFromAstNode(root->children[0], false, false, container, sm, filename);
    unaryOpNode->children[0] = exprNode;
    return unaryOpNode;
  } else if (strcmp(root->label, IDENTIFIER) == 0) {
    //child - value, terminal
    OperationTreeNode *idValueNode = newOperationTreeNode(root->children[0]->label, 0, root->children[0]->line, root->children[0]->pos, root->children[0]->isImaginary);
    Symbol *gotSymbol = findSymbol(sm, root->children[0]->label);
    if (!isFunctionName) {
      if (gotSymbol == NULL) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Var not found error. Var with name %s at %s:%d:%d is not declared\n",
                root->children[0]->label, filename, root->children[0]->line, root->children[0]->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }    
      }
    }
    if (gotSymbol != NULL) {
      idValueNode->type = createTypeInfo(gotSymbol->typeName, gotSymbol->custom, gotSymbol->isArray, gotSymbol->arrayDim, gotSymbol->line, gotSymbol->pos);
    }
    if (isLvalue | isFunctionName) {
      return idValueNode;
    } else {
      OperationTreeNode *readNode = newOperationTreeNode(READ, 1, root->children[0]->line, root->children[0]->pos, true);
      if (gotSymbol != NULL) {
        readNode->type = createTypeInfo(gotSymbol->typeName, gotSymbol->custom, gotSymbol->isArray, gotSymbol->arrayDim, gotSymbol->line, gotSymbol->pos);
      }
      readNode->children[0] = idValueNode;
      return readNode;
    }
  } else if (isLiteral(root->label)) {
    //child - value, terminal
    if (isLvalue) {
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
               "Assign error. Can't use literal to assign at %s:%d:%d\n",
               filename, root->children[0]->line,
               root->children[0]->pos + 1);
      addOperationTreeError(container, buffer);
    }
    if (isFunctionName) {
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
              "Call error. Can't use literal to call function at %s:%d:%d\n",
              filename, root->children[0]->line,
              root->children[0]->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }        
    }
    OperationTreeNode *literalValueNode = newOperationTreeNode(root->children[0]->label, 0, root->children[0]->line, root->children[0]->pos, root->children[0]->isImaginary);
    OperationTreeNode *literalTypeNode = newOperationTreeNode(root->label, 0, root->line, root->pos, root->isImaginary);
    OperationTreeNode *litReadNode = newOperationTreeNode(LIT_READ, 2, root->children[0]->line, root->children[0]->pos, true);
    litReadNode->children[0] = literalTypeNode;
    litReadNode->children[1] = literalValueNode;

    if (strcmp(literalTypeNode->label, SYMB) == 0) {
      litReadNode->children[1]->type = createTypeInfo("char", false, false, 0, root->children[0]->line, root->children[0]->pos);
    } else if (strcmp(literalTypeNode->label, BOOL) == 0) {
      litReadNode->children[1]->type = createTypeInfo("bool", false, false, 0, root->children[0]->line, root->children[0]->pos);
    } else if (strcmp(literalTypeNode->label, DEC) == 0) {
      if (!isCanBeInt(literalValueNode->label)) {
        if (isCanBeUnsignedInt(literalValueNode->label)) {
          litReadNode->children[1]->type = createTypeInfo("uint", false, false, 0, root->children[0]->line, root->children[0]->pos);
        } else if (isCanBeLong(literalValueNode->label)) {
          litReadNode->children[1]->type = createTypeInfo("long", false, false, 0, root->children[0]->line, root->children[0]->pos);
        } else if (isCanBeUnsignedLong(literalValueNode->label)) {
          litReadNode->children[1]->type = createTypeInfo("ulong", false, false, 0, root->children[0]->line, root->children[0]->pos);
        } else {
          litReadNode->children[1]->type = createTypeInfo("_", false, false, 0, root->children[0]->line, root->children[0]->pos);
          char buffer[1024];
          snprintf(buffer, sizeof(buffer),
                  "Type error. Can't represent a value %s as int, uint, long or ulong at %s:%d:%d\n",
                  literalValueNode->label, filename, root->children[0]->line,
                  root->children[0]->pos + 1);
          if (container->error == NULL) {
            container->error = createOperationTreeErrorInfo(buffer);
          } else {
            addOperationTreeError(container, buffer);
          }             
        }
      } else {
        litReadNode->children[1]->type = createTypeInfo("int", false, false, 0, root->children[0]->line, root->children[0]->pos);
      }
    } else if (strcmp(literalTypeNode->label, STR) == 0) {
      litReadNode->children[1]->type = createTypeInfo("string", false, false, 0, root->children[0]->line, root->children[0]->pos);
    }
    litReadNode->type = createTypeInfo(litReadNode->children[1]->type->typeName, false, false, 0, root->children[0]->line, root->children[0]->pos);
    return litReadNode;
  } else {
    return NULL;
  }      
}

OperationTreeNode *buildTyperefHelper(OperationTreeErrorContainer *container, TypeInfo* varType, const char* filename) {
  OperationTreeNode *withTypeNode = newOperationTreeNode(WITH_TYPE, varType->isArray ? 3 : 2, 0, 0, true);
  if (varType->isArray) {
    withTypeNode->children[0] = newOperationTreeNode(varType->typeName, 0, varType->line, varType->pos, false);
    withTypeNode->children[1] = newOperationTreeNode(varType->custom ? CUSTOM : BUILTIN, 0, varType->line, varType->pos, false);

    if (varType->next != NULL) {
      withTypeNode->children[2] = newOperationTreeNode(OT_ARRAY, 2, varType->line, varType->pos, false);
      char buffer[12];
      snprintf(buffer, sizeof(buffer), "%u", varType->arrayDim);
      withTypeNode->children[2]->children[0] = newOperationTreeNode(buffer, 0, varType->line, varType->pos, false); 

      withTypeNode->children[2]->children[1] = buildTyperefHelper(container, varType->next, filename);

    } else {
      withTypeNode->children[2] = newOperationTreeNode(OT_ARRAY, 1, varType->line, varType->pos, false);
      char buffer[12];
      snprintf(buffer, sizeof(buffer), "%u", varType->arrayDim);
      withTypeNode->children[2]->children[0] = newOperationTreeNode(buffer, 0, varType->line, varType->pos, false);
    }
  } else {
    withTypeNode->children[0] = newOperationTreeNode(varType->typeName, 0, varType->line, varType->pos, false);
    withTypeNode->children[1] = newOperationTreeNode(varType->custom ? CUSTOM : BUILTIN, 0, varType->line, varType->pos, false);
  }
  return withTypeNode;
}

OperationTreeNode *buildVarDeclareHelper(MyAstNode* id, MyAstNode* init, OperationTreeErrorContainer *container, TypeInfo* varType, ScopeManager *sm, const char* filename) {
  OperationTreeNode *declareNode;
  OperationTreeNode *withTypeNode = newOperationTreeNode(WITH_TYPE, varType->isArray ? 3 : 2, 0, 0, true);
  if (varType->isArray) {
    OperationTreeNode *varNameNode = newOperationTreeNode(id->children[0]->label, 0, id->children[0]->line, id->children[0]->pos, false);
    withTypeNode->children[0] = newOperationTreeNode(varType->typeName, 0, varType->line, varType->pos, false);
    withTypeNode->children[1] = newOperationTreeNode(varType->custom ? CUSTOM : BUILTIN, 0, varType->line, varType->pos, false);

    if (varType->next != NULL) {
      withTypeNode->children[2] = newOperationTreeNode(OT_ARRAY, 2, varType->line, varType->pos, false);
      char buffer[12];
      snprintf(buffer, sizeof(buffer), "%u", varType->arrayDim);
      withTypeNode->children[2]->children[0] = newOperationTreeNode(buffer, 0, varType->line, varType->pos, false); 

      withTypeNode->children[2]->children[1] = buildTyperefHelper(container, varType->next, filename);

    } else {
      withTypeNode->children[2] = newOperationTreeNode(OT_ARRAY, 1, varType->line, varType->pos, false);
      char buffer[12];
      snprintf(buffer, sizeof(buffer), "%u", varType->arrayDim);
      withTypeNode->children[2]->children[0] = newOperationTreeNode(buffer, 0, varType->line, varType->pos, false);
    }
    assert(strcmp(init->children[0]->label, id->children[0]->label) == 0);
    OperationTreeNode *varInitExprNode;
    if (init->childCount == 2) {
      varInitExprNode = buildExprOperationTreeFromAstNode(init->children[1], false, false, container, sm, filename);
      OperationTreeNode *helperNode = newOperationTreeNode(WRITE, 2, id->children[0]->line, id->children[0]->pos, false);
      helperNode->children[0] = newOperationTreeNode(id->children[0]->label, 0, id->children[0]->line, id->children[0]->pos, false);
      helperNode->children[0]->type = createTypeInfo(varType->typeName, varType->custom, varType->isArray, varType->arrayDim, varType->line, varType->pos);
      helperNode->children[1] = varInitExprNode;
      helperNode->type = createTypeInfo(varType->typeName, varType->custom, varType->isArray, varType->arrayDim, varType->line, varType->pos);
      declareNode = newOperationTreeNode(DECLARE, 3, 0, 0, true);
      declareNode->children[0] = withTypeNode;
      declareNode->children[1] = varNameNode;
      declareNode->children[2] = helperNode;
    } else {
      declareNode = newOperationTreeNode(DECLARE, 2, 0, 0, true);
      declareNode->children[0] = withTypeNode;
      declareNode->children[1] = varNameNode;
    }
  } else {
    OperationTreeNode *varNameNode = newOperationTreeNode(id->children[0]->label, 0, id->children[0]->line, id->children[0]->pos, false);
    withTypeNode->children[0] = newOperationTreeNode(varType->typeName, 0, varType->line, varType->pos, false);
    withTypeNode->children[1] = newOperationTreeNode(varType->custom ? CUSTOM : BUILTIN, 0, varType->line, varType->pos, false);
    OperationTreeNode *varInitExprNode;
    if (init->childCount == 2) {
      varInitExprNode = buildExprOperationTreeFromAstNode(init->children[1], false, false, container, sm, filename);
      OperationTreeNode *helperNode = newOperationTreeNode(WRITE, 2, id->children[0]->line, id->children[0]->pos, false);
      helperNode->children[0] = newOperationTreeNode(id->children[0]->label, 0, id->children[0]->line, id->children[0]->pos, false);
      helperNode->children[0]->type = createTypeInfo(varType->typeName, varType->custom, varType->isArray, varType->arrayDim, varType->line, varType->pos);
      helperNode->children[1] = varInitExprNode;
      helperNode->type = createTypeInfo(varType->typeName, varType->custom, varType->isArray, varType->arrayDim, varType->line, varType->pos);
      declareNode = newOperationTreeNode(DECLARE, 3, id->children[0]->line, id->children[0]->pos, true);
      declareNode->children[0] = withTypeNode;
      declareNode->children[1] = varNameNode;
      declareNode->children[2] = helperNode;
    } else {
      declareNode = newOperationTreeNode(DECLARE, 2, id->children[0]->line, id->children[0]->pos, true);
      declareNode->children[0] = withTypeNode;
      declareNode->children[1] = varNameNode;
    }
  }
  return declareNode;
}

OperationTreeNode *buildVarOperationTreeFromAstNode(MyAstNode* root, OperationTreeErrorContainer *container, TypeInfo* varType, ScopeManager *sm, const char* filename) {
  assert(strcmp(root->children[0]->label, TYPEREF) == 0);

  uint32_t varCount = (root->childCount - 1) / 2;

  OperationTreeNode *varNode;
  if (varCount == 1) {
    //use DECLARE node
    varNode = buildVarDeclareHelper(root->children[1], root->children[2], container, varType, sm, filename);
    const char *symbolName = root->children[1]->children[0]->label;
    Symbol *gotSymbol = findSymbol(sm, symbolName);
    if (gotSymbol == NULL) {
      addSymbol(sm, symbolName, varType->typeName, varType->custom, varType->isArray, varType->arrayDim, root->children[1]->children[0]->line, root->children[1]->children[0]->pos);
      varNode->children[1]->type = createTypeInfo(varType->typeName, varType->custom, varType->isArray, varType->arrayDim, varType->line, varType->pos);
    } else {
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
              "Var declaration error. Var with name %s at %s:%d:%d was previously declared at %s:%d:%d\n",
              symbolName, filename, root->children[1]->children[0]->line,
              root->children[1]->children[0]->pos + 1, filename, gotSymbol->line, gotSymbol->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }    
    }
  } else {
    //use SEQ_DECLARE with childern type DECLARE
    varNode = newOperationTreeNode(SEQ_DECLARE, varCount, 0, 0, true);
    for (uint32_t i = 0; i < varCount; i++) {
      varNode->children[i] = buildVarDeclareHelper(root->children[i + 1], root->children[i + 1 + varCount], container, varType, sm, filename);
      const char *symbolName = root->children[i + 1]->children[0]->label;
      Symbol *gotSymbol = findSymbol(sm, symbolName);
      if (gotSymbol == NULL) {
        addSymbol(sm, symbolName, varType->typeName, varType->custom, varType->isArray, varType->arrayDim, root->children[i + 1]->children[0]->line, root->children[i + 1]->children[0]->pos);
      } else {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Var declaration error. Var with name %s at %s:%d:%d was previously declared at %s:%d:%d\n",
                symbolName, filename, root->children[i + 1]->children[0]->line,
                root->children[i + 1]->children[0]->pos + 1, filename, gotSymbol->line, gotSymbol->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }         
      }
    }
  }
  return varNode;
}

void printOperationTreeHelper(OperationTreeNode* node, int level) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%s (Line: %u, Pos: %u, Imaginary: %s, Type: %s)\n", node->label, node->line, node->pos,
           node->isImaginary ? "Yes" : "No", node->type != NULL ? node->type->typeName : "_");
    for (uint32_t i = 0; i < node->childCount; i++) {
        printOperationTreeHelper(node->children[i], level + 1);
    }
}

void printOperationTree(OperationTreeNode* root) {
    printOperationTreeHelper(root, 0);
}

OperationTreeErrorInfo* createOperationTreeErrorInfo(const char *message) {
    OperationTreeErrorInfo *errorInfo = (OperationTreeErrorInfo*)malloc(sizeof(OperationTreeErrorInfo));
    errorInfo->message = strdup(message);
    errorInfo->next = NULL;
    return errorInfo;
}

void addOperationTreeError(OperationTreeErrorContainer *container, const char *buffer) {
  if (container->error == NULL) {
    container->error = createOperationTreeErrorInfo(buffer);
  } else {
    OperationTreeErrorInfo *current = container->error;
    while (current->next != NULL) {
      OperationTreeErrorInfo *nextError = current->next;
      current = nextError;
    }
    current->next = createOperationTreeErrorInfo(buffer);
  }
}

void freeOperationTreeErrors(OperationTreeErrorInfo *error) {
  while (error != NULL) {
    OperationTreeErrorInfo *nextError = error->next;
    free(error->message);
    free(error);
    error = nextError;
  }
}