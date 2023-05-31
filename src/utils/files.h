/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 *
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE for more details about
 * how you can use it, you have freedom to distribute and
 * use this code in your project. However, you will have to
 * state changes you made and include the orginal author of
 * this code.
 * 
 * files.h
 * This file provides functions for I/O functions. When the
 * other parts of the program wants to read a code file or
 * any other I/O actions, they will called functions in this
 * file.
*/

char* readFile(const char* filename);
void initProject();
void version();
void help();
int run(const char *filename);