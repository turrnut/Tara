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
 * lexer.h
 *
 */

#ifndef lexer_header
#define lexer_header

#include "../ir/ir.h"
#include "../error/error.h"

typedef enum {
    ADD_TOKEN,
    AND_TOKEN, 
    ASSIGN_TOKEN,
    CLASS_TOKEN,
    COLON_TOKEN,
    COMMA_TOKEN,
    DIV_TOKEN,
    DOT_TOKEN,
    ELIF_TOKEN,
    ELSE_TOKEN,
    EOF_TOKEN,
    EQUAL_TOKEN,
    ERROR_TOKEN,
    FALSE_TOKEN,
    FOR_TOKEN,
    FUNCTION_TOKEN,
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL_TO_TOKEN,
    ID_TOKEN,
    IF_TOKEN,
    IGNORE_TOKEN,
    LCURBRACES_TOKEN,
    LESS_THAN_TOKEN,
    LESS_THAN_OR_EQUAL_TO_TOKEN,
    LINE_TOKEN,
    LPAREN_TOKEN,
    MUL_TOKEN,
    NUMBER_TOKEN,
    NOT_TOKEN,
    NOT_EQUAL_TOKEN,
    NULL_TOKEN,
    OR_TOKEN,
    RCURBRACES_TOKEN,
    RETURN_TOKEN,
    RPAREN_TOKEN,
    SCOLON_TOKEN,
    SUB_TOKEN,
    SUPER_TOKEN,
    THIS_TOKEN,
    TRACE_TOKEN,
    TRUE_TOKEN,
    VARIABLE_TOKEN,
    WHILE_TOKEN
} TokenTypes;

typedef struct {
    TokenTypes type;
    const char* first;
    int len;
    Position pos;
} Token;

typedef struct {
    const char* first;
    const char* current;
    Position pos;
} Lexer;

Token get_token();
Token new_error_token(Error err);
void new_lexer(const char* src);
Token new_token(TokenTypes ty);
TokenTypes id_type();
char next_char();
bool is(char ch);
bool inNumber(char ch);
void filter();
char peekNext();
char peekCurrent();

#endif
