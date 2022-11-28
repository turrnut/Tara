/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 *
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE in the project for
 * more details about how you can use it, you have freedom
 * to distribute and use this file in your project. However,
 * you will have to state changes you made and include the
 * orginal author of this file.
 *
 * load.cpp
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
 * the parser takes the tokens produce by the lexer as input,
 * and parse them into an Abstract Syntax Tree(AST) which
 * consists of different nodes. The AST tells the program
 * the priority of the tokens and which to execute first.
 *
 */

#ifndef LOAD
#define LOAD

#include <vector>
#include <iostream>
#include <cstdlib>
#include <map>
#include <memory>
#include <ctype.h>
#include <stdbool.h>
#include "lexutils.h"
using namespace std;
/*
 * Lexer
 */

/**
 * This enum provides number representaions for different tokens,
 * a token can be seen as one of the numbers in te token class.
 */
enum Token
{
    tok_eof = -1,
    tok_fun = -2,
    tok_im = -3,
    tok_id = -4,
    tok_num = -5,
};
static string idstr;
static double numval;
long long get()
{
    return lexconfig.getcursor();
}
void set(long long l)
{
    lexconfig.setcursor(l);
}
string getfilename()
{
    return lexconfig.getfilename();
}
void setfilename(string name)
{
    lexconfig.setfilename(name);
}
string gettext()
{
    return lexconfig.gettext();
}
void settext(string filetext)
{
    lexconfig.settext(filetext);
}

/**
 * This class gets the current token and return it according to
 * values defined in the enum Token, if its not a token defined
 * in the enum, it will return its ASCII value
 */
static int lex()
{
    if (lexconfig.getfilename().empty() || lexconfig.gettext().empty())
    {
        exit(1);
    }
    string text = lexconfig.gettext();
    string filename = lexconfig.getfilename();
    long long i = 0;
    while (true)
    {
        if (get() == -1)
        {
            set(0);
            lexconfig.setlcount(1);
        }
        static int current = text[get()];

        if (current == EOF || get() >= text.length() - 1)
        {
            return tok_eof;
        }

        long long currentCCount = lexconfig.getccount();
        lexconfig.setccount(1 + currentCCount);
        if (current == '(')
        {
            set(get() + 1);
            current = text[get()];
            if (current == '(')
            {
                set(get() + 1);
                current = text[get()];
            }
            return '(';
        }

        if (current == ')')
        {
            set(get() + 1);
            current = text[get()];
            if (current == ')')
            {
                set(get() + 1);
                current = text[get()];
            }
            return ')';
        }
        if (current == '\n')
        {
            long long currentLCount = lexconfig.getlcount();
            lexconfig.setlcount(1 + currentLCount);
            lexconfig.setccount(0);
        }
        if (current == '\n' || current == '\r' || current == '\t' || current == ' ')
        {
            set(get() + 1);
            current = text[get()];
            continue;
        }
        if (isspace(current))
        {
            set(get() + 1);
            continue;
        }
        if (isalpha(current))
        {
            idstr = current;
            while (isalnum((current = text[get() + 1])))
            {
                idstr += current;
                set(get() + 1);
            }
            if (idstr == "fun")
                return tok_fun;
            if (idstr == "import")
                return tok_im;

            return tok_id;
        }
        if (isdigit(current) || '.' == current)
        {
            string num;
            do
            {
                num += current;
                current = text[get() + 1];
                set(get() + 1);
            } while (isdigit(current) || '.' == current);
            numval = strtod(num.c_str(), 0);
            return tok_num;
        }
        if (current == '#')
        {
            do
            {
                current = text[get() + 1];
                set(get() + 1);
            } while (current != EOF && current != '\n' && current != '\r');
            if (current != EOF)
            {
                return lex();
            }
        }
        int character = current;
        current = text[get() + 1];
        return character;
    }
}

/*
 * Parser
 */

static int current;
static map<char, long long> binpriority;

/**
 * This function sets the priority of the binary operators
 * which is usually called when the compiler first started
 */
static void setbinpriority()
{
    binpriority['>'] = 10;
    binpriority['<'] = 20;
    binpriority['+'] = 30;
    binpriority['-'] = 30;
    binpriority['/'] = 40;
    binpriority['*'] = 60;
    binpriority['^'] = 70;
}

/**
 * This function gets the priority of the current token,
 * which can be used by other parts of the program to
 * determine what token should be evaluated first.
 * The token priority was set through the setbinpriority
 * function.
 */
static long long getTokenpriority()
{
    if (!isascii(current))
    {
        return -1;
    }
    long long priority = binpriority[current];
    if (priority <= 0)
    {
        return -1;
    }
    return priority;
}

/**
 * Advance to the next token and return it
 */
static int next()
{
    current = lex();
    return current;
}

/*
    Nodes in the Abstract Syntax Tree(AST)
*/
/**
 * Base class for all nodes
 */
class Node
{
public:
    Node() {}
    virtual ~Node() {}
};
#include "../error/error.h"

/**
 * This node represent a binary expression which
 * contains a left and right value and an operator
 * in the middle
 */
class BinaryNode : public Node
{
    char o;
    unique_ptr<Node> l;
    unique_ptr<Node> r;

public:
    BinaryNode(unique_ptr<Node> left, char op, unique_ptr<Node> right)
    {
        this->o = op;
        this->l = move(left);
        this->r = move(right);
    }
};

/**
 * This node represent the expression of an
 * invocation of a function, which contains its name
 * and arguments
 */
class FunCallNode : public Node
{
    string name;
    vector<unique_ptr<Node>> args;

public:
    FunCallNode(const string &funname, vector<unique_ptr<Node>> arguments)
    {
        this->name = funname;
        this->args = move(arguments);
    }
};

