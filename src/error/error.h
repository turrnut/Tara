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
    EXPECT_LINE,
    EXPECT_EXPRESSION,
    EXPECT_CHAR_RPAREN,
    VALUE_TOO_LARGE,
    EXPECT_ID_FOR_VAR,

    EXPR_MUST_BE_NUMBER,
    ILLEGAL_OPERANDS,
    ZERO_DIVISION,
    UNDEFINED_ERROR
} Error;

/**
 * Note: argument is type Error
*/
char* get_error_text(Error err,...);
char* get_error_text_with_one_arg(Error err, char* arg);
#endif