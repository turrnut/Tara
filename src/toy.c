#include "include/base.h"
#include "code/ir.h"
#include "debugging/debugging.h"
int main(int argc, char const *argv[]) {    
    IR ir;
    initIR(&ir);

    int val = addDataValue(&ir, 12);
    writeIR(&ir, INS_DEC);
    writeIR(&ir, val);
    
    writeIR(&ir, INS_RET);

    showIR(&ir, "testing IR");
    freeIR(&ir);
    return 0;
}
