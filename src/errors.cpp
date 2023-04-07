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
 * errors.cpp
 * 
 * 
*/
#pragma once
#include <iostream>
#include <stdlib.h>
#include "positions.c"
#include "lexer.cpp"
using namespace std;
typedef string str;

enum ErrorType{
    ILLEGAL_CHARACTER,
    EXPECTED_TOKEN
};
void quit() {
    exit(EXIT_FAILURE);    
}


void error(ErrorType name, str msg, Position where, str fname){
    cout << "\a\nError generated while execution." << endl;
    switch (name) {
        case ILLEGAL_CHARACTER:
            cout << "\tIllegalCharacterError : " << msg << endl; 
            break;
        case EXPECTED_TOKEN:
            cout << "\tTokenExpectedError : " << msg << endl;
            break;
        default:
            return;
            
    }
    cout << "At file " << fname << ":" << where.line << ":" << where.col << endl;
    quit();
}

    
