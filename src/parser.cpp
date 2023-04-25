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
 * parser.cpp
 * The parser takes in a list of tokens and convert it to 
 * a tree of nodes called the AST(Abstract Syntax Tree)
 * and return to the main program.
 * 
*/
#pragma once
#include <iostream>
#include <vector>
#include "errors.cpp"
#include "lexer.cpp"
using namespace std;
typedef string str;

enum NodeType {
    UNARY_NODE,
    BINARY_NODE,
    NUMBER_NODE
};

class Node{
    public:
        NodeType type;
        Token numtoken, operation;

        // C++ forces me to use pointers here ;-(
        Node* left;
        Node* right;

        ~Node() {}

        // number node
        Node(NodeType type, Token token) {
            this->type = type;
            this->numtoken = token;
        }

        // binary node
        Node(Node* left, Token operation, Node* right):left(left), right(right), operation(){}

};

ostream &operator << (ostream &os, Node const &n) {
    switch(n.type) {
        case NUMBER_NODE:
            return os << "[" << n.type << "]";
        case BINARY_NODE:
            return os << "[" << n.left << n.operation << n.right << "]";
        default:
            return os << "[" << n.type << "]";
    }
}

TokenType arith_operations[] = {PLUS, MINUS, MULTIPLY, DIVIDE, POWER}; 

class Parser {
    public:
        vector<Token> tokens;
        long index;
        Token current;
        ~Parser() {}
        Parser(vector<Token> tokens) : tokens(tokens) {
            index = -1;
            step();
        }

        void step() {
            index ++;
            if (index < tokens.size())
                current = tokens[index];
        }
};

