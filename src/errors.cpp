#include <iostream>
#include <stdlib.h>
using namespace std;
typedef string str;

enum ErrorType{
    ILLEGAL_CHARACTER
};
void quit() {
    exit(EXIT_FAILURE);    
}


void error(ErrorType name, str msg){
    switch (name) {
        case ILLEGAL_CHARACTER:
            cout << "\aIllegalCharacterError" << " : " << msg << "\n"; 
            quit();
            break;
        default:
            return;
            
    }
}

    
