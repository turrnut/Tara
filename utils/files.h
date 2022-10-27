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
 * files.h
 * This file provides functions for I/O functions. When the
 * other parts of the program wants to read a code file or
 * any other I/O actions, they will called functions in this
 * file.
*/

#include <iostream>
#include <sys/stat.h>
#include <fstream>
using namespace std;
bool exists (string filename) {
  struct stat buffer;
  int status = stat(filename.c_str(), &buffer);
  return status == 0; 
}

string readFile(string filename){
    string text = "";
    string res;
    ifstream file(filename);
    while (getline (file, text)) {
        res = res + text + "\n";
    }
    file.close();
    return res;
}