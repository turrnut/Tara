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
 *
 */
#ifndef TOY
#define TOY
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "core/load.cpp"
#include "utils/files.h"
using namespace std;

void HandleDefinition()
{
    if (Parser::parseFunctionDefiniton())
    {
        fprintf(stderr, "Parsed a function definition.\n");
    }
    else
    {
        next();
    }
}

void HandleImport()
{
    if (Parser::parseImport())
    {
        fprintf(stderr, "Parsed an import\n");
    }
    else
    {
        next();
    }
}

void HandleTopLevel()
{
    if (Parser::parseTopLevel())
    {
        fprintf(stderr, "Parsed a top-level expression\n");
    }
    else
    {
        next();
    }
}

void run(string filename, string text)
{
    setfilename(filename);
    settext(text);
    setbinpriority();
    // int tok = lex();
    // cout << tok << ", ";
    // tok = lex();
    // cout << tok;
    while (current = next())
    {
        if (current == EOF)
        {
            return;
        }
        switch (current)
        {
        case ';':
            next();
            break;
        case tok_fun:
            HandleDefinition();
            break;
        case tok_im:
            HandleImport();
            break;
        default:
            HandleTopLevel();
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        if (exists(argv[1]))
        {
            string text;

            try
            {
                text = readFile(argv[1]);
            }
            catch (exception e)
            {
                cout << "ERROR: Cannot open the file" << argv[1];
                return 1;
            }
            run(argv[1], text);
        }
        else
        {
            cout << "ERROR: File does not exists: " << argv[1];
            return 1;
        }
    }
    return 0;
}

#endif
