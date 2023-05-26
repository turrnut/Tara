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
 * codegen.c
 * Implementation of codegen.h, it takes in the source code
 * and compile it into IR(Intermediate Representation). The
 * IR can then be executed by the Language runtime.
 */

#include "codegen.h"
#include "lexer.h"

/**
 * Takes in the source code, then transform it into a series
 * of tokens before producing IR.
*/
CodeGenerationResult codegen(const char* src){
    new_lexer(src);
    // codegen_next_char();
    // get_expr();
    // eat(EOF_TOKEN);
    Position pos_tracker = {-1,0};
    while(1){
        Token token = get_token();
        if ((token.pos.row != pos_tracker.row) || (token.pos.col != pos_tracker.col)) {
            printf("%4d:%4d\t", token.pos.row, token.pos.col);
            pos_tracker.row = token.pos.row;
            pos_tracker.col = token.pos.col;
        }
        printf("%2d '%.*s'\n", token.type, token.len, token.first);
        if(token.type == EOF_TOKEN)
            break;
    }
}
