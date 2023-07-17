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
 * error.c
 */

#include <stdarg.h>
#include "error.h"
char* get_error_text(Error err){

    switch (err)
    {
        case UNTERMINATED_STRING:
            return "StringError: The string provided was never ended.";
        case VALUE_TOO_LARGE:
            return "ValueError: The value is too large to store in 1 byte.";
        case EXPECT_END:
            return "SyntaxError: Expect the end of file.";
        case ILLEGAL_CHARACTER:
            return "SyntaxError: The character provided cannot be recognized.";
        case EXPECT_CHAR_RPAREN:
            return "SyntaxError: Expect ')'.";
        case EXPECT_LINE:
            return "SyntaxError: Expect ';' or new line.";
        case EXPECT_EXPRESSION:
            return "SyntaxError: Expect expression.";
        case EXPECT_ID_FOR_VAR:
            return "SyntaxError: Expect an identifier for variable.";
        ////////////////////////////
        case EXPR_MUST_BE_NUMBER:
            return "TypeError: Expression must be of type 'number'.";
        case ZERO_DIVISION:
            return "ZeroDivisionError: Can't divide a number by zero.";
        case ILLEGAL_OPERANDS:
            return "IllegalOperandsError: Invalid operand types.";

        case UNKNOWN_ERROR:
        default:
            return "Error";
            break;
    }
    
}