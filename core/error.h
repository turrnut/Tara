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
 * error.h
 * This file includes the function for error logs. When the
 * compiler found a problem, it calles functions in this
 * file to report it.
*/

#ifndef __ERROR__
#define __ERROR__
#include <iostream>
#include <stdlib.h>
#include "load.h"

unique_ptr<int> error(const char* msg){
    fprintf(stderr,"Error: %s\n",msg);
    return nullptr;
}
#endif
