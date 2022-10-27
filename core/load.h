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
 * load.h
 * This file received raw text, tokenize and parse it,
 * and will output the abstract syntax tree.
 * 
 * lexer
 * The lexer receives raw text, and tokenize the
 * text into tokens. The int lex(string, string)
 * functionwill return a single int value that represents
 * the token defined in enum Token.
 * 
 * parser
 * 
*/
#ifndef __LOAD__
#define __LOAD__
#include <vector>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <ctype.h>
#include "lexutils.h"
using namespace std;
/**
 * Lexer
*/
enum Token {
    tok_eof = -1,
    tok_fun = -2,
    tok_ext = -3,
    tok_id  = -4,
    tok_num = -5,
};
static string idstr;
static double numval;
long long get(){
    return lexconfig.getcursor();
}
void set(long long l){
    lexconfig.setcursor(l);
}
string getfilename(){
    return lexconfig.getfilename();
}
void setfilename(string name){
    lexconfig.setfilename(name);
}
string gettext(){
    return lexconfig.gettext();
}
void settext(string filetext){
    lexconfig.settext(filetext);
}
static int lex() {
    if (lexconfig.getfilename().empty() || lexconfig.gettext().empty()) {
        exit(1);
    }
    string text = lexconfig.gettext();
    string filename = lexconfig.getfilename();
    long long i = 0;
    while (true){
        if (get() == -1) {
            set(0);
        }
        static int current = text[get()];

        if (current == EOF || get() >= text.length() -1) {
            return tok_eof;
        }
        if (current == '\n' || current == '\r' || current == '\t' || current == ' '){
            set(get() + 1);
            current = text[get()];
            continue;
        }
        if (isspace(current)){
            set(get() + 1);
            continue;
        }
        if(isalpha(current)){
            idstr = current;
            while(isalnum((current = text[get() + 1]))){
                idstr += current;
                set(get() + 1);
            }
            if (idstr == "fun")
                return tok_fun;
            if (idstr == "import")
                return tok_ext;
            return tok_id;
        }
        if (isdigit(current) || '.' == current){
            string num;
            do {
                num += current;
                current = text[get() + 1];
                set(get() + 1);
            } while (isdigit(current) || '.' == current);
            numval = strtod(num.c_str(), 0);
            return tok_num;
        }
        if (current == '#') {
            do
            {
                current = text[get() + 1];
                set(get() + 1);
            } while (current != EOF && current != '\n' && current != '\r');
            if (current != EOF) {
                return lex();
            }
        }
        int character = current;
        current = text[get() + 1];
        return character;
    }
}

/**
 * Parser
*/

static int current;
static int next() {
    current = lex();
    return current;
}


/*
    Nodes in the Abstract Syntax Tree(AST)
*/
// Base class for all nodes
class Node {
    public:
        Node(){ }
        virtual ~Node(){ }
};
class BinaryNode : public Node{
    char o;
    unique_ptr<Node> l;
    unique_ptr<Node> r;
    public:
        BinaryNode(char op, unique_ptr<Node> right, unique_ptr<Node> left){
            this->o = op;
            this->l = move(left);
            this->r = move(right);
        }
};
class FunCallNode : public Node {
    string name;
    std::vector<unique_ptr<Node>> args;
    public:
        FunCallNode(const string &funname, std::vector<unique_ptr<Node>> arguments){
            this->name = funname;
            this->args = move(arguments);
        }
};
class NumberNode : public Node {
    double val;
    public:
        NumberNode(double value) {
            this->val = value;
        }
};
class VariableNode : public Node {
    string name;
    public:
        VariableNode(string varname){
            this->name = varname;
        }
};
class FunctionType{
    string name;
    vector<string> args;
    public:
        FunctionType(const string &funname, vector<string> arguments){
            this->name = funname;
            this->args = move(arguments);
        }
        ~FunctionType(){

        }
        string &getname(){
            return this->name;
        }
};
class Function{
    unique_ptr<FunctionType> fun;
    unique_ptr<Node> content;

    public:
        Function(unique_ptr<FunctionType> type, unique_ptr<Node> body){
            this->fun = move(type);
            this->content = move(body);
        }
};

/**
 * The class that parse the tokens.
*/
class Parser{
    public:
        static unique_ptr<Node> parseNumber(){
            auto res = make_unique<NumberNode>(numval);
            next();
            return move(res);
        }

};
#endif
