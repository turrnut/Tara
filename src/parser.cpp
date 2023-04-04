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
 * 
*/
#pragma once
#include <iostream>
#include <vector>
#include "lexer.cpp"
using namespace std;
typedef string str;

class Node {
    public:
        Node() = default;
};

class NumericNode : public Node{
    double value;
    public:
        NumericNode(double val) : value(val) {}
};

class VariableReferenceNode : public Node {
    str name;
    public:
        VariableReferenceNode(const str &name) : name(name) {}    
};

class BinaryOperationNode : public Node {
  char operation;
  Node left, right;

public:
  BinaryOperationNode(char operation, Node left, Node right) : operation(operation), left(left), right(right) {}
};

class Function {
    public:
        str funname;
        vector<Node> arguments;
        Function(str funname, vector<Node> arguments) : funname(funname), arguments(arguments) {}
};

class FunctionDefinitionNode : public Node { 
    Function function;
    Node content;
    public:
        FunctionDefinitionNode(Function function, Node content) : function(function), content(content) {}
};

class FunctionCallNode : public Node {
    str callee;
    vector<Node> parameters;
    public:
        FunctionCallNode(str callee, vector<Node> parameters) : callee(callee), parameters(parameters) {}
};

class ImportStatementNode : public Node {
    str name;
    public:
        ImportStatementNode(str name) : name(name) {}
};

class Parser {
    vector<Token> tokens;
    long int index;
    Token current_token;
    Node mynode;
    public:
        Parser(vector<Token> tokens) : tokens(tokens), index(-1){}
        Token next() {
            this->index++;
            if(this->index < this->tokens.size()) 
                this->current_token = this->tokens[this->index];
            
            return this->current_token;
        }
        Node getNode(){ 
            do {
                next();
            } while(index < tokens.size());
            Node node;
            return node;
        }

};

