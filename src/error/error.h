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
 * error.h
 * 
 */

#ifndef error_header
#define error_header
#include "../code/lexer.h"
typedef enum {
    UNKNOWN_ERROR,
    ILLEGAL_CHARACTER,
    UNTERMINATED_STRING,
    EXPECT_END,
    EXPECT_CHAR_RPAREN,
    EXPECT_EXPRESSION,
    VALUE_TOO_LARGE,

    EXPR_MUST_BE_NUMBER,
    ILLEGAL_OPERANDS,
    ZERO_DIVISION
} Error;

/**
 * Note: argument is type Error
*/
char* get_error_text(Error err);
#endif