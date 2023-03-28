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
using namespace std;
typedef string str;

vector<Token> execute(str fname, str content) {
    Lexer lexer(fname, content);
    vector<Token> tokens = lexer.lexer();
    return tokens;
}

int main(int argc, char const *argv[])
{
    str filename = "";
    if (argc >= 2){
        filename = argv[1];
        string fname = filename;
    } else {
        cout << "ERROR: no input files." << "\n";
        return 1;
    }
    string contents = "";
    if (exists(filename))
        contents = readFile(filename);
    else {
        cout << "ERROR: file didn't exist." << "\n";
        return 1;
    }
    string ftext = contents;
    try{
        vector<Token> tokens = execute(filename, contents);
        for(long long l = 0; l < tokens.size(); l ++) {
            cout << tokens[l] << ",";
        }
    } catch(...) {
        cout << "Unknown Error Occured.\n";
    }
    return 0;
}