/**
 * This node represent a number
 */
class NumberNode : public Node
{
    double val;

public:
    NumberNode(double value)
    {
        this->val = value;
    }
};

/**
 * this node represent a variable definition
 */
class VariableNode : public Node
{
    string name;

public:
    VariableNode(string varname)
    {
        this->name = varname;
    }
};

/**
 * This class represent a function type
 */
class FunctionType
{
    string name;
    vector<string> args;

public:
    FunctionType(const string &funname, vector<string> arguments)
    {
        this->name = funname;
        this->args = move(arguments);
    }
    ~FunctionType()
    {
    }
    string &getname()
    {
        return this->name;
    }
};
/**
 * This class represent a function
 */
class Function
{
    unique_ptr<FunctionType> fun;
    unique_ptr<Node> content;

public:
    Function(unique_ptr<FunctionType> type, unique_ptr<Node> body)
    {
        this->fun = move(type);
        this->content = move(body);
    }
};
/**
 * The Parser class parse the tokens. By doing so, several functions were
 * defined in the Parser that parse different tokens.
 *
 */
class Parser
{
public:
    /**
     * This function parse a number
     */
    static unique_ptr<Node> parseNumber()
    {
        auto res = make_unique<NumberNode>(numval);
        next();
        return move(res);
    }

    /**
     * This function should be invoked whenever parenthese(s) are
     * detected
     */
    static unique_ptr<Node> parseParenthese()
    {
        next();
        auto val = parseExpression();
        if (!val)
        {
            return nullptr;
        }
        if (current != ')')
        {
            return error("Expected ')'", PARSE_ERROR);
        }
        next();
        return val;
    }

    /**
     * This function parses an identifier
     */
    static unique_ptr<Node> parseId()
    {
        string id = idstr;
        next();

        if (current != '(')
        {
            return make_unique<VariableNode>(id);
        }
        next();
        vector<unique_ptr<Node>> arguments;

        if (current != ')')
        {
            while (true)
            {
                if (auto argument = parseExpression())
                {
                    arguments.push_back(move(argument));
                }
                else
                {
                    return nullptr;
                }

                if (current != ')')
                {
                    break;
                }

                if (current != ',')
                {
                    return error("Expected ')' or ',' in arguments list", PARSE_ERROR);
                }
                next();
            }
        }
        next();
        return make_unique<FunCallNode>(id, move(arguments));
    }

    /**
     * This function parse a function
     */
    static unique_ptr<FunctionType> parseFunctionType()
    {
        if (current == tok_id)
        {
            string name = idstr;
            next();

            if (current != '(')
            {
                error("Expected '(' in function definition", PARSE_ERROR);
                return nullptr;
            }

            vector<string> arguments;
            while (next() == tok_id)
            {
                arguments.push_back(idstr);
            }

            if (current == ')')
            {
                next();
                return make_unique<FunctionType>(name, move(arguments));
            }
            error("Expected ')' in function definition", PARSE_ERROR);
            return nullptr;
        }
        else
        {
            error("Expected a name for the function", PARSE_ERROR);
            return nullptr;
        }
        error("Expected a name for the function", PARSE_ERROR);
        return nullptr;
    }

    /**
     * This function parse a function definition and should
     * be called whenever there is an function definition
     * statement
     */
    static unique_ptr<Function> parseFunctionDefiniton()
    {
        next();
        auto funtype = parseFunctionType();
        if (!funtype)
        {
            return nullptr;
        }
        auto content = parseExpression();
        if (content)
        {
            return make_unique<Function>(move(funtype), move(content));
        }
        return nullptr;
    }

    /**
     * This function parse an import statement
     */
    static unique_ptr<FunctionType> parseImport()
    {
        next();
        return parseFunctionType();
    }

    /**
     * This function parse a top-level expression
     */
    static unique_ptr<Function> parseTopLevel()
    {
        if (auto content = parseExpression())
        {
            auto type = make_unique<FunctionType>("", vector<string>());
            return make_unique<Function>(move(type), move(content));
        }
        return nullptr;
    }

    /**
     * This function is used to parse the right operator in an
     * expression
     */
    static unique_ptr<Node> parseRightBinaryOperator(int priority, unique_ptr<Node> leftoperator)
    {
        while (true)
        {
            int tokenPriority = getTokenpriority();
            if (tokenPriority < priority)
            {
                return leftoperator;
            }
            int op = current;
            next();
            auto rightoperator = determine();
            if (!rightoperator)
            {
                return nullptr;
            }

            int rightOperatorPriority = getTokenpriority();
            if (tokenPriority < rightOperatorPriority)
            {
                leftoperator = make_unique<BinaryNode>(move(leftoperator), op, move(rightoperator));
            }

            rightOperatorPriority = getTokenpriority();
            if (tokenPriority < rightOperatorPriority)
            {
                rightoperator = parseRightBinaryOperator(1 + tokenPriority, move(rightoperator));
                if (!rightoperator)
                {
                    return nullptr;
                }
            }
            leftoperator = make_unique<BinaryNode>(move(leftoperator), op, move(rightoperator));
        }
    }

    /**
     * This function parse an expression according to its
     * token type which can be determined through the
     * determine function in the same class
     */
    static unique_ptr<Node> parseExpression()
    {
        auto l = determine();
        if (!l)
            return nullptr;
        return parseRightBinaryOperator(0, move(l));
    }

    /**
     * This function is used to determine what is the
     * current token and return the evaluation of it
     * according to its type
     */
    static unique_ptr<Node> determine()
    {
        switch (current)
        {
        default:
            error("unkown token when parsing an expression");
        case tok_id:
            return parseId();
        case tok_num:
            return parseNumber();
        case '(':
            return parseParenthese();
        }
    }
};
#endif
