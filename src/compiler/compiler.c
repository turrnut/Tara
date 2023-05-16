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
 * compiler.c
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "../base/base.h"
#include "../test/test.h"
#include "../data/data.h"
#include "../memory/memory.h"
#include "compiler.h"

#define binary_operation(op) \
    do { \
      double second = stack_pop(); \
      double first = stack_pop(); \
      stack_push(first op second); \
    } while (false)

Compiler compiler;

void init() {}
void end() {}

int trace()
{
    printf("        ");
    for (Data *i = compiler.stack; i < compiler.stacktop; i++)
    {
        printf("[ ");
        printData(*i);
        printf("]");
    }
    return showIns(compiler.ir, (int)(compiler.bp - compiler.ir->code));
}

void stack_push(Data data)
{
    *compiler.stacktop = data;
    compiler.stacktop++;
}
int stack_is_empty()
{
    if ((sizeof(compiler.stack) / sizeof(*compiler.stack)) == 0)
        return 1;
    return 0;
}
Data stack_pop()
{
    compiler.stacktop--;
    return *compiler.stacktop;
}

Data readData()
{
    return compiler.ir->coll.elements[step()];
}

uint8_t step()
{
    if (*compiler.bp < STACK_SIZE)
        return *compiler.bp++;
    printf("\n\aERROR: Stack Overflow\n");
    exit(1);
}

int stack_alloc(int vol) {
    return ((vol) < (STACK_SIZE * 2) ? (STACK_SIZE * 2) : (vol)*1.5);
}

void update_stacktop()
{
    compiler.stacktop = compiler.stack;
}

void new_compiler(IR *ir)
{
    compiler.ir = ir;
    compiler.bp = compiler.ir->code;

    compiler.stacktop = compiler.stack;
}

Result compile(IR *ir)
{
    new_compiler(ir);

    while (1)
    {
        uint8_t instruction;
        instruction = step();
        switch (instruction)
        {
        case INS_RETURN:
        {
            printData(stack_pop());
            printf("\n");
            return EXECUTE_SUCCESS;
            break;
        }
        case INS_DATA:
        {
            stack_push(readData());
            break;
        }

        case INS_NEGATIVE:{
            Data st = *compiler.stacktop;
            stack_push(-st);
            break;
        }
        case INS_ADD:{binary_operation(+); break;}
        case INS_SUB:{binary_operation(-); break;}
        case INS_MUL:{binary_operation(*); break;}
        case INS_DIV:{binary_operation(/); break;}
        }
    }
}
