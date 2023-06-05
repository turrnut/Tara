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
 * lexer.c
 * The lexer takes in raw source code text and convert it
 * into a list of tokens.
 *
 */

#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "../ir/ir.h"
#include "../base/base.h"
#include "../error/error.h"

Lexer lexer;
bool isPrevLine = false;

void new_lexer(const char* src){
    lexer.first, lexer.current = src;
    Position startingPosition = {
        1,0 // row, col
    };
    lexer.pos = startingPosition;
}
Token new_error_token(int err) {
    char* m = get_error_text(err);

    Token token;
    token.type = ERROR_TOKEN;
    const char* message = (const char *)m;
    token.first = message;
    token.len = (int)strlen(message);
    token.pos = lexer.pos;
    return token;
}
Token new_token(TokenTypes ty){
    Token token;
    token.type = ty;
    token.first = lexer.first;
    token.pos = lexer.pos;
    token.len = (int)(lexer.current - lexer.first); 
    if (isPrevLine && ty == LINE_TOKEN){
        token.type = IGNORE_TOKEN; //////////////////////////////////////////////////////////////////////////////////
    }
    if (ty == LINE_TOKEN) isPrevLine = true; else isPrevLine = false;
    return token;
}

bool is(char c) {
    if (*lexer.current == '\0')
        goto f;
    
    if (*lexer.current == c) {
        lexer.current ++;
        return true;
    }

    f:
    return false;
}
char lexer_next_char() {
    lexer.current ++;
    if (peekCurrent() == '\n'){
        lexer.pos.row ++;
        lexer.pos.col = 0;
    } else
        lexer.pos.col ++;
    return lexer.current[-1];
}

void filter(){
    while(1) {
        char p = peekCurrent();
        if (p == '#') 
            while(peekNext() != '\n' && *lexer.current != '\0') lexer_next_char();
        
        if (p == ' ' || p == '\r' || p == '\t') lexer_next_char(); else return;
    }
}

char peekCurrent(){
    return *lexer.current;
}

char peekNext() {
  if (*lexer.current == '\0') return '\0';
  return lexer.current[1];
}


bool inNumber(char ch){ return ch <= 57 && ch >= 48; }
bool inAlphabet(char ch) { return (ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90) || (ch == 95); }
Token new_text(){
    while (peekCurrent() != '\'' && *lexer.current != '\0') {
        lexer_next_char();
    }
    if (*lexer.current == '\0') return new_error_token(UNTERMINATED_STRING);
    lexer_next_char(); // skip the ending quote
    return new_token(TEXT_TOKEN);
}

Token new_number() {
    while(inNumber(peekCurrent()))
        lexer_next_char();
    if(peekCurrent() == '.' && inNumber(peekNext())){
        lexer_next_char();
        while (inNumber(peekCurrent()))
            lexer_next_char();
        
    }
    return new_token(NUMBER_TOKEN);
}

bool inKey(int strt, int len, const char* pattern) {
    if(lexer.current - lexer.first == strt + len && memcmp(lexer.first + strt, pattern, len) == 0)
        return true;
    return false;
}

TokenTypes id_type() {
    int strt = 1;
    TokenTypes def = ID_TOKEN; // default
    switch (lexer.first[0])
    {
        case 'a': return inKey(strt, 2, "nd") ? AND_TOKEN : def;
        case 'c': return inKey(strt, 4, "lass") ? CLASS_TOKEN : def;
        case 'e': 
            if (lexer.current - lexer.first > 1) {
                switch (lexer.first[1])
                {
                    case 'l':
                        if (lexer.current - lexer.first > 2) {
                            switch (lexer.first[2]) {
                                case 'i':
                                    return inKey(strt + 2, 1, "f") ? ELIF_TOKEN : def;
                                case 's':
                                    return inKey(strt + 2, 1, "e") ? ELSE_TOKEN : def;

                            }
                        }
                }
            }
        case 'f':
            if (lexer.current - lexer.first > 1) {
                switch (lexer.first[1])
                {
                    case 'a': return inKey(strt + 1, 3, "lse") ? FALSE_TOKEN : def;
                    case 'o': return inKey(strt + 1, 1, "r") ? FOR_TOKEN : def;
                    case 'u': return inKey(strt + 1, 1, "n") ? FUNCTION_TOKEN : def;
                }
            }
            break;
        case 't':
            if (lexer.current - lexer.first > 1) {
                switch (lexer.first[1])
                {
                    case 'r': 
                        if (lexer.current - lexer.first > 2) {
                            switch (lexer.first[2]) {
                                case 'a': return inKey(strt + 2, 2, "ce") ? TRACE_TOKEN : def;
                                case 'u': return inKey(strt + 2, 1, "e") ? TRUE_TOKEN : def;
                            }
                        }
                        
                    case 'h': return inKey(strt + 1, 2, "is") ? THIS_TOKEN : def;
                }
            }
            break;
        case 'i': return inKey(strt, 1, "f") ? IF_TOKEN : def;
        case 'n': return inKey(strt, 3, "ull") ? NULL_TOKEN : def;
        case 'o': return inKey(strt, 1, "r") ? OR_TOKEN : def;
        case 'r': return inKey(strt, 5, "eturn") ? RETURN_TOKEN : def;
        case 's': return inKey(strt, 4, "uper") ? SUPER_TOKEN : def;
        case 'v': return inKey(strt, 2, "al") ? VARIABLE_TOKEN : def;
        case 'w': return inKey(strt, 4, "hile") ? WHILE_TOKEN : def;
        case 'p': return inKey(strt, 5, "lease") ? IGNORE_TOKEN : def;
    }
    return def;
}

Token new_id() {
    while(inAlphabet(peekCurrent()) || inNumber(peekCurrent()))
        lexer_next_char();
    return new_token(id_type());
}

Token get_token() {
    lexer.first = lexer.current;
    if(*lexer.current == '\0') {
        return new_token(EOF_TOKEN);
    }
    filter();

    char ch = lexer_next_char();
    if (inNumber(ch))
        return new_number();
    if (inAlphabet(ch))
        return new_id();
    switch(ch){
        case '+': {filter(); return new_token(ADD_TOKEN);}
        case '-': return new_token(SUB_TOKEN);
        case '*': return new_token(MUL_TOKEN);
        case '/': return new_token(DIV_TOKEN);
        case ',': return new_token(COMMA_TOKEN);
        case '.': return new_token(DOT_TOKEN);
        case '(': return new_token(LPAREN_TOKEN);
        case ')': return new_token(RPAREN_TOKEN);
        case ';': return new_token(LINE_TOKEN);
        case ':': return new_token(COLON_TOKEN);
        case '{': return new_token(LCURBRACES_TOKEN);
        case '}': return new_token(RCURBRACES_TOKEN);
        case '\'':return new_text();
        case '\n':return new_token(LINE_TOKEN);
        case '=': return new_token(is('=')?EQUAL_TOKEN:ASSIGN_TOKEN);
        case '!': return new_token(is('=')?NOT_EQUAL_TOKEN:NOT_TOKEN);
        case '<': return new_token(is('=')?LESS_THAN_OR_EQUAL_TO_TOKEN:LESS_THAN_TOKEN);
        case '>': return new_token(is('=')?GREATER_THAN_OR_EQUAL_TO_TOKEN:GREATER_THAN_TOKEN);
    }
    return new_error_token(ILLEGAL_CHARACTER);
}


