#include <iostream>
#include <vector>
#include "errors.cpp"
using namespace std;
typedef string str;
static string content;

class Thing{
    public:
        str get_string() {
            return "";
        }
};

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

class Lexer{
    str content;
    int pos;
    char current;
    vector<Token> tokens;
    public:
        Lexer(str content) {
            this->content = content;
            this->pos = -1;
            this->current = '\0';
        }
        void step(){
            this->pos++;
            if (this->pos < this->content.size())
                this->current = this->content[pos];
        } 
        void back(){
            this->pos--;
            if (this->pos < this->content.size())
                this->current = this->content[pos];
        } 
        vector<Token> lexer() {
            do {
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
                            str character(1, this->current);
                            step();
                            vector<Token> empty;
                            error(ILLEGAL_CHARACTER,"Illegal Character \'"+character+"\'");
                        
                    }
                }
            }while (this->pos <= this->content.length());
            

            return tokens;
        }

        void add(vector<Token> list, Token thing) {
            tokens.push_back(thing);

        }   
        Token number() {
            string numstr = "";
            int dots = 0;
            
            while(this->pos < this->content.size() && (isdigit(this->current) || this->current == '.')) {
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
            cout<< "!" << stold(numstr) << "!" << "\n";
            return token;

        }  

};

vector<Token> execute(str text) {
    content = text;
    Lexer lexer(content);
    vector<Token> tokens = lexer.lexer();
    return tokens;
}



