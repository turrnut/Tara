#include <iostream>
#include <vector>
#include "files.h"
#include "lexer.cpp"
using namespace std;
typedef string str;

int main(int argc, char const *argv[])
{
    str filename = "";
    if (argc >= 2){
        filename = argv[1];
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
    try{
        vector<Token> tokens = execute(contents);
        for(long long l = 0; l < tokens.size(); l ++) {
            cout << tokens[l] << ",";
        }
    } catch(...) {
        cout << "Unknown Error Occured.\n";
    }
    return 0;
}
