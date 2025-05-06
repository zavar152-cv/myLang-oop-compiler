#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <argp.h>
#include <libgen.h>
#include <string.h>
#include <time.h>

#include "asm/stringbuffer/stringbuffer.h"
#include "cfg/ot/ot.h"
#include "grammar/myLang.h"
#include "./dotUtils/dotUtils.h"
#include "cfg/cfg.h"
#include "cfg/cg/cg.h"
#include "asm/symbols.h"
#include "asm/codegen/codegen.h"

struct arguments {
    char **input_files;
    char *output_dir;
    char *asm_dir;
    int debug;
    int ot;
    int input_file_count;
};

static struct argp_option options[] = {
    { "debug",  'd', 0,       0, "Enable debug output" },
    { "output", 'o', "DIR",   0, "Output directory name for CFG" },
    { "operation tree", 't', 0,   0, "Draw operation tree in dot with CFG" },
    { "asm", 'a', "DIR",   0, "Output directory name for ASM" },
    { 0 }
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'd':
            arguments->debug = 1;
            break;
        case 't':
            arguments->ot = 1;
            break;
        case 'o':
            arguments->output_dir = arg;
            break;
        case 'a':
            arguments->asm_dir = arg;
            break;
        case ARGP_KEY_ARG:
            arguments->input_files = realloc(arguments->input_files, sizeof(char*) * (arguments->input_file_count + 1));
            if (!arguments->input_files) {
                argp_failure(state, 1, ENOMEM, "Out of memory");
            }
            arguments->input_files[arguments->input_file_count] = arg;
            arguments->input_file_count++;
            break;
        case ARGP_KEY_END:
            if (arguments->input_file_count == 0) {
                argp_usage(state);
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static char args_doc[] = "INPUT_FILES...";

static char doc[] = "Compiler";

static struct argp argp = { options, parse_opt, args_doc, doc };

char *concat(char *original, char *suffix) {
  char *newString = NULL;
  size_t originalLength = strlen(original);
  size_t suffixLength = strlen(suffix);
  size_t totalLength = originalLength + suffixLength + 1;

  newString = malloc(totalLength);
  strcpy(newString, original);

  strcat(newString, suffix);
  return newString;
}

char* getFileNameWithoutExtension(const char* filePath) {
    char *pathCopy = strdup(filePath);
    char *baseName = basename(pathCopy);
    char *dot = strrchr(baseName, '.');
    if (dot != NULL) {
        *dot = '\0';
    }
    char *result = strdup(baseName);
    free(pathCopy);
    return result;
}

char* getOutputFileName(const char* sourceFilePath, const char* functionName, const char* ext, const char* outputDir) {
    char *sourceName = getFileNameWithoutExtension(sourceFilePath);
    size_t totalLength = strlen(sourceName) + 1 + strlen(functionName) + 1 + strlen(ext) + 1;
    char *fileName = (char*)malloc(totalLength);
    snprintf(fileName, totalLength, "%s.%s.%s", sourceName, functionName, ext);

    char *outputFilePath;
    if (outputDir != NULL) {
        size_t dirLength = strlen(outputDir);
        if (outputDir[dirLength - 1] == '/') {
            dirLength--;
        }
        size_t pathLength = dirLength + 1 + strlen(fileName) + 1;
        outputFilePath = (char*)malloc(pathLength);
        snprintf(outputFilePath, pathLength, "%.*s/%s", (int)dirLength, outputDir, fileName);
    } else {
        char *pathCopy = strdup(sourceFilePath);
        char *dirName = dirname(pathCopy);
        size_t pathLength = strlen(dirName) + 1 + strlen(fileName) + 1;
        outputFilePath = (char*)malloc(pathLength);
        snprintf(outputFilePath, pathLength, "%s/%s", dirName, fileName);
        free(pathCopy);
    }

    free(sourceName);
    free(fileName);

    return outputFilePath;
}

char* getDirectory(const char* path) {
    if (path == NULL) {
        return NULL;
    }

    char* path_copy = strdup(path);
    if (path_copy == NULL) {
        return NULL;
    }

    char* last_slash = strrchr(path_copy, '/');
#ifdef _WIN32
    char* last_backslash = strrchr(path_copy, '\\');
    if (last_backslash != NULL && (last_slash == NULL || last_backslash > last_slash)) {
        last_slash = last_backslash;
    }
#endif

    if (last_slash != NULL) {
        *last_slash = '\0';
        char* directory = strdup(path_copy);
        free(path_copy);
        return directory;
    } else {
        free(path_copy);
        return NULL;
    }
}

void freeLocalVarAsVoid(void *local) {
  freeLocalVar((LocalVar *)local);
}

void freeConstVarAsVoid(void *local) {
  freeConstVar((ConstVar *)local);
}

int main(int argc, char *argv[]) {

    struct arguments arguments;

    arguments.debug = 0;
    arguments.ot = 0;
    arguments.output_dir = NULL;
    arguments.asm_dir = NULL;
    arguments.input_files = NULL;
    arguments.input_file_count = 0;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if (arguments.debug) {
        printf("Debug output is enabled\n");
    }

    printf("Input files:\n");
    for (int i = 0; i < arguments.input_file_count; i++) {
        printf("  %s\n", arguments.input_files[i]);
    }

    FilesToAnalyze files;
    files.filesCount = arguments.input_file_count;

    files.result = malloc(sizeof(MyLangResult*) * files.filesCount);
    files.fileName = arguments.input_files;

    for (int i = 0; i < arguments.input_file_count; i++) {
        MyLangResult *result = malloc(sizeof(MyLangResult));
        parseMyLangFromFile(result, arguments.input_files[i], arguments.debug);
        if (!result->isValid && arguments.debug) {
            printErrors(&result->errorContext);
        } 

        char* gramOut = concat(arguments.input_files[i], "_gram.dot");
        int err = generateDotFileFromMyTree(result->tree, gramOut, arguments.debug);

        if (err == FILE_ERROR) {
          fprintf(stderr, "Error opening file %s for writing.\n", gramOut);
        }
        free(gramOut);

        files.result[i] = result;
    }

    ClassProgram* prog = buildClassProgram(&files, arguments.debug);

    for (int i = 0; i < arguments.input_file_count; i++) {
        if (!files.result[i]->isValid) {
            printf("Parser errors of file %s:\n", files.fileName[i]);
            printErrors(&files.result[i]->errorContext);
            printf("\n");
        } 
    }

    ClassInfo *classInfo = prog->classes;
    while (classInfo != NULL) {
        FunctionInfo *func = classInfo->program->functions;
        if (classInfo->program->errors != NULL) {
          printf("Errors of %s class:\n", classInfo->name);
          ProgramErrorInfo *error = classInfo->program->errors;
          while (error != NULL) {
            printf("%s\n", error->message);
            error = error->next;
          }
        }

        if (classInfo->program->warnings != NULL) {
          printf("Warnings of %s class:\n", classInfo->name);
          ProgramWarningInfo *warning = classInfo->program->warnings;
          while (warning != NULL) {
            printf("%s\n", warning->message);
            warning = warning->next;
          }
        }
        classInfo = classInfo->next;
    }


    classInfo = prog->classes;
    while (classInfo != NULL) {
        FunctionInfo *func = classInfo->program->functions;
        const char *mainFileName = NULL;
        while (func != NULL) {
          if (strcmp(func->functionName, "main") == 0) {
            mainFileName = func->fileName;
          }
          char *suffix = concat(".", func->functionName);
          char *functionName = concat(classInfo->name, suffix);
          char *outputFilePath = getOutputFileName(func->fileName, functionName, "dot", arguments.output_dir);
          if (func->cfg != NULL)
            writeCFGToDotFile(func->cfg, outputFilePath, arguments.ot);
          func = func->next;
          free(suffix);
          free(functionName);
          free(outputFilePath);
        }
        classInfo = classInfo->next;
    }


    struct StringBuffer *buffer = stringbuffer_new_with_options(1024, true);
    uint32_t alrValue = 0;
    stringbuffer_append_string(buffer, "    [section codeM]\n\n");

    classInfo = prog->classes;
    while (classInfo != NULL) {
        FunctionInfo *func = classInfo->program->functions;
        while (func != NULL) {
          if (strcmp(func->functionName, "main") == 0) {
            char *classInfoString = concat("classInfo_", classInfo->name);
            commandLDI32(buffer, REG_AR, classInfoString);
            commandMOV(buffer, REG_THIS, REG_ALR);
            
            
            char fieldsCountBuffer[1024];
            snprintf(fieldsCountBuffer, sizeof(fieldsCountBuffer), "%ld", classInfo->fieldsCount);
            commandNEW(buffer, REG_AR, fieldsCountBuffer);
            free(classInfoString);

            char *mainMethod = concat(classInfo->name, "_main");
            commandJMP(buffer, mainMethod);
            free(mainMethod);

            break;
          }
          func = func->next;
        }
        classInfo = classInfo->next;
    }

    classInfo = prog->classes;
    while (classInfo != NULL) {
        FunctionEntry *funcE = classInfo->program->functionTable->entry;
        while (funcE != NULL) {
            funcE->locals = createHashTable(20);
            funcE->consts = createHashTable(20);
            FunctionInfo *func = classInfo->program->functions;
            while (func != NULL) {
              if (strcmp(func->functionName, funcE->functionName) == 0) {
                break;
              }
              func = func->next;
            }
            if (func->cfg != NULL) {
                BasicBlock *b = func->cfg->blocks;
                while (b != NULL) {
                    for (int i = 0; i < b->instructionCount; i++) {
                        scanOperationTreeForVars(classInfo, funcE, b->instructions[i].otRoot);
                        prepareRegsAndTemps(b->instructions[i].otRoot, arguments.debug);
                    }
                    b = b->next;
                }
    
                for (int i = 0; i < funcE->consts->size; i++) {
                    HashNode *node = funcE->consts->buckets[i];
                    while (node) {
                        ((ConstVar *)node->value)->address = ((ConstVar *)node->value)->address + alrValue;
                        alrValue = alrValue + ((ConstVar *)node->value)->size;
                        node = node->next;
                    }
                }
    
                if (funcE->argumentsCount > 0) {
                    int64_t offset = 8 + funcE->argumentsCount * 8;
                    ArgumentInfo *arg = funcE->arguments;
                    while (arg != NULL) {
                        arg->offset = offset;
                        offset = offset - 8;
                        arg = arg->next;
                    } 
                }
                
    
                if (arguments.debug) {
                printf("\nLocals for %s:\n", funcE->functionName);
                for (int i = 0; i < funcE->locals->size; i++) {
                    HashNode *node = funcE->locals->buckets[i];
                    while (node) {
                    printf("Key: %s, Name: %s, Index: %d", node->key, ((LocalVar *)node->value)->name,
                            ((LocalVar *)node->value)->index);
                    printf("\n");
                    node = node->next;
                    }
                }
    
                printf("\nConsts for %s:\n", funcE->functionName);
                for (int i = 0; i < funcE->consts->size; i++) {
                    HashNode *node = funcE->consts->buckets[i];
                    while (node) {
                    printf("Key: %s, Value: %s, Address: %d", node->key, ((ConstVar *)node->value)->name,
                            ((ConstVar *)node->value)->address);
                    printf("\n");
                    node = node->next;
                    }
                }
                if (funcE->argumentsCount > 0) {
                    printf("\nArgs for %s:\n", funcE->functionName);
                    ArgumentInfo *arg = funcE->arguments;
                    while (arg != NULL) {
                        printf("Name: %s, Offset: %ld", arg->name, arg->offset);
                        printf("\n");
                        arg = arg->next;
                    } 
                }
                }
                bool isMain = strcmp(funcE->functionName, "main") == 0;
                generateASMForFunction(classInfo, prog->classes, buffer, func, funcE, isMain, arguments.debug);
    
            }
    
            funcE = funcE->next;
        }
        classInfo = classInfo->next;
    }

    stringbuffer_append_string(buffer, "\n    [section constantsM]\n\n");
    
    classInfo = prog->classes;
    while (classInfo != NULL) {
        if (classInfo->isInterface) {
            classInfo = classInfo->next;
            continue;
        } else {
            stringbuffer_append_string(buffer, "vtable_");
            stringbuffer_append_string(buffer, classInfo->name);
            stringbuffer_append_string(buffer, ":\n");

            ClassVtableEntry *vtableEntry = classInfo->vtable->head;
            while (vtableEntry != NULL) {
                if (!vtableEntry->isBuiltin) {
                    stringbuffer_append_string(buffer, "    dq ");
                    stringbuffer_append_string(buffer, vtableEntry->className);
                    stringbuffer_append_string(buffer, "_");
                    stringbuffer_append_string(buffer, vtableEntry->functionName);
                    stringbuffer_append_string(buffer, "\n");
                }
                vtableEntry = vtableEntry->next;
            }
        }
        stringbuffer_append_string(buffer, "\n");

        if (classInfo->interfaceCount > 0) {
            for (uint32_t i = 0; i < classInfo->interfaceCount; i++) {
                stringbuffer_append_string(buffer, "itable_");
                stringbuffer_append_string(buffer, classInfo->interfaceNames[i]);
                stringbuffer_append_string(buffer, "_");
                stringbuffer_append_string(buffer, classInfo->name);
                stringbuffer_append_string(buffer, ":\n");

                ClassInfo *interfaceInfo = findClassWithName(prog->classes, classInfo->interfaceNames[i]);
                ClassVtableEntry *vtableEntry = interfaceInfo->vtable->head;
                while (vtableEntry != NULL) {
                    stringbuffer_append_string(buffer, "    dq ");
                    stringbuffer_append_string(buffer, classInfo->name);
                    stringbuffer_append_string(buffer, "_");
                    stringbuffer_append_string(buffer, vtableEntry->functionName);
                    stringbuffer_append_string(buffer, "\n");
                    vtableEntry = vtableEntry->next;
                }
                stringbuffer_append_string(buffer, "\n");
            }
            stringbuffer_append_string(buffer, "\n");
        }

        stringbuffer_append_string(buffer, "classInfo_");
        stringbuffer_append_string(buffer, classInfo->name);
        stringbuffer_append_string(buffer, ":\n");

        stringbuffer_append_string(buffer, "    .typeId: dq ");
        char output[6]; 
        sprintf(output, "0x%02lX", classInfo->typeId);
        stringbuffer_append_string(buffer, output);
        stringbuffer_append_string(buffer, "\n");

        stringbuffer_append_string(buffer, "    .superPtr: dq ");
        stringbuffer_append_string(buffer, "classInfo_");
        if (classInfo->parentName == NULL) {
            stringbuffer_append_string(buffer, "Object");
        } else {
            stringbuffer_append_string(buffer, classInfo->parentName);
        }
        stringbuffer_append_string(buffer, "\n");

        stringbuffer_append_string(buffer, "    .vtablePtr: dq ");
        stringbuffer_append_string(buffer, "vtable_");
        stringbuffer_append_string(buffer, classInfo->name);
        stringbuffer_append_string(buffer, "\n");

        stringbuffer_append_string(buffer, "    .interfaceCount:\n");
        stringbuffer_append_string(buffer, "        dq ");
        sprintf(output, "0x%02X", classInfo->interfaceCount);
        stringbuffer_append_string(buffer, output);
        stringbuffer_append_string(buffer, "\n");

        if (classInfo->interfaceCount == 0) {
            stringbuffer_append_string(buffer, "    .interfaceIds:\n");
            stringbuffer_append_string(buffer, "        dq 0x0\n");
            stringbuffer_append_string(buffer, "    .interfaceImpl:\n");
            stringbuffer_append_string(buffer, "        dq 0x0\n");
        } else {
            stringbuffer_append_string(buffer, "    .interfaceIds:\n");
            for (uint32_t i = 0; i < classInfo->interfaceCount; i++) {
                stringbuffer_append_string(buffer, "        dq ");
                ClassInfo *interfaceInfo = findClassWithName(prog->classes, classInfo->interfaceNames[i]);
                sprintf(output, "0x%02lX\n", interfaceInfo->typeId);
                stringbuffer_append_string(buffer, output);
            }
            stringbuffer_append_string(buffer, "    .interfaceImpl:\n");
            for (uint32_t i = 0; i < classInfo->interfaceCount; i++) {
                stringbuffer_append_string(buffer, "        dq ");
                stringbuffer_append_string(buffer, "itable_");
                stringbuffer_append_string(buffer, classInfo->interfaceNames[i]);
                stringbuffer_append_string(buffer, "_");
                stringbuffer_append_string(buffer, classInfo->name);
                stringbuffer_append_string(buffer, "\n");
            }
        }

        stringbuffer_append_string(buffer, "\n");

        classInfo = classInfo->next;
    }

    classInfo = prog->classes;
    while (classInfo != NULL) {
        FunctionEntry *funcE = classInfo->program->functionTable->entry;

        while (funcE != NULL) {
            for (int i = 0; i < funcE->consts->size; i++) {
                HashNode *node = funcE->consts->buckets[i];
                while (node) {
                    stringbuffer_append_string(buffer, "\n");
                    ConstVar *var = ((ConstVar *)node->value);
                    if (strcmp(var->typeName, "string") == 0) {
                        stringbuffer_append_string(buffer, node->key);
                        stringbuffer_append_string(buffer, ":\n");
                        for (size_t i = 1; i < strlen(var->name) - 1; i++) {
                            stringbuffer_append_string(buffer, "  dq ");
                            unsigned char value = (unsigned char)var->name[i];
                            char output[6]; 
                            sprintf(output, "0x%02X", value);
                            stringbuffer_append_string(buffer, output);
                            stringbuffer_append_string(buffer, "\n");
                        }
                        stringbuffer_append_string(buffer, "  dq 0x00");
                    } else {
                        stringbuffer_append_string(buffer, node->key);
                        stringbuffer_append_string(buffer, ":\n");
                        stringbuffer_append_string(buffer, "  dq ");
                        stringbuffer_append_string(buffer, ((ConstVar *)node->value)->name);
                        stringbuffer_append_string(buffer, "\n");
                    }

                    node = node->next;
                }
            }
            funcE = funcE->next;
        }
        classInfo = classInfo->next;
    }

    char *out = stringbuffer_to_string(buffer);
    stringbuffer_release(buffer);

    FILE *asmFile = fopen(arguments.asm_dir, "wa");
    fprintf(asmFile, "%s", out);
    fclose(asmFile);
    free(out);

    classInfo = prog->classes;
    while (classInfo != NULL) {
        FunctionInfo *func = classInfo->program->functions;
        const char *mainFileName = NULL;
        while (func != NULL) {
          if (strcmp(func->functionName, "main") == 0) {
            mainFileName = func->fileName;
          }
          char *suffix = concat(".", func->functionName);
          char *functionName = concat(classInfo->name, suffix);
          char *outputFilePath = getOutputFileName(func->fileName, functionName, "dot", arguments.output_dir);
          if (func->cfg != NULL)
            writeCFGToDotFile(func->cfg, outputFilePath, arguments.ot);
          func = func->next;
          free(suffix);
          free(functionName);
          free(outputFilePath);
        }
        classInfo = classInfo->next;
    }

    classInfo = prog->classes;
    while (classInfo != NULL) {
        freeFunctionTable(classInfo->program->functionTable, freeLocalVarAsVoid, freeConstVarAsVoid);
        classInfo = classInfo->next;
    }
    
    freeClassProgram(prog);

    for (uint32_t i = 0; i < files.filesCount; i++) {
        destroyMyLangResult(files.result[i]);
        free(files.result[i]);
    }
    free(arguments.input_files);
    free(files.result);

    // char *out = stringbuffer_to_string(buffer);
    // if (arguments.debug)
    //     printf("%s\n\n", out);
    // stringbuffer_release(buffer);

    // FILE *asmFile = fopen(arguments.asm_dir, "wa");
    // fprintf(asmFile, "%s", out);
    // fclose(asmFile);
    // free(out);

    // freeFunctionTable(prog->functionTable, freeLocalVarAsVoid, freeConstVarAsVoid);

    // FunctionInfo *func = prog->functions;
    // const char *mainFileName = NULL;
    // while (func != NULL) {
    //   if (strcmp(func->functionName, "main") == 0) {
    //     mainFileName = func->fileName;
    //   }
    //   char *outputFilePath = getOutputFileName(func->fileName, func->functionName, "dot", arguments.output_dir);
    //   if (func->cfg != NULL)
    //     writeCFGToDotFile(func->cfg, outputFilePath, arguments.ot);
    //   func = func->next;
    //   free(outputFilePath);
    // }

    // if (mainFileName == NULL) {
    //     fprintf(stderr, "Error: main function is not defined\n");
    // }

    // if (prog->errors == NULL && (mainFileName != NULL || arguments.output_dir != NULL)) {
    //     CallGraph *graph = (CallGraph *)malloc(sizeof(CallGraph));
    //     graph->functions = NULL;

    //     traverseProgramAndBuildCallGraph(prog, graph, false);
    //     char* dir;
    //     char* path;
    //     if (arguments.output_dir != NULL) {
    //         dir = arguments.output_dir;
    //         path = concat(dir, "/cg.dot");
    //         writeCallGraphToDot(graph, path);
    //         free(path);
    //     } else if (mainFileName != NULL) {
    //         dir = getDirectory(mainFileName);
    //         path = concat(dir, "/cg.dot");
    //         writeCallGraphToDot(graph, path);
    //         free(path);
    //         free(dir);
    //     } else {
    //         fprintf(stderr, "Error: can't save CG to dot file because main function and output directory are not defined\n");
    //     }

    //     freeCallGraph(graph);
    // }

    // freeProgram(prog);

    // for (uint32_t i = 0; i < files.filesCount; i++) {
    //     destroyMyLangResult(files.result[i]);
    //     free(files.result[i]);
    // }
    // free(arguments.input_files);
    // free(files.result);
    return 0;
}
