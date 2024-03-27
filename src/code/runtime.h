#ifndef runtime_header
#define runtime_header

#define MAXSTACK 256

#include "../code/ir.h"
#include "../types/types.h"

typedef struct {
    IR* ir;
    uint8_t* pc;
    DataValue stack[MAXSTACK];
    DataValue* stackTop;
} Runtime;

typedef enum {
    SUCCESS,
    COMPILE_ERROR,
    RUNTIME_ERROR
} Result;

void startRuntime();
void endRuntime();
Result run(IR* ir);
void reStack();
void stackPush();
DataValue stackPop();

#endif
