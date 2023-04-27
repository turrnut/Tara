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
#include "stdlib.h"
#include "errors.cpp"
#include "lexer.cpp"
using namespace std;
typedef string str;

enum NodeType
{
    UNARY_NODE = -1,
    BINARY_NODE = -2,
    NUMBER_NODE = -3,
    VARIABLE_NODE = -4
};

enum NodeFunction
{
    SCALAR,
    ITEM,
    EXPRESSION
};

class Node
{
public:
    NodeType ntype;
    Token numtoken, operation;
    str varname;

    // C++ forces me to use pointers here ;-(
    Node *left;
    Node *right;
    long long intvalue;
    float decvalue;

    ~Node()
    {
        free(this->left);
        free(this->right);
    }

    Node() = default;

    /** number */
    Node(NodeType ntype, Token token)
    {
        this->ntype = ntype;
        this->numtoken = token;
    }

    /** binary operation */
    Node(NodeType ntype, Node *left, Token operation, Node *right) : ntype(ntype), left(left), right(right), operation(operation) {}

    /** variable*/
    Node(NodeType ntype, str name, long long intvalue) : ntype(ntype), varname(name), intvalue(intvalue){};
    Node(NodeType ntype, str name, long double intvalue) : ntype(ntype), varname(name), decvalue(decvalue){};
};

ostream &operator<<(ostream &os, Node const &n)
{
    switch (n.ntype)
    {
    case NUMBER_NODE:
        return os << "[" << n.ntype << n.numtoken << "]";
    case BINARY_NODE:
        return os << "[" << n.left << n.operation << n.right << "]";
    case VARIABLE_NODE:
        return os << "[variable:" << n.varname << "]";
    default:
        return os << "[" << n.ntype << "]";
    }
}

TokenType arith_operations[] = {PLUS, MINUS, MULTIPLY, DIVIDE, POWER};

class Parser
{
public:
    vector<Token> tokens;
    long index;
    vector<Node> AST;
    Token current;
    ~Parser() {}
    Parser(vector<Token> t) : tokens(t)
    {
        index = -1;
    }

    Node var()
    {
        step(); // name

        str name = this->current.strvalue;
        step(); // {

        if (this->current.type != LEFT_BRACKETS)
        {
            cout << this->current.type;
            error(EXPECTED_TOKEN, "Expected '{' ", this->current.position, thefilename, true);
        }

        Node value;
        value = getNode();
        step();
        if (value.numtoken.type == INTEGER)
        {
            Node thenode(VARIABLE_NODE, name, value.numtoken.value);
            return thenode;
        }
        else if (value.numtoken.type == DECIMAL)
        {
            Node thenode(VARIABLE_NODE, name, value.numtoken.decvalue);
            return thenode;
        }
    }

    Node integer()
    {
        Token e = this->current;
        step();
        return Node(NUMBER_NODE, e);
    }

    Node decimal()
    {
        Token e = this->current;
        step();
        return Node(NUMBER_NODE, e);
    }

    Node getNode()
    {
        step();
        switch (this->current.type)
        {
        default:
            break;
        case INTEGER:
            return integer();

        case DECIMAL:
            return decimal();
        case VARIABLE_DEFINITION:
            return var();
        }
    }

    void parser()
    {
        while (true)
        {
            step(); // expect '('
            if (this->current.type == END_OF_FILE)
                break;

            if (this->current.type == NEW_LINE)

                continue;

            if (this->current.type != LEFT_PARENTHESE)
            {
                cout << this->current.type;
                error(EXPECTED_TOKEN, "Expected '(' ", this->current.position, thefilename, true);
            }
            Node node = getNode();
            this->AST.push_back(node);
        }
    }

    void step()
    {
        this->index++;
        if (this->index < tokens.size())
            this->current = tokens[this->index];
    }
};
