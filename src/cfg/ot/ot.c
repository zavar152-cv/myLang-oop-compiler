#include "ot.h"
#include "../tokens.h"
#include "../cfg.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

OperationTreeNode *newOperationTreeNode(const char *label, uint32_t childCount, uint32_t line, uint32_t pos, bool isImaginary) {
  OperationTreeNode *node = (OperationTreeNode *)malloc(sizeof(OperationTreeNode));
  node->label = strdup(label);
  node->childCount = childCount;
  node->children = (OperationTreeNode **)malloc(childCount * sizeof(OperationTreeNode *));
  node->line = line;
  node->pos = pos;
  node->isImaginary = isImaginary;
  node->type = NULL;
  node->offset = 0;
  node->isSpilled = false;
  node->reg = NULL;
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
  if (root->reg != NULL)
    free((void *)root->reg);
  free(root);
}

bool isBinaryOp(const char *label) {
  return strcmp(label, PLUS) == 0 ||
          strcmp(label, MINUS) == 0 ||
          strcmp(label, MUL) == 0 ||
          strcmp(label, DIV) == 0 ||
          strcmp(label, MOD) == 0 ||
          strcmp(label, LE) == 0 ||
          strcmp(label, GR) == 0 ||
          strcmp(label, LE_EQ) == 0 ||
          strcmp(label, GR_EQ) == 0 ||
          strcmp(label, EQ) == 0 ||
          strcmp(label, NEQ) == 0 ||
          strcmp(label, AND) == 0 ||
          strcmp(label, OR) == 0;
}

bool isArithmeticOp(const char *label) {
  return strcmp(label, PLUS) == 0 ||
          strcmp(label, MINUS) == 0 ||
          strcmp(label, MUL) == 0 ||
          strcmp(label, DIV) == 0 ||
          strcmp(label, MOD) == 0 ||
          strcmp(label, NEG) == 0;
}

bool isLogicalOp(const char *label) {
  return strcmp(label, AND) == 0 ||
          strcmp(label, OR) == 0 ||
          strcmp(label, NOT) == 0;
}

bool isEqOp(const char *label) {
  return strcmp(label, EQ) == 0 ||
          strcmp(label, NEQ) == 0;
}

bool isCmpOp(const char *label) {
  return  strcmp(label, LE) == 0 ||
          strcmp(label, GR) == 0 ||
          strcmp(label, LE_EQ) == 0 ||
          strcmp(label, GR_EQ) == 0 ||
          strcmp(label, EQ) == 0 ||
          strcmp(label, NEQ) == 0;
}

bool isUnaryOp(const char *label) {
  return strcmp(label, NEG) == 0 ||
          strcmp(label, NOT) == 0;
}

bool isLiteral(const char *label) {
  return strcmp(label, BOOL) == 0 ||
          strcmp(label, STR) == 0 ||
          strcmp(label, SYMB) == 0 ||
          strcmp(label, HEX) == 0 ||
          strcmp(label, BITS) == 0 ||
          strcmp(label, DEC) == 0;
}

bool isNumericType(const char *type) {
  return strcmp(type, "byte") == 0 ||
          strcmp(type, "int") == 0 ||
          strcmp(type, "uint") == 0 ||
          strcmp(type, "long") == 0 ||
          strcmp(type, "ulong") == 0;
}

bool isLogicalType(const char *type) {
  return strcmp(type, "bool") == 0;
}

bool isSymbType(const char *type) {
  return strcmp(type, "char") == 0;
}

