#ifndef debugging_header
#define debugging_header

#include "../code/ir.h"

void showIR(IR* ir, const char* testname);
int showInstruction(IR* ir, int idx);
void printStuff(DataValue val);

#endif
