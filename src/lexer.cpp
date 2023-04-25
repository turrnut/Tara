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
 * lexer.cpp
 * This file feeds the text to the lexer and break it down in
 * small fragments known as tokens. These tokens are then
 * returned and transferred to the parser.
 * 
*/
#pragma once
#include <iostream>
#include <vector>
#include "errors.cpp"
#include "positions.c"

using namespace std;
typedef string str;

static bool stepnext = true;
static str thefilename;
class Thing{
    
};

/**
 * A list of Token types
*/
enum TokenType{
    INTEGER = -1,
    DECIMAL= -2,
    PLUS= -3,
    MINUS= -4,
    MULTIPLY= -5,
    DIVIDE= -6,
    LEFT_PARENTHESE= -7,
    RIGHT_PARENTHESE= -8,
    FUNCTION_DEFITION = -9,
    VARIABLE_DEFINITION = -10,
    STRING = -11,
    IMPORT_STATEMENT = -12,
    IDENTIFIER = -13,
    COMMA = -14,
    POWER = -15,
    NEW_LINE = -16,
    END_OF_FILE = -17
};

/**
 * The Token class represents a single token. Each token must
 * have a TokenType and optionally a value. Tokens without type
 * will not be allowed. TokenTypes are defined in the TokenType
 * enum.
 * 
*/
class Token: public Thing {
    public:
        TokenType type;
        Position position;

        long long value;
        long double decvalue;
        str strvalue;
        bool isNull;
        Token() = default;
        Token(TokenType type) : type(type), isNull(true), position(clone()){}
        Token(TokenType type, long long value) : type(type), value(value), isNull(false), position(clone()){}
        Token(TokenType type, str strvalue) : type(type), strvalue(strvalue), isNull(false), position(clone()){}
        Token(TokenType type, long double decvalue) : type(type), decvalue(decvalue), isNull(false), position(clone()){}
};

/**
 * Operator override so tokens can be printed to the standard
 * output. The method of printing a token varies according to
 * its type. Sometimes used for testing purposes.
 * 
*/
ostream &operator << (ostream &os, Token const &t) {
    if (t.isNull || t.type == VARIABLE_DEFINITION)
        return os << "<" << to_string(t.type) << ">";
    else {
        if (t.type == INTEGER)
            return os << "<" << to_string(t.type) + ":" + to_string(t.value) << ">";
        else if (t.type == STRING || t.type == FUNCTION_DEFITION || t.type == IMPORT_STATEMENT || t.type == IDENTIFIER) 
            return os << "<" << to_string(t.type) + ":" + t.strvalue << ">";
        else if (t.type == DECIMAL) 
            return os << "<" << to_string(t.type) + ":" + to_string(t.decvalue) << ">";
        
    }
}

/**
 * The Lexer class will take in some text and convert it to
 * a list of tokens and return it.
 * 
*/
class Lexer{
    str content;
    str fname;
    char current;
    vector<Token> tokens;
    bool isShell;
    public:
        ~Lexer(){}
        Lexer(str file_name, str file_text, bool isShell) {
            thefilename = file_name;
            this->isShell = isShell;
            this->fname = file_name;
            this->content = file_text;
            this->current = '\0';
        }
        int step(){
            forward(this->current);
            if (position.index < this->content.size())
                this->current = this->content[position.index];
            return this->current;
        } 
        void back(){
            backward(this->current);
            if (position.index < this->content.size())
                this->current = this->content[position.index];
        } 
        vector<Token> lexer() {
            init_pos();
            do {

                step();
                if (this->current == '\t' || this->current == '\r' || this->current == ' ' || this->current == '\n' || this->current == ';') {
                    if (this->current == '\n') {
                        Token token(NEW_LINE);
                        tokens.push_back(token);
                    }
                    continue;
                }  else if (isdigit(current) || current == '.') {
                    tokens.push_back(number());
                } else if (isalpha(this->current)) {
                    tokens.push_back(id());
                }
                else {
                    switch(this->current) {
                        case '+':
                            add(tokens, Token(PLUS));
                            break;
                        case '-':
                            add(tokens, Token(MINUS));
                            break;
                        case '*':
                            add(tokens, Token(MULTIPLY));
                            break;
                        case '/':
                            add(tokens, Token(DIVIDE));
                            break;
                        case '(':
                            add(tokens, Token(LEFT_PARENTHESE));
                            break;
                        case ')':
                            add(tokens, Token(RIGHT_PARENTHESE));
                            break;
                        case '^':
                            add(tokens, Token(POWER));
                            break;
                        case ',':
                            add(tokens, Token(POWER));
                            break;
                        
                        default:
                            Position where = clone();

                            str character(1, this->current);
                            str fname = this->fname;
                            step();
                            
                            string message = "Illegal Character \'"+character+"\'";
                            error(ILLEGAL_CHARACTER, message, where, fname, this->isShell);
                        
                    }
                }
            }while (position.index <= this->content.length());
            
            Token eof(END_OF_FILE);
            tokens.push_back(eof);
            return tokens;
        }

        void add(vector<Token> list, Token thing) {
            tokens.push_back(thing);
            
        }   

        Token id() {
            if(isalpha(this->current)){
                str idstr = "";
                idstr += this->current;
                while (isalnum((this->current = this->step())))
                    idstr += this->current;
                Token token;
                if (idstr == "fun")
                    token = Token(FUNCTION_DEFITION, idstr);
                if (idstr == "import")
                    token = Token(IMPORT_STATEMENT, idstr);
                if (idstr == "val") {
                    Token v(VARIABLE_DEFINITION);
                    return v;
                }
                else 
                    token = Token(IDENTIFIER, idstr);
                back();
                return token;
            }
        }

        Token number() {
            string numstr = "";
            int dots = 0;

            while(position.index < this->content.size() && (isdigit(this->current) || this->current == '.' || this->current == '\n' || this->current == '\r' || this->current == '\t' || this->current == ' ')) {
                if (this->current == '\n' || this->current == '\r' || this->current == '\t' || this->current == ' ') {
                    step();
                    continue;
                }

                numstr += current;
                if(this->current == '.') {
                    if(dots == 1)
                        break;
                    dots++;
                }
                step();
                
            }
            back();
            if (dots == 0) {
                Token token(INTEGER, stoll(numstr));
                return token;
            }

            Token token(DECIMAL, stold(numstr));
            return token;

        }  

};



