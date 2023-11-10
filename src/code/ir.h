#ifndef ir_header
#define ir_header

#include "../include/base.h"
#include "../types/types.h"

typedef enum {
    INS_RET, // return
    INS_DEC, // define constant
} InsCode;

typedef struct {
    int row;
    int col;
} Position;

typedef struct {
    uint8_t* code;
    int counter;
    int volume;
    DataValuesList list;
    Position pos;
} IR;

void emptyIR(IR* ir);
void initIR(IR* ir);
void freeIR(IR* ir);
int addDataValue(IR* ir, DataValue val);
void writeIR(IR* ir, uint8_t stuff);

#endif
