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
 * toy.c
 * This is the entry point of the program, which contains the
 * main function.
 *
 */

#include "base/base.h"
#include "ir/ir.h"
#include "test/test.h"
#include "compiler/compiler.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[])
{

    init();
    IR ir;
    initIR(&ir);

    int constant = addData(&ir, 1.2);
    Position e = {0, 0};
    Position f = {0, 1};
    createIR(&ir, INS_DATA, e);
    createIR(&ir, constant, f);
    constant = addData(&ir, 3.4);
    createIR(&ir,INS_DATA,e);
    createIR(&ir,constant,e);
    createIR(&ir,INS_ADD,e);

    constant = addData(&ir, 5.6);
    createIR(&ir,INS_DATA,e);
    createIR(&ir,constant,e);
    createIR(&ir,INS_DIV,e);

    createIR(&ir, INS_NEGATIVE, f);
    createIR(&ir, INS_RETURN, e);


    showIR(&ir, "testing");
    compile(&ir);

    end();
    releaseIR(&ir);
    return 0;
}
