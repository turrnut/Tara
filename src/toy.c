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
 * toy.c
 * This is the entry point of the program, which contains the
 * main function.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/base.h"
#include "ir/ir.h"
#include "test/test.h"
#include "runtime/runtime.h"
#include "utils/files.h"
#include "code/codegen.h"

int main(int argc, char const *argv[])
{
    switch (argc) {
        case 1:
            printf("ERR: No input file(s). Use the -h option to learn more.\n");
            return 1;
        default:{

            
            int i = 1;
            while (i < argc)
            {
                if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0){
                    version();
                    return 0;
                }

                if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
                    help();
                    return 0;
                }
                if (strcmp(argv[i],"--init") == 0 || strcmp(argv[i], "-i") == 0) {
                    initProject();
                    return 0;
                }

                jit(argv[i]);
                i++;
            }
            break;
            
        }
        
    }
    return 0;
}
