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