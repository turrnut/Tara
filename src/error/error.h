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
 * error.h
 * 
 */
#ifndef error_header
#define error_header
typedef enum {
    ERROR, ILLEGAL_CHARACTER, UNTERMINATED_STRING
} Error;
char* get_error_text(Error err);
#endif