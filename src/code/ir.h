#ifndef ir_header
#define ir_header

#include "../include/base.h"
#include "../types/types.h"

typedef enum {
    INS_RETURN, // return
    INS_DEFCONST, // define constant
    INS_DEFCONST_LARGE,
    INS_ADD,
    INS_SUB,
    INS_MUL,
    INS_DIV,
    INS_NEGATE
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
int addDataValueToList(IR* ir, DataValue val);
void writeIR(IR* ir, uint8_t stuff, Position pos);
void defineConstant(IR* ir, DataValue val, Position pos);

#endif
