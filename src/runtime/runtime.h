/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 *
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE for more details about
 * how you can use it, you have freedom to distribute and
 * use this code in your project. However, you will have to
 * state changes you made and include the orginal author of
 * this code.
 *
 * compiler.h
 *
 */
#ifndef compiler_header
#define compiler_header

#include "../ir/ir.h"
#include "../error/error.h"
#include "../include/constants.h"
#include "../types/types.h"

typedef struct
{
    IR *ir;
    uint8_t *bp; // byte pointer
    Data *stack;
    Data *stacktop;
    int vol; // stack size
    const char* filename;
    Object* heap;
    Map pool;
    Map global_map;
} RuntimeEnvironment;

typedef enum
{
    EXECUTE_SUCCESS,
    COMPILE_ERROR,
    RUNTIME_ERROR
} Result;

extern RuntimeEnvironment runtime;

void start_runtime_environment(IR* ir, const char* filename);
void end_runtime_environment();
void new_runtime(IR *ir, const char* fname);
void freeStack();
void freeHeap();
void freeMaps();
void releaseObject(Object* o);
void update_stacktop();
void stack_push(Data data);
int stack_is_empty();
int stack_alloc(int vol);
Data stack_pop();
uint8_t step();
Data readData();
Text* readText();
Result reportRuntimeError(const char *err);
Data see(int i);
Result Compile(const char* filename, const char* src, IR* ir);
Result Execute(const char* filename, IR* ir);
void concat_text();

#endif
