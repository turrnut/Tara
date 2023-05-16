/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 *
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE for details for
 * more details about how you can use it, you have freedom
 * to distribute and use this file in your project. However,
 * you will have to state changes you made and include the
 * orginal author of this file.
 *
 * compiler.h
 *
 */
#ifndef compiler_header
#define compiler_header

#include "../ir/ir.h"

#define STACK_SIZE 1024

typedef struct
{
    IR *ir;
    uint8_t *bp; // byte pointer
    Data stack[STACK_SIZE];
    Data *stacktop;
} Compiler;

typedef enum
{
    EXECUTE_SUCCESS,
    COMPILE_ERROR,
    RUNTIME_ERROR
} Result;

void init();
void end();
void update_stacktop();
void stack_push(Data data);
int stack_is_empty();
int stack_alloc(int vol);
Data stack_pop();
uint8_t step();
Data readData();

Result compile(IR *ir);

#endif
