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
 * codegen.h
 * Declares the functionality needed to generate IR. Specific
 * implementation can be found in codegen.cs
 */

#ifndef codegen_header
#define codegen_header
#include "../runtime/runtime.h"
#include "../ir/ir.h"

/**
 * Represents whether the execution is successful or not.
*/
typedef enum {
    CODEGEN_OK,
    CODEGEN_ERROR
} CodeGenerationResult;

/**
 * Generates the IR, taking the source code text and IR
 * pointer as an input.
*/
CodeGenerationResult codegen(const char* src);

#endif
