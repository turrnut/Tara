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
 * lexutils.h
 * This file provides a place for the lexer, which is
 * defined in file load.h, to store some data. The
 * lexer will have to keep track the location, file name,
 * file text, etc. and with this file it can easily
 * manages the information of the lexer.
 * 
*/
#include <iostream>
using namespace std;
#ifndef LEXUTILS
#define LEXUTILS
class LexerConfig{
    long long cursor;
    long long lcount;
    long long ccount;
    string filename;
    string text; 
    public:
        LexerConfig() {
            this->cursor = -1;
        }
        ~LexerConfig(){
            
        }
        LexerConfig(long long l) {
            this->cursor = l;
        }
        long long getcursor() {
            return this->cursor;
        }
        void setcursor(long long l) {
            this->cursor = l;
            
        }
        string getfilename(){
            return this->filename;
        }
        void setfilename(string name){
            this->filename = name;
        }
        string gettext(){
            return this->text;
        }
        void settext(string filetext){
            this->text = filetext;
        }

        void setlcount(long long count){
            this->lcount = count;
        }

        long long getlcount(){
            return this->lcount;
        }

        void setccount(long long count){
            this->ccount = count;
        }

        long long getccount(){
            return this->ccount;
        }
} lexconfig;
#endif