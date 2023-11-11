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

    int val = addDataValue(&ir, 12);
    int val2 = addDataValue(&ir, 123);
    int val3 = addDataValue(&ir, 122);
    int val4 = addDataValue(&ir, 12.22);
    writeIR(&ir, INS_DEFCONST, mypos);
    writeIR(&ir, val, mypos);
    writeIR(&ir, INS_DEFCONST, mypos);
    writeIR(&ir, val2, mypos);
    writeIR(&ir, INS_DEFCONST, mypos);
    writeIR(&ir, val3, mypos);
    writeIR(&ir, INS_DEFCONST, mypos);
    writeIR(&ir, val4, mypos);
    
    writeIR(&ir, INS_RETURN, mypos2);

    showIR(&ir, "testing IR");
    freeIR(&ir);
    return 0;
}
