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
 * toy.cpp
 * This file is the entry point of the programming language.
 * It contains the main function.
 */
#include <iostream>
#include <vector>
#include "files.h"
#include "lexer.cpp"
#include "parser.cpp"
using namespace std;
typedef string str;

static str version_info = "1.0.0";
static str fname;
void execute(str filename, str content, bool shell)
{
    fname = filename;
    Lexer lexer(fname, content, shell);
    vector<Token> tokens = lexer.lexer();
    Parser parser(tokens);
    parser.parser();

    for (int i = 0; i < parser.AST.size(); i++)
    {
        Node e = parser.AST[i];
        int val = e.intvalue;
        cout << val << endl;
    }
}

int main(int argc, char const *argv[])
{
    str filename = "";
    if (argc >= 2)
    {
        filename = argv[1];
        string fname = filename;
    }
    else
    {
        cout << "ERROR: no input file.";
        return 1;
    }
    string contents = "";
    if (exists(filename))
        contents = readFile(filename);
    else
    {
        cout << "ERROR: file didn't exist."
             << "\n";
        return 1;
    }
    string ftext = contents;
    try
    {
        execute(filename, contents, false);
    }
    catch (...)
    {
        cout << "Unknown Error Occured.\n";
    }
    return 0;
}