bool isTextType(const char *type) {
  return strcmp(type, "string") == 0;
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

bool isBinaryOperationAllowed(const char *op, const char *lType, const char *rType) {
  if ((strcmp(op, PLUS) == 0) && (strcmp(lType, "string") == 0) && (strcmp(rType, "string") == 0)) {
    return true;
  } if (isArithmeticOp(op)) {
    return (isNumericType(lType) && isNumericType(rType));
  } else if (isEqOp(op)) {
    return true;
  } else if (isLogicalOp(op)) {
    return (isNumericType(lType) && isNumericType(rType)) || (isLogicalType(lType) && isLogicalType(rType));
  } else {
    return false;
  }
}

bool isUnaryOperationAllowed(const char *op, const char *type) {
  return isNumericType(type) && (isArithmeticOp(op) || isLogicalOp(op));
}

void checkTypeCompatibility(OperationTreeNode *lValueExprNode, OperationTreeNode *rValueExprNode, OperationTreeErrorContainer *container, const char* filename) {
  if (!lValueExprNode->type->custom && !lValueExprNode->type->isArray) {
    if (strcmp(lValueExprNode->type->typeName, "byte") == 0) {
      if (strcmp(rValueExprNode->label, LIT_READ) == 0 &&
          isCanBeByte(rValueExprNode->children[1]->label)) {
        TypeInfo *newTypeParent =
            createTypeInfo("byte", false, false, 0, rValueExprNode->type->line,
                           rValueExprNode->type->pos);
        TypeInfo *newTypeChild = createTypeInfo(
            "byte", false, false, 0, rValueExprNode->children[1]->type->line,
            rValueExprNode->children[1]->type->pos);
        freeTypeInfo(rValueExprNode->type);
        freeTypeInfo(rValueExprNode->children[1]->type);
        rValueExprNode->type = newTypeParent;
        rValueExprNode->children[1]->type = newTypeChild;
      } else if (strcmp(rValueExprNode->type->typeName, "byte") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Type error. Can't cast value at %s:%d:%d to byte\n", filename,
                 rValueExprNode->line, rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
    } else if (strcmp(lValueExprNode->type->typeName, "int") == 0) {
      if (strcmp(rValueExprNode->type->typeName, "byte") != 0 &&
          strcmp(rValueExprNode->type->typeName, "int") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Type error. Can't cast value at %s:%d:%d to int\n", filename,
                 rValueExprNode->line, rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
    } else if (strcmp(lValueExprNode->type->typeName, "uint") == 0) {
      if (strcmp(rValueExprNode->label, LIT_READ) == 0 &&
          isCanBeUnsignedInt(rValueExprNode->children[1]->label)) {
        TypeInfo *newTypeParent =
            createTypeInfo("uint", false, false, 0, rValueExprNode->type->line,
                           rValueExprNode->type->pos);
        TypeInfo *newTypeChild = createTypeInfo(
            "uint", false, false, 0, rValueExprNode->children[1]->type->line,
            rValueExprNode->children[1]->type->pos);
        freeTypeInfo(rValueExprNode->type);
        freeTypeInfo(rValueExprNode->children[1]->type);
        rValueExprNode->type = newTypeParent;
        rValueExprNode->children[1]->type = newTypeChild;
      } else if (strcmp(rValueExprNode->type->typeName, "uint") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Type error. Can't cast value at %s:%d:%d to uint\n", filename,
                 rValueExprNode->line, rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
    } else if (strcmp(lValueExprNode->type->typeName, "long") == 0) {
      if (strcmp(rValueExprNode->label, LIT_READ) == 0 &&
          isCanBeLong(rValueExprNode->children[1]->label)) {
        TypeInfo *newTypeParent =
            createTypeInfo("long", false, false, 0, rValueExprNode->type->line,
                           rValueExprNode->type->pos);
        TypeInfo *newTypeChild = createTypeInfo(
            "long", false, false, 0, rValueExprNode->children[1]->type->line,
            rValueExprNode->children[1]->type->pos);
        freeTypeInfo(rValueExprNode->type);
        freeTypeInfo(rValueExprNode->children[1]->type);
        rValueExprNode->type = newTypeParent;
        rValueExprNode->children[1]->type = newTypeChild;
      } else if (strcmp(rValueExprNode->type->typeName, "byte") != 0 &&
                 strcmp(rValueExprNode->type->typeName, "int") != 0 &&
                 strcmp(rValueExprNode->type->typeName, "uint") != 0 &&
                 strcmp(rValueExprNode->type->typeName, "long") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Type error. Can't cast value at %s:%d:%d to long\n", filename,
                 rValueExprNode->line, rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
    } else if (strcmp(lValueExprNode->type->typeName, "ulong") == 0) {
      if (strcmp(rValueExprNode->label, LIT_READ) == 0 &&
          isCanBeUnsignedLong(rValueExprNode->children[1]->label)) {
        TypeInfo *newTypeParent =
            createTypeInfo("ulong", false, false, 0, rValueExprNode->type->line,
                           rValueExprNode->type->pos);
        TypeInfo *newTypeChild = createTypeInfo(
            "ulong", false, false, 0, rValueExprNode->children[1]->type->line,
            rValueExprNode->children[1]->type->pos);
        freeTypeInfo(rValueExprNode->type);
        freeTypeInfo(rValueExprNode->children[1]->type);
        rValueExprNode->type = newTypeParent;
        rValueExprNode->children[1]->type = newTypeChild;
      } else if (strcmp(rValueExprNode->type->typeName, "uint") != 0 &&
                 strcmp(rValueExprNode->type->typeName, "ulong") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Type error. Can't cast value at %s:%d:%d to ulong\n",
                 filename, rValueExprNode->line, rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
    } else if (strcmp(lValueExprNode->type->typeName, "bool") == 0) {
      if (strcmp(rValueExprNode->type->typeName, "bool") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Type error. Can't cast value at %s:%d:%d to bool\n", filename,
                 rValueExprNode->line, rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
    } else if (strcmp(lValueExprNode->type->typeName, "char") == 0) {
      if (strcmp(rValueExprNode->type->typeName, "char") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Type error. Can't cast value at %s:%d:%d to char\n", filename,
                 rValueExprNode->line, rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
    } else if (strcmp(lValueExprNode->type->typeName, "string") == 0) {
      if (strcmp(rValueExprNode->type->typeName, "string") != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Type error. Can't cast value at %s:%d:%d to string\n",
                 filename, rValueExprNode->line, rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
    }
  } else if (lValueExprNode->type->isArray) {
    if (rValueExprNode->type->isArray) {
      if (strcmp(lValueExprNode->type->typeName,
                 rValueExprNode->type->typeName) != 0) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Type error. Can't cast array at %s:%d:%d to array at "
                 "%s:%d:%d. Array casting is't allowed\n",
                 filename, rValueExprNode->line, rValueExprNode->pos + 1,
                 filename, lValueExprNode->line, lValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
    } else {
      if (strcmp(lValueExprNode->type->typeName,
                 rValueExprNode->type->typeName) != 0) {
        char buffer[1024];
        snprintf(
            buffer, sizeof(buffer),
            "Type error. Can't cast value at %s:%d:%d to array at %s:%d:%d.\n",
            filename, rValueExprNode->line, rValueExprNode->pos + 1, filename,
            lValueExprNode->line, lValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      } else {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Assign error. Can't assign %s to array %s:%d:%d\n",
                rValueExprNode->type->typeName, filename, rValueExprNode->line,
                rValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }           
      }
    }
  } else if (lValueExprNode->type->custom) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer),
             "Type error. Custom types are not allowed at %s:%d:%d\n", filename,
             rValueExprNode->line, rValueExprNode->pos + 1);
    if (container->error == NULL) {
      container->error = createOperationTreeErrorInfo(buffer);
    } else {
      addOperationTreeError(container, buffer);
    }
  }

  if (lValueExprNode->type->isArray) {
    if (strcmp(lValueExprNode->label, INDEX) == 0) {
      OperationTreeNode *indexNode = lValueExprNode;
      int dimI = 0;
      while (strcmp(indexNode->label, INDEX) == 0) {
        indexNode = indexNode->children[0];
        dimI++;
      }
      if (dimI != lValueExprNode->type->arrayDim) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Index error. Check indexing and array dimension match %s:%d:%d\n",
                filename, lValueExprNode->line,
                lValueExprNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }   
      }
    } else if (rValueExprNode->type->isArray && (lValueExprNode->type->arrayDim != rValueExprNode->type->arrayDim)) {
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
              "Assign error. Can't assign %s to array %s:%d:%d\n",
              rValueExprNode->type->typeName, filename, rValueExprNode->line,
              rValueExprNode->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }        
    }
  }

  if (rValueExprNode->type->isArray) {
    if (!lValueExprNode->type->isArray) {
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
               "Read error. Can't assign array to %s %s:%d:%d\n",
               lValueExprNode->type->typeName, filename, rValueExprNode->line, rValueExprNode->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }
    }
  }
}

ArgumentInfo **listToArray(ArgumentInfo *head, uint32_t argumentsCount) {
    uint32_t size = argumentsCount;
    ArgumentInfo *current;
    if (size == 0) {
        return NULL;
    }
    ArgumentInfo **array = (ArgumentInfo **)malloc(size * sizeof(ArgumentInfo *));
    if (array == NULL) {
        return NULL;
    }
    current = head;
    for (int32_t i = size - 1; i >= 0; i--) {
        array[i] = current;
        current = current->next;
    }
    return array;
}

typedef enum {
    CONV_TYPE_BYTE,
    CONV_TYPE_INT,
    CONV_TYPE_UINT,
    CONV_TYPE_LONG,
    CONV_TYPE_ULONG
} NumberType;

char* convertHexOrBitToDecimalString(const char* input, NumberType type, char* output, size_t output_size)
{
    int base = 0;
    const char* s = input;

    if (s[0] == '0') {
        if (s[1] == 'x' || s[1] == 'X') {
            base = 16;
            s += 2;
        } else if (s[1] == 'b' || s[1] == 'B') {
            base = 2;
            s += 2;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }

    errno = 0;
    char* endptr;
    uint64_t value = strtoull(s, &endptr, base);
    if (errno != 0 || *endptr != '\0') {
        return NULL;
    }

    switch (type) {
        case CONV_TYPE_BYTE:
            if (value > UINT8_MAX) {
                return NULL;
            }
            snprintf(output, output_size, "%u", (unsigned int)(uint8_t)value);
            break;
        case CONV_TYPE_INT:
            if (value > INT32_MAX) {
                return NULL;
            }
            snprintf(output, output_size, "%d", (int32_t)value);
            break;
        case CONV_TYPE_UINT:
            if (value > UINT32_MAX) {
                return NULL;
            }
            snprintf(output, output_size, "%u", (uint32_t)value);
            break;
        case CONV_TYPE_LONG:
            if (value > INT64_MAX) {
                return NULL;
            }
            snprintf(output, output_size, "%ld", (int64_t)value);
            break;
        case CONV_TYPE_ULONG:
            snprintf(output, output_size, "%lu", value);
            break;
        default:
            return NULL;
    }
    return output;
}


OperationTreeNode *buildExprOperationTreeFromAstNode(MyAstNode* root, bool isLvalue, bool isFunctionName, OperationTreeErrorContainer *container, ScopeManager *sm, FunctionTable *functionTable, const char* filename) {
  if (strcmp(root->label, ASSIGN) == 0) {
    //left - EXPR
    //right - EXPR
    OperationTreeNode *writeOpNode = newOperationTreeNode(WRITE, 2, root->line, root->pos, root->isImaginary);
    OperationTreeNode *lValueExprNode = buildExprOperationTreeFromAstNode(root->children[0], true, false, container, sm, functionTable, filename);
    OperationTreeNode *rValueExprNode = buildExprOperationTreeFromAstNode(root->children[1], false, false, container, sm, functionTable, filename);
    
    checkTypeCompatibility(lValueExprNode, rValueExprNode, container, filename);

    writeOpNode->children[0] = lValueExprNode;
    writeOpNode->children[1] = rValueExprNode;
    writeOpNode->type = copyTypeInfo(lValueExprNode->type);
    return writeOpNode;
  } else if (strcmp(root->label, FUNC_CALL) == 0) {
    //if count == 2
    //left - EXPR_LIST
    //right - EXPR

    //if count == 1
    //child - EXPR
    if (root->childCount == 2) {
      OperationTreeNode *funcNameNode = buildExprOperationTreeFromAstNode(root->children[1], false, true, container, sm, functionTable, filename);
      OperationTreeNode *callNode = newOperationTreeNode(OT_CALL, 1 + root->children[0]->childCount, funcNameNode->line, funcNameNode->pos, funcNameNode->isImaginary);
      callNode->children[0] = funcNameNode;
      callNode->type = copyTypeInfo(funcNameNode->type);
      FunctionEntry *func = findFunctionEntry(functionTable, funcNameNode->label);
      for (uint32_t i = 0; i < root->children[0]->childCount; i++) {
        OperationTreeNode *argNode = buildExprOperationTreeFromAstNode(root->children[0]->children[i], false, false, container, sm, functionTable, filename);
        callNode->children[1 + i] = argNode;
      }

      if (func != NULL) {
        if (!func->isVarargs) {
          if (callNode->childCount - 1 == func->argumentsCount) {
            for (uint32_t i = callNode->childCount - 1; i > 0; i--) {
              if (func != NULL) {
                ArgumentInfo *arg = func->arguments;
                uint32_t j = callNode->childCount - 1;
                while (j != i) {
                  arg = arg->next;
                  j--;
                }
                OperationTreeNode *fakeArgNode = newOperationTreeNode(arg->name, 0, arg->line, arg->pos, false);
                fakeArgNode->type = copyTypeInfo(arg->type);
                checkTypeCompatibility(fakeArgNode, callNode->children[i], container, filename);
                destroyOperationTreeNodeTree(fakeArgNode);
              } 
            }
            //don't show error, it was shown before
          } else {
            char buffer[1024];
            snprintf(buffer, sizeof(buffer),
                    "Call error. Different count of parameters and arguments in calling function %s at %s:%d:%d\n",
                    func->functionName, filename, callNode->line,
                    callNode->pos + 1);
            if (container->error == NULL) {
              container->error = createOperationTreeErrorInfo(buffer);
            } else {
              addOperationTreeError(container, buffer);
            }
          }
        } else {
          if (callNode->childCount - 1 >= func->argumentsCount) {
            ArgumentInfo **argArray = listToArray(func->arguments, func->argumentsCount);
            for (uint32_t i = 0; i < func->argumentsCount; i++) {
              OperationTreeNode *fakeArgNode = newOperationTreeNode(argArray[i]->name, 0, argArray[i]->line, argArray[i]->pos, false);
              fakeArgNode->type = copyTypeInfo(argArray[i]->type);
              checkTypeCompatibility(fakeArgNode, callNode->children[i + 1], container, filename);
              destroyOperationTreeNodeTree(fakeArgNode);
            }
            ArgumentInfo *lastArg = argArray[func->argumentsCount - 1];
            for (uint32_t i = func->argumentsCount; i < callNode->childCount; i++) {
              OperationTreeNode *fakeArgNode = newOperationTreeNode(lastArg->name, 0, lastArg->line, lastArg->pos, false);
              fakeArgNode->type = copyTypeInfo(lastArg->type);
              checkTypeCompatibility(fakeArgNode, callNode->children[i], container, filename);
              destroyOperationTreeNodeTree(fakeArgNode);
            }
            free(argArray);
          } else {
            char buffer[1024];
            snprintf(buffer, sizeof(buffer),
                    "Call error. Different count of parameters and arguments in calling function %s at %s:%d:%d\n",
                    func->functionName, filename, callNode->line,
                    callNode->pos + 1);
            if (container->error == NULL) {
              container->error = createOperationTreeErrorInfo(buffer);
            } else {
              addOperationTreeError(container, buffer);
            }            
          }            
        }
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
      OperationTreeNode *funcNameNode = buildExprOperationTreeFromAstNode(root->children[0], false, true, container, sm, functionTable, filename);
      OperationTreeNode *callNode = newOperationTreeNode(OT_CALL, 1, funcNameNode->line, funcNameNode->pos, funcNameNode->isImaginary);
      callNode->children[0] = funcNameNode;
      callNode->type = copyTypeInfo(funcNameNode->type);
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
      OperationTreeNode *indexNameNode = buildExprOperationTreeFromAstNode(root->children[0], isLvalue, isFunctionName, container, sm, functionTable, filename);
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
      OperationTreeNode *indexNameNode = buildExprOperationTreeFromAstNode(root->children[1], isLvalue, isFunctionName, container, sm, functionTable, filename);
      OperationTreeNode *indexNode = newOperationTreeNode(INDEX, 1 + root->children[0]->childCount, indexNameNode->line, indexNameNode->pos, indexNameNode->isImaginary);
      indexNode->children[0] = indexNameNode;
      indexNode->type = copyTypeInfo(indexNameNode->type);
      if (indexNode->type->isArray) {
        indexNode->type->arrayDim = indexNode->type->arrayDim - 1;
        if (indexNode->type->arrayDim == 0) {
          indexNode->type->isArray = false;
        }
      } else if (strcmp(indexNode->type->typeName, "string") == 0) {
        freeTypeInfo(indexNode->type);
        freeTypeInfo(indexNameNode->type);
        indexNode->type = createTypeInfo("char", false, false, 0, indexNode->line, indexNode->pos);
        indexNameNode->type = createTypeInfo("char", false, true, 1, indexNode->line, indexNode->pos);
      }
      if (!indexNameNode->type->isArray) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Index error. Index can be applied only for arrays or strings at %s:%d:%d\n",
                filename, indexNameNode->line,
                indexNameNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }        
      }
      for (uint32_t i = 0; i < root->children[0]->childCount; i++) {
        OperationTreeNode *iNode = buildExprOperationTreeFromAstNode(root->children[0]->children[i], false, false, container, sm, functionTable, filename);
        indexNode->children[1 + i] = iNode;
        if (strcmp(iNode->label, WRITE) == 0) {
          char buffer[1024];
          snprintf(buffer, sizeof(buffer),
                  "Index error. Can't use write operations as indexes at %s:%d:%d\n",
                  filename, iNode->line,
                  iNode->pos + 1);
          if (container->error == NULL) {
            container->error = createOperationTreeErrorInfo(buffer);
          } else {
            addOperationTreeError(container, buffer);
          }          
        }
        if (strcmp(iNode->type->typeName, "int") != 0) {
          char buffer[1024];
          snprintf(buffer, sizeof(buffer),
                  "Index error. Only int type can be used for indexing at %s:%d:%d\n",
                  filename, iNode->line,
                  iNode->pos + 1);
          if (container->error == NULL) {
            container->error = createOperationTreeErrorInfo(buffer);
          } else {
            addOperationTreeError(container, buffer);
          }
        }
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
    OperationTreeNode *leftExprNode = buildExprOperationTreeFromAstNode(root->children[0], false, false, container, sm, functionTable, filename);
    OperationTreeNode *rightExprNode = buildExprOperationTreeFromAstNode(root->children[1], false, false, container, sm, functionTable, filename);

    if (isCmpOp(root->label)) {

      if (isCmpOp(leftExprNode->label)) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                 "Compare error. Can't use result of compare operation as "
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
                 "Compare error. Can't use result of compare operation as "
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

    if (leftExprNode->type->isArray || rightExprNode->type->isArray || leftExprNode->type->custom || rightExprNode->type->isArray) {
      binaryOpNode->type = createTypeInfo("_", false, false, 0, binaryOpNode->line, binaryOpNode->pos);
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
               "Operation error. Can't apply binary operation '%s' for custom type or array %s at %s:%d:%d\n",
               binaryOpNode->label, leftExprNode->type->typeName, filename,
               binaryOpNode->line, binaryOpNode->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }
    } else {
      if (strcmp(leftExprNode->type->typeName, rightExprNode->type->typeName) == 0) {
        if (isBinaryOperationAllowed(binaryOpNode->label, leftExprNode->type->typeName, rightExprNode->type->typeName)) {
          binaryOpNode->type = copyTypeInfo(leftExprNode->type);
        } else {
          binaryOpNode->type = createTypeInfo("_", false, false, 0, binaryOpNode->line, binaryOpNode->pos);
          char buffer[1024];
          snprintf(buffer, sizeof(buffer),
                  "Operation error. Can't apply binary operation '%s' for type %s at %s:%d:%d\n",
                  binaryOpNode->label, leftExprNode->type->typeName,
                  filename, binaryOpNode->line,
                  binaryOpNode->pos + 1);
          if (container->error == NULL) {
            container->error = createOperationTreeErrorInfo(buffer);
          } else {
            addOperationTreeError(container, buffer);
          }
        }
      } else {
        binaryOpNode->type = createTypeInfo("_", false, false, 0, binaryOpNode->line, binaryOpNode->pos);
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Type error. Can't perform binary operation '%s' with different types (%s and %s) at %s:%d:%d\n",
                binaryOpNode->label, leftExprNode->type->typeName, rightExprNode->type->typeName,
                filename, binaryOpNode->line,
                binaryOpNode->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }
      }
    }

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
    OperationTreeNode *exprNode = buildExprOperationTreeFromAstNode(root->children[0], false, false, container, sm, functionTable, filename);
    OperationTreeNode *unaryOpNode = newOperationTreeNode(root->label, 1, exprNode->line, exprNode->pos, root->isImaginary);
    unaryOpNode->children[0] = exprNode;
    if (isUnaryOperationAllowed(unaryOpNode->label, exprNode->type->typeName)) {
      unaryOpNode->type = copyTypeInfo(exprNode->type);
    } else {
      unaryOpNode->type = copyTypeInfo(exprNode->type);
      char buffer[1024];
      snprintf(buffer, sizeof(buffer),
              "Operation error. Can't apply unary operation '%s' for type %s at %s:%d:%d\n",
              unaryOpNode->label, exprNode->type->typeName,
              filename, exprNode->line,
              exprNode->pos + 1);
      if (container->error == NULL) {
        container->error = createOperationTreeErrorInfo(buffer);
      } else {
        addOperationTreeError(container, buffer);
      }
    }
    return unaryOpNode;
  } else if (strcmp(root->label, IDENTIFIER) == 0) {
    //child - value, terminal
    OperationTreeNode *idValueNode = newOperationTreeNode(root->children[0]->label, 0, root->children[0]->line, root->children[0]->pos, root->children[0]->isImaginary);
    Symbol *gotSymbol = findSymbol(sm, root->children[0]->label);
    if (!isFunctionName) {
      if (gotSymbol == NULL) {
        idValueNode->type = createTypeInfo("_", false, false, 0, root->children[0]->line, root->children[0]->pos);
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Var not found error. Var with name %s at %s:%d:%d is not declared\n",
                root->children[0]->label, filename, root->children[0]->line, root->children[0]->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }    
      } else {
        idValueNode->type = createTypeInfo(gotSymbol->typeName, gotSymbol->custom, gotSymbol->isArray, gotSymbol->arrayDim, gotSymbol->line, gotSymbol->pos);
      }
    } else {
      FunctionEntry *entry = findFunctionEntry(functionTable, root->children[0]->label);
      if (entry == NULL) {
        idValueNode->type = createTypeInfo("_", false, false, 0, root->children[0]->line, root->children[0]->pos);
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Function not found error. Function with name %s at %s:%d:%d is not declared\n",
                root->children[0]->label, filename, root->children[0]->line, root->children[0]->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }    
      } else {
        idValueNode->type = copyTypeInfo(entry->returnType);
      }
    }

    if (isLvalue | isFunctionName) {
      return idValueNode;
    } else {
      OperationTreeNode *readNode = newOperationTreeNode(READ, 1, root->children[0]->line, root->children[0]->pos, true);
      readNode->type = copyTypeInfo(idValueNode->type);
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
    } else if (strcmp(literalTypeNode->label, HEX) == 0) {
      char *output = (char*)malloc(100);
      char *converted = convertHexOrBitToDecimalString(literalValueNode->label, CONV_TYPE_INT, output, sizeof(output));
      if (converted == NULL) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Represantation error. Can't represent a hex value %s as int, uint, long or ulong at %s:%d:%d\n",
                literalValueNode->label, filename, root->children[0]->line,
                root->children[0]->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }           
      } else {
        free((void *)literalValueNode->label);
        literalValueNode->label = strdup(converted);
        if (!isCanBeInt(converted)) {
          if (isCanBeUnsignedInt(converted)) {
            litReadNode->children[1]->type = createTypeInfo("uint", false, false, 0, root->children[0]->line, root->children[0]->pos);
          } else if (isCanBeLong(converted)) {
            litReadNode->children[1]->type = createTypeInfo("long", false, false, 0, root->children[0]->line, root->children[0]->pos);
          } else if (isCanBeUnsignedLong(converted)) {
            litReadNode->children[1]->type = createTypeInfo("ulong", false, false, 0, root->children[0]->line, root->children[0]->pos);
          } else {
            litReadNode->children[1]->type = createTypeInfo("_", false, false, 0, root->children[0]->line, root->children[0]->pos);
            char buffer[1024];
            snprintf(buffer, sizeof(buffer),
                    "Type error. Can't represent a hex value %s as int, uint, long or ulong at %s:%d:%d\n",
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
        free(converted);
      }
    } else if (strcmp(literalTypeNode->label, BITS) == 0) {
      char *output = (char*)malloc(100);
      char *converted = convertHexOrBitToDecimalString(literalValueNode->label, CONV_TYPE_INT, output, sizeof(output));
      if (converted == NULL) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Represantation error. Can't represent a binary value %s as int, uint, long or ulong at %s:%d:%d\n",
                literalValueNode->label, filename, root->children[0]->line,
                root->children[0]->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }           
      } else {
        free((void *)literalValueNode->label);
        literalValueNode->label = strdup(converted);
        if (!isCanBeInt(converted)) {
          if (isCanBeUnsignedInt(converted)) {
            litReadNode->children[1]->type = createTypeInfo("uint", false, false, 0, root->children[0]->line, root->children[0]->pos);
          } else if (isCanBeLong(converted)) {
            litReadNode->children[1]->type = createTypeInfo("long", false, false, 0, root->children[0]->line, root->children[0]->pos);
          } else if (isCanBeUnsignedLong(converted)) {
            litReadNode->children[1]->type = createTypeInfo("ulong", false, false, 0, root->children[0]->line, root->children[0]->pos);
          } else {
            litReadNode->children[1]->type = createTypeInfo("_", false, false, 0, root->children[0]->line, root->children[0]->pos);
            char buffer[1024];
            snprintf(buffer, sizeof(buffer),
                    "Type error. Can't represent a binary value %s as int, uint, long or ulong at %s:%d:%d\n",
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
      }
      free(converted);
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

OperationTreeNode *buildVarDeclareHelper(MyAstNode* id, MyAstNode* init, OperationTreeErrorContainer *container, TypeInfo* varType, ScopeManager *sm, FunctionTable *functionTable, const char* filename) {
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
      varInitExprNode = buildExprOperationTreeFromAstNode(init->children[1], false, false, container, sm, functionTable, filename);
      OperationTreeNode *helperNode = newOperationTreeNode(WRITE, 2, id->children[0]->line, id->children[0]->pos, false);
      helperNode->children[0] = newOperationTreeNode(id->children[0]->label, 0, id->children[0]->line, id->children[0]->pos, false);
      helperNode->children[0]->type = copyTypeInfo(varType);
      helperNode->children[1] = varInitExprNode;

      checkTypeCompatibility(helperNode->children[0], varInitExprNode, container, filename);
  
      helperNode->type = copyTypeInfo(varType);
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
      varInitExprNode = buildExprOperationTreeFromAstNode(init->children[1], false, false, container, sm, functionTable, filename);
      OperationTreeNode *helperNode = newOperationTreeNode(WRITE, 2, id->children[0]->line, id->children[0]->pos, false);
      helperNode->children[0] = newOperationTreeNode(id->children[0]->label, 0, id->children[0]->line, id->children[0]->pos, false);
      helperNode->children[0]->type = copyTypeInfo(varType);
      helperNode->children[1] = varInitExprNode;

      checkTypeCompatibility(helperNode->children[0], varInitExprNode, container, filename);

      helperNode->type = copyTypeInfo(varType);
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

OperationTreeNode *buildVarOperationTreeFromAstNode(MyAstNode* root, OperationTreeErrorContainer *container, TypeInfo* varType, ScopeManager *sm, FunctionTable *functionTable, const char* filename) {
  assert(strcmp(root->children[0]->label, TYPEREF) == 0);

  uint32_t varCount = (root->childCount - 1) / 2;

  OperationTreeNode *varNode;
  if (varCount == 1) {
    //use DECLARE node
    varNode = buildVarDeclareHelper(root->children[1], root->children[2], container, varType, sm, functionTable, filename);
    const char *symbolName = root->children[1]->children[0]->label;
    Symbol *gotSymbol = findSymbol(sm, symbolName);
    if (gotSymbol == NULL) {
      addSymbol(sm, symbolName, varType->typeName, varType->custom, varType->isArray, varType->arrayDim, root->children[1]->children[0]->line, root->children[1]->children[0]->pos);
      varNode->children[1]->type = copyTypeInfo(varType);
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
    uint32_t i = 1;
    uint32_t varI = 0;
    while (i + 1 < root->childCount) {
      varNode->children[varI] = buildVarDeclareHelper(root->children[i], root->children[i + 1], container, varType, sm, functionTable, filename);
      const char *symbolName = root->children[i]->children[0]->label;
      Symbol *gotSymbol = findSymbol(sm, symbolName);
      if (gotSymbol == NULL) {
        addSymbol(sm, symbolName, varType->typeName, varType->custom, varType->isArray, varType->arrayDim, root->children[i]->children[0]->line, root->children[i]->children[0]->pos);
        varNode->children[varI]->type = copyTypeInfo(varType);
      } else {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "Var declaration error. Var with name %s at %s:%d:%d was previously declared at %s:%d:%d\n",
                symbolName, filename, root->children[i]->children[0]->line,
                root->children[i]->children[0]->pos + 1, filename, gotSymbol->line, gotSymbol->pos + 1);
        if (container->error == NULL) {
          container->error = createOperationTreeErrorInfo(buffer);
        } else {
          addOperationTreeError(container, buffer);
        }         
      }
      i += 2;
      varI++;
    }
    varNode->type = copyTypeInfo(varNode->children[0]->type);
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
    printf("%s (Line: %u, Pos: %u, Imaginary: %s, Type: %s, Array: %d, Reg: %s)\n", node->label, node->line, node->pos,
           node->isImaginary ? "Yes" : "No", node->type != NULL ? node->type->typeName : "_", node->type != NULL ? node->type->arrayDim : -1, node->reg);
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

TypeInfo *copyTypeInfo(TypeInfo *typeInfo) {
    if (!typeInfo) {
        return NULL;
    }

    TypeInfo *copy = createTypeInfo(
        typeInfo->typeName,
        typeInfo->custom,
        typeInfo->isArray,
        typeInfo->arrayDim,
        typeInfo->line,
        typeInfo->pos
    );

    copy->isVarargs = typeInfo->isVarargs;

    if (!copy) {
        return NULL;
    }

    copy->next = copyTypeInfo(typeInfo->next);

    return copy;
}

ArgumentInfo *copyArgumentInfo(ArgumentInfo *argInfo) {
    if (!argInfo) {
        return NULL;
    }

    ArgumentInfo *copy = (ArgumentInfo *)malloc(sizeof(ArgumentInfo));
    if (!copy) {
        return NULL;
    }

    copy->type = copyTypeInfo(argInfo->type);
    if (argInfo->type && !copy->type) {
        free(copy);
        return NULL;
    }

    if (argInfo->name) {
        copy->name = strdup(argInfo->name);
        if (!copy->name) {
            if (copy->type) {
                freeTypeInfo(copy->type);
            }
            free(copy);
            return NULL;
        }
    } else {
        copy->name = NULL;
    }

    copy->line = argInfo->line;
    copy->pos = argInfo->pos;

    copy->next = copyArgumentInfo(argInfo->next);

    return copy;
}

FunctionEntry *createFunctionEntry(const char *fileName, const char *functionName, TypeInfo *returnType, ArgumentInfo *arguments, bool isVarargs, bool isBuiltin, uint32_t argumentsCount, uint32_t line, uint32_t pos) {
    FunctionEntry *entry = (FunctionEntry *)malloc(sizeof(FunctionEntry));
    if (!entry) {
        return NULL;
    }
    entry->fileName = strdup(fileName);
    entry->functionName = strdup(functionName);
    entry->returnType = returnType;
    entry->arguments = arguments;
    entry->next = NULL;
    entry->line = line;
    entry->pos = pos;
    entry->argumentsCount = argumentsCount;
    entry->isVarargs = isVarargs;
    entry->isBuiltin = isBuiltin;
    entry->locals = NULL;
    return entry;
}

void freeFunctionEntry(FunctionEntry *entry, void (*free_value)(void *)) {
    if (!entry) {
        return;
    }
    freeTypeInfo(entry->returnType);
    freeArguments(entry->arguments);
    free(entry->fileName);
    free(entry->functionName);
    freeHashTable(entry->locals, free_value);
    free(entry);
}

FunctionTable *createFunctionTable(void) {
    FunctionTable *table = (FunctionTable *)malloc(sizeof(FunctionTable));
    if (!table) {
        return NULL;
    }
    table->entry = NULL;
    return table;
}

void freeFunctionTable(FunctionTable *table, void (*free_value)(void *)) {
    if (!table) {
        return;
    }
    FunctionEntry *current = table->entry;
    while (current) {
        FunctionEntry *next = current->next;
        freeFunctionEntry(current, free_value);
        current = next;
    }
    free(table);
}

void addFunctionTable(FunctionTable *table, FunctionEntry *entry) {
    if (!table || !entry) {
        return;
    }

    entry->next = table->entry;
    table->entry = entry;
}

FunctionEntry *findFunctionEntry(FunctionTable *table, const char *functionName) {
    if (!table || !functionName) {
        return NULL;
    }

    FunctionEntry *current = table->entry;
    while (current != NULL) {
        if (strcmp(current->functionName, functionName) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

uint8_t getTypeSize(const char *type, bool custom, bool array) {
  if (custom | array) {
    return 8;
  }

  if (strcmp(type, "byte") == 0) {
    return 1;
  } else if (strcmp(type, "int") == 0) {
    return 4;
  } else if (strcmp(type, "uint") == 0) {
    return 4;
  } else if (strcmp(type, "long") == 0) {
    return 8;
  } else if (strcmp(type, "ulong") == 0) {
    return 8;
  } else if (strcmp(type, "char") == 0) {
    return 1;
  } else if (strcmp(type, "bool") == 0) {
    return 1;
  }
}