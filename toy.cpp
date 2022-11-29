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
 * toy.cpp
 * This file is the entry point of the programming language.
 *
 */
#ifndef TOY
#define TOY

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
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

/**
 * Execute the code. First argument is the name of the file and
 * the second argument is the text in the code file
*/
void run(string filename, string text)
{
    setfilename(filename);
    settext(text);
    setbinpriority();
    while ((current = next()))
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

            text = readFile(argv[1]);
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
