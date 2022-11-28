/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 *
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE in the project for
 * more details about how you can use it, you have freedom
 * to distribute and use this file in your project. However,
 * you will have to state changes you made and include the
 * orginal author of this file.
 *
 * error.h
 * This file includes the function for error logs. When the
 * compiler found a problem, it calles functions in this
 * file to report it.
 */

#ifndef __ERROR__
#define __ERROR__
#include <iostream>
#include <stdlib.h>
#include "../core/load.cpp"

enum ErrorTypes
{
    ERROR = 1,
    PARSE_ERROR = 2
} errtypes;

/**
 * This functions prints the error according to its name and
 * message associated to it
 */
unique_ptr<Node> errorWithName(const char *msg, const char *errorname)
{
    cout << "\a\n"
         << errorname << ": " << msg << "\nFile: " << lexconfig.getfilename() << ":" << lexconfig.getlcount() << ":" << lexconfig.getccount() << "\n";
    return nullptr;
}

/**
 * This function reports an error
 */
unique_ptr<Node> error(const char *msg)
{
    return errorWithName(msg, "Error");
}

/**
 * This function reports a parse error, parse errors are usually
 * caused by incorrect syntaxes.
 */
unique_ptr<Node> parseerror(const char *msg)
{
    return errorWithName(msg, "ParseError");
}

/**
 * This function reports an error according to the type of the
 * error, all error types are define in enum ErrorTypes
 */
unique_ptr<Node> error(const char *msg, int type)
{
    switch (type)
    {
    case 1:
        return error(msg);
        break;
    case 2:
        return parseerror(msg);
        break;
    default:
        return error(msg);
    }
}

#endif
