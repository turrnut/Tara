/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 *
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE for more details about
 * how you can use it, you have freedom to distribute and
 * use this code in your project. However, you will have to
 * state changes you made and include the orginal author of
 * this code.
 *
 * test.h
 *
 */

#ifndef test_header
#define test_header
#include <time.h>
#include "../ir/ir.h"

void printName(const char* name);
void showIR(IR *ir, const char *name);
int showIns(IR *ir, int i);
void ins(const char *name, int offset);
void insD(const char *name, IR *ir,
          int offset);

#endif