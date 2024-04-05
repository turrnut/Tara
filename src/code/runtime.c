#include <stdio.h>

#include "../include/base.h"
#include "../debugging/debugging.h"
#include "runtime.h"

#define operation(oper) \
    do { \
        double right = stackPop();\
        double left = stackPop();\
        stackPush(left oper right);\
    } while(false)

Runtime runtime;

void reStack() {
    runtime.stackTop = runtime.stack;
}

void startRuntime() {
    reStack();
}

void stackPush(DataValue val) {
    *runtime.stackTop = val;
    runtime.stackTop++;
}
DataValue stackPop(){
    runtime.stackTop--;
    return *runtime.stackTop;
}

void endRuntime() {

}

Result run(IR* ir) {
    runtime.ir = ir;
    runtime.pc = runtime.ir->code;
    while(1) {
        #ifndef READY
            #ifdef RUNTIME_DEBUGGING
                printf("");
                for (DataValue* thing = runtime.stack; thing < runtime.stackTop; thing++) {
                    printf("{ ");
                    printStuff(*thing);
                    printf(" }");
                }
                printf("\n");
                showInstruction(runtime.ir, (int)(runtime.pc - runtime.ir->code));
            #endif
        #endif
        uint8_t ins = *runtime.pc++;
        switch (ins) {
            case INS_RETURN: {
                printStuff(stackPop());
                printf("\n");
                return SUCCESS;
            }
            case INS_DEFCONST: {
                DataValue value = runtime.ir->list.data[*runtime.pc++];
                stackPush(value);
                break;
            }
            case INS_ADD: operation(+); break;
            case INS_SUB: operation(-); break;
            case INS_MUL: operation(*); break;
            case INS_DIV: operation(/); break;
            case INS_NEGATE:
                stackPush(-stackPop());
                break;
        }
    }
    #undef operation
}

