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

/**
 * This function should be called whenever a function definition
 * expression is detected
 */
void DoFunctionDefinition()
{
    auto ast = Parser::parseFunctionDefinition();
    if (ast) {
        if (auto *ir = ast->codegen()){
            fprintf(stderr, "function defintion detected ->");
            ir->print(errs());
            cout << "\n";
        }
    }
    else {
        next();
    }
}

void DoImport()
{
    auto ast = Parser::parseImport();
    if (ast) {
        if (auto *ir = ast->codegen()){
            fprintf(stderr, "import detected ->");
            ir->print(errs());
            cout << "\n";
        }
    }
    else {
        next();
    }
}

void DoTopLevel()
{
    auto ast = Parser::parseTopLevel();
    if (ast) {
        if (auto *ir = ast->codegen()){
            fprintf(stderr, "import detected ->");
            ir->print(errs());
            cout << "\n";
            ir->eraseFromParent();
        }
    }
    else {
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
    bool isnext = true;

    initialize();

    while (isnext == true ? next() : current)
    {
        isnext = true;
        if (current == tok_eof)
        {
            return;
        }
        switch (current)
        {
        case tok_eof:
            return;
        case ')':
            break;
        case ';':
            break;
        case tok_fun:
            DoFunctionDefinition();
            break;
        case tok_im:
            DoImport();
            isnext = false;
            break;
        default:
            DoTopLevel();
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        cout << "ERROR: No input file(s)" << "\n";
        return 1;
    }

    if (exists(argv[1]))
    {
        string text;

        text = readFile(argv[1]);
        run(argv[1], text);
    }
    else
    {
        cout << "ERROR: File does not exists: " << argv[1] << "\n";
        return 1;
    }

    return 0;
}

#endif
