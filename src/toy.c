#include "include/base.h"
#include "code/ir.h"
#include "code/runtime.h"
#include "debugging/debugging.h"
int main(int argc, char const *argv[]) {  
    startRuntime();

    IR ir;
    initIR(&ir);

    Position mypos;
    mypos.row = 123;
    mypos.col = 123;
    Position mypos2;
    mypos2.row = 66;
    mypos2.col = 178;

    defineConstant(&ir, 1.2, mypos);
    defineConstant(&ir, 3.4, mypos2);

    writeIR(&ir, INS_ADD, mypos);

    defineConstant(&ir, 5.6, mypos2);
    writeIR(&ir, INS_DIV,mypos);

    writeIR(&ir, INS_NEGATE, mypos2);
    writeIR(&ir, INS_RETURN, mypos2);

    showIR(&ir, "testing IR");
    run(&ir);
    endRuntime();
    freeIR(&ir);
    return 0;
}
