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
 * error.c
 */

#include "error.h"
char* get_error_text(Error err){
    switch (err)
    {
    case ILLEGAL_CHARACTER:
        return "IllegalCharacterError";
    
    case UNTERMINATED_STRING:
        return "UnterminatedStringError";

    case ERROR:
    default:
        return "Error";
        break;
    }
    
}