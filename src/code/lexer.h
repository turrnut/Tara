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

/**
 * Enumeration for every token
*/
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
    GREATER_THAN_TOKEN,
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
    STRING_TOKEN,
    SUB_TOKEN,
    SUPER_TOKEN,
    THIS_TOKEN,
    TRACE_TOKEN,
    TRUE_TOKEN,
    VARIABLE_TOKEN,
    WHILE_TOKEN
} TokenTypes;

/**
 * Represents a token.
 * Properties:
 *  TokenTypes type:
 *    the token's type
 *  const char* first:
 *    what is the token's first character
 *  int len:
 *    length of token
 *  Position pos:
 *    position of the token located
*/
typedef struct {
    TokenTypes type;
    const char* first;
    int len;
    Position pos;
} Token;

/**
 * Represents a lexer.
 * Properties:
 *  const char* first:
 *    first character in the current expression
 *  const char* current:
 *    current text being handled
 *  Position pos:
 *    location of the current token is located
*/
typedef struct {
    const char* first;
    const char* current;
    Position pos;
} Lexer;

Token get_token();
Token new_error_token(int err/* enum member of Error */);
void new_lexer(const char* src);
Token new_token(TokenTypes ty);
TokenTypes id_type();
char lexer_next_char();
bool is(char ch);
bool inNumber(char ch);
void filter();
char peekNext();
char peekCurrent();

#endif
