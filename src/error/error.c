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
        case ILLEGAL_CHARACTER:
            return "IllegalCharacterError: The character provided cannot be recognized.";
        case UNTERMINATED_STRING:
            return "UnterminatedStringError: The string provided was never ended.";
        case EXPECT_END:
            return "ExpectEndingError: Expect the end of file.";
        case VALUE_TOO_LARGE:
            return "ValueTooLargeError: The value is too large to store in 1 bytecode.";
        case EXPECT_CHAR_RPAREN:
            return "ExpectCharacterError: Expect ')'.";
        case EXPECT_EXPRESSION:
            return "ExpectExpressionEror: Expect expression.";
        ////////////////////////////
        case EXPR_MUST_BE_NUMBER:
            return "TypeError: Expression must be of type 'number'.";
        case ZERO_DIVISION:
            return "ZeroDivisionError: Can't divide a number by zero.";

        case UNKNOWN_ERROR:
        default:
            return "Error";
            break;
    }
    
}