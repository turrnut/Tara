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
    STRING = -9
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

        long long value;
        long double decvalue;
        str strvalue;
        bool isNull;
        Token(TokenType type){
            this->type = type;
            this->isNull = true;
        }
        Token(TokenType type, long long value){
            this->type = type;
            this->value = value;
            this->isNull = false;
        }
        Token(TokenType type, str strvalue){
            this->type = type;
            this->strvalue = value;
            this->isNull = false;
        }

        Token(TokenType type, long double decvalue){
            this->type = type;
            this->decvalue = decvalue;
            this->isNull = false;
        }
};

/**
 * Operator override so tokens can be printed to the standard
 * output. The method of printing a token varies according to
 * its type. Sometimes used for testing purposes.
 * 
*/
ostream &operator << (ostream &os, Token const &t) {
    if (t.isNull)
        return os << "<" << to_string(t.type) << ">";
    else {
        if (t.type == INTEGER)
            return os << "<" << to_string(t.type) + ":" + to_string(t.value) << ">";
        else if (t.type == STRING)
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
    public:
        Lexer(str file_name, str file_text) {
            this->fname = file_name;
            this->content = file_text;
            this->current = '\0';
        }
        void step(){
            forward(this->current);
            if (position.index < this->content.size())
                this->current = this->content[position.index];
        } 
        void back(){
            backward(this->current);
            if (position.index < this->content.size())
                this->current = this->content[position.index];
        } 
        vector<Token> lexer() {
            init_pos();
            do {
                cout << "current position: " << position.index << "," << position.line << "," << position.col << "\n";
                step();
                if (this->current == '\t' || this->current == '\r' || this->current == ' ' || this->current == '\n') {
                    continue;
                }  else if (isdigit(current) || current == '.') {
                    tokens.push_back(number());
                } else {
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
                        
                        default:
                            Position where = clone();

                            str character(1, this->current);
                            str fname = this->fname;
                            step();
                            
                            string message = "Illegal Character \'"+character+"\'";
                            error(ILLEGAL_CHARACTER, message, where, fname);
                        
                    }
                }
            }while (position.index <= this->content.length());
            

            return tokens;
        }

        void add(vector<Token> list, Token thing) {
            tokens.push_back(thing);

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



