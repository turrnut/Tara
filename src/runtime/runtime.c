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
 * runtime.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../base/base.h"
#include "../test/test.h"
#include "../data/data.h"
#include "../error/error.h"
#include "../code/codegen.h"
#include "../memory/memory.h"
#include "runtime.h"

#define binary_operation(convert, op, div) \
    do { \
        if (!IS_NUMBER(see(1)) || !IS_NUMBER(see(0))) \
            return reportRuntimeError(strcat(strcat(strcat(get_error_text(EXPR_MUST_BE_NUMBER), ", found type '"), get_str_from_type_name(see(0).type)), "'")); \
        double right = UNPACK_NUMBER(stack_pop()); \
        double left = UNPACK_NUMBER(stack_pop()); \
        if (right == 0 && div) { \
            return reportRuntimeError(get_error_text(ZERO_DIVISION));\
        } \
        stack_push(convert(left op right)); \
    } while (false)

RuntimeEnvironment runtime;

void start_runtime_environment() {}
void end_runtime_environment() {
    free(runtime.stack);
    runtime.stack = NULL;
}

int trace() {
    printf("        ");
    for (Data *i = runtime.stack; i < runtime.stacktop; i++)
    {
        printf("[ ");
        printData(*i);
        printf("]");
    }
    return showIns(runtime.ir, (int)(runtime.bp - runtime.ir->code));
}

void stack_push(Data data)
{
    *runtime.stacktop = data;
    runtime.stacktop++;
}
int stack_is_empty()
{
    if ((sizeof(runtime.stack) / sizeof(*runtime.stack)) == 0)
        return 1;
    return 0;
}
Data stack_pop()
{
    runtime.stacktop--;
    return *runtime.stacktop;
}

Data readData()
{
    return runtime.ir->coll.elements[step()];
}

uint8_t step()
{
    if (*runtime.bp < STACK_SIZE)
        goto ret;
        
    int targetSize = stack_alloc(*runtime.bp);
    runtime.stack = realloc(runtime.stack, *runtime.bp * sizeof(*runtime.stack));
    ret:
    return *runtime.bp++;
}

int stack_alloc(int vol) {
    return ((vol) < (STACK_SIZE * 2) ? (STACK_SIZE * 2) : (vol)*1.5);
}

void update_stacktop()
{
    runtime.stacktop = runtime.stack;
}

void new_runtime(IR *ir, const char* fname)
{
    runtime.ir = ir;
    runtime.bp = runtime.ir->code;
    runtime.stack = malloc(STACK_SIZE * sizeof(*runtime.stack));
    runtime.stacktop = runtime.stack;
    runtime.filename = fname;
}

Result reportRuntimeError(const char *err) {
    printf("\a\nError generated during runtime.\n\t%s\nAt file %s:%i:%i\n", err, runtime.filename, runtime.ir->pos.row, runtime.ir->pos.col);
    runtime.stacktop = runtime.stack;
    return RUNTIME_ERROR;
}

Data see (int i) { return runtime.stacktop[-1-i]; }

Result do_run() {
    while (1) {
        #ifdef RUNTIME_DEBUG_MODE
            showIns(runtime.ir,(int)(runtime.bp - runtime.ir->code));
        #endif
        uint8_t instruction;
        instruction = step();
        switch (instruction)
        {
            case INS_RETURN: {
                printData(stack_pop());
                printf("\n");
                return EXECUTE_SUCCESS;
                break;
            }
            case INS_DATA:{
                stack_push(readData());
                break;
            }
            case INS_NEGATIVE:{
                int zero = 0;
                if(!IS_NUMBER(see(zero))) return reportRuntimeError(strcat(strcat(strcat(get_error_text(EXPR_MUST_BE_NUMBER), ", found type '"), get_str_from_type_name(see(zero).type)), "'"));
                stack_push(PACK_NUMBER(-UNPACK_NUMBER(stack_pop())));
                break;
            }
            case INS_EQUAL: {
                Data right = stack_pop();
                Data left = stack_pop();
                stack_push(PACK_BOOLEAN(isEqual(left,right)));
                break;
            }
            case INS_GREATER_THAN:
                binary_operation(PACK_BOOLEAN, >, false);
                break;
            case INS_GREATER_THAN_OR_EQUAL_TO:
                binary_operation(PACK_BOOLEAN, >=, false);
                break;
            case INS_LESS_THAN:
                binary_operation(PACK_BOOLEAN, <, false);
                break;
            case INS_LESS_THAN_OR_EQUAL_TO:
                binary_operation(PACK_BOOLEAN, <=, false);
                break;
            case INS_ADD:{ binary_operation(PACK_NUMBER, +, false); break; }
            case INS_SUB:{ binary_operation(PACK_NUMBER, -, false); break; }
            case INS_MUL:{ binary_operation(PACK_NUMBER, *, false); break; }
            case INS_DIV:{ binary_operation(PACK_NUMBER, /, true); break; }
            case INS_NOT:{
                stack_push(PACK_BOOLEAN(isFalse(stack_pop())));
                break;
            }
            case INS_DATA_NULL: {
                stack_push(PACK_NULL);
                break;
            }
            case INS_DATA_FALSE: {
                stack_push(PACK_BOOLEAN(false));
                break;
            }
            case INS_DATA_TRUE: {
                stack_push(PACK_BOOLEAN(true));
                break;
            }
        }
    }
}

Result execute(const char* filename, const char* src) {
    start_runtime_environment();
    IR ir;
    initIR(&ir);
    Result res;

    if(codegen(filename,src, &ir) == CODEGEN_ERROR) {
        res = COMPILE_ERROR;
        goto bye;
    }
    
    new_runtime(&ir, filename);
    runtime.ir = &ir;
    runtime.bp = runtime.ir->code;

    res = do_run();
    
    bye:
    releaseIR(&ir);
    end_runtime_environment();
    return res;
}
