#include <stdio.h>
#include "include/base.h"
#include "code/ir.h"
#include "debugging/debugging.h"
int main(int argc, char const *argv[]) {    
    IR ir;
    initIR(&ir);

    Position mypos;
    mypos.row = 123;
    mypos.col = 123;
    Position mypos2;
    mypos2.row = 66;
    mypos2.col = 178;

    defineConstant(&ir, 123, mypos);
    writeIR(&ir, INS_RETURN, mypos2);

    showIR(&ir, "testing IR");
    freeIR(&ir);
    return 0;
}
