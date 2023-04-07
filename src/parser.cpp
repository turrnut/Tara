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
#include "errors.cpp"
#include "lexer.cpp"
using namespace std;
typedef string str;

enum VariableType {
    VAL_INTEGER,
    VAL_DECIMAL,
    VAL_STRING
};

class Node {
    public:
        Node() = default;
};

class ChildNode : public Node{
    public:
        ChildNode() = default;
};

class VariableDefinitionNode : public ChildNode {

    public:
        str name;
        
        VariableType type;
        long long ivalue;
        long double dvalue;
        str varname;
        str svalue;
        VariableDefinitionNode() = default;
        VariableDefinitionNode(str varname, long long value) : varname(varname), ivalue(value), type(VAL_INTEGER){}
        VariableDefinitionNode(str varname, long double value) :varname(varname), dvalue(value), type(VAL_DECIMAL){}
        VariableDefinitionNode(str varname, str value) :varname(varname), svalue(value), type(VAL_STRING){}

};

class RootNode : public Node{
    vector<ChildNode> children;
    public:
        RootNode() = default;
        RootNode(vector<ChildNode> c) : children(c){}
        vector<ChildNode> getChildren() {
            return this->children;
        }
        void setChildren(vector<ChildNode> c) {
            this->children = c;
        }
};

class DecimalNumericNode : public ChildNode{
    long double value;
    public:
        DecimalNumericNode(double val) : value(val) {}
        long double getValue() {return this->value;}
};

class IntegerNumericNode : public ChildNode{
    long long value;
    public:
        IntegerNumericNode(long long val) : value(val) {}
        long long getValue() {return this->value;}
};

class VariableReferenceNode : public ChildNode {
    str name;
    public:
        VariableReferenceNode(const str &name) : name(name) {}    
};


class BinaryOperationNode : public ChildNode {
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

class FunctionDefinitionNode : public ChildNode { 
    Function function;
    Node content;
    public:
        FunctionDefinitionNode(Function function, Node content) : function(function), content(content) {}
};

class FunctionCallNode : public ChildNode {
    str callee;
    vector<Node> parameters;
    public:
        FunctionCallNode(str callee, vector<Node> parameters) : callee(callee), parameters(parameters) {}
};

class ImportStatementNode : public ChildNode {
    str name;
    public:
        ImportStatementNode(str name) : name(name) {}
};

class Parser {
    vector<Token> tokens;
    long int index;
    Token current_token;
    str fname;
    public:
        RootNode mynode;
        Parser( str fname, vector<Token> tokens) : tokens(tokens), index(-1), fname(fname){}
        RootNode parser() {
            return mynode;
        }
        
        Token next() {
            this->index++;
            if(this->index < this->tokens.size()) 
                this->current_token = this->tokens[this->index];
            
            return this->current_token;
        }

        void addNode(ChildNode node) {
            vector<ChildNode> newroot = mynode.getChildren();
            newroot.push_back(node);
            mynode = RootNode(newroot);
        }
        void var () {
            // (val keyword)
            next();

            // name
            str vname = this->current_token.strvalue;
            next();

            // (
            next();

            // value
            
            if (current_token.type == INTEGER){
                IntegerNumericNode num = intval();
                cout << vname << "=" << num.getValue() << endl;
                VariableDefinitionNode variable(vname, num.getValue());
                addNode(variable);
            }
            else if (current_token.type == DECIMAL){
                DecimalNumericNode num = decval();
                cout << vname << "=" << num.getValue() << endl;
                VariableDefinitionNode variable(vname, num.getValue());
                addNode(variable);
            }
            next();
            return;
        }
        IntegerNumericNode intval() {
            IntegerNumericNode number(this->current_token.value);
            next();
            if(!(this->current_token.type == RIGHT_PARENTHESE))
                error(EXPECTED_TOKEN, "Expected \')\'", this->current_token.position, this->fname);
            return number;
        }

        DecimalNumericNode decval() {
            DecimalNumericNode number(this->current_token.decvalue);
            next();
            if(!(this->current_token.type == RIGHT_PARENTHESE))
                error(EXPECTED_TOKEN, "Expected \')\'", this->current_token.position, this->fname);
            return number;
        }

        Node getNode(){ 
            while(true){
                next();
                // filter out unnecessary tokens
                if(this->current_token.type == NEW_LINE) {
                    continue;
                }
                if(this->current_token.type == END_OF_FILE){
                    break;
                }

                ///////////////////////
                if(!(this->current_token.type == LEFT_PARENTHESE))
                    error(EXPECTED_TOKEN, "Expected \'(\'", this->current_token.position, this->fname);
                next();
                
                switch(this->current_token.type) {
                    case VARIABLE_DEFINITION:
                        var();
                        break;
                    default:
                        break;
                }
                

            }
            Node node;
            return node;
        }

};

