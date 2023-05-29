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
 * Implementation of codegen.h header. To read more documentation
 * please visit codegen.h
 */

#include <stdarg.h>
#include <stdlib.h>
#include "codegen.h"
#include "lexer.h"
#include "../base/base.h"
#include "../error/error.h"
#include "../test/test.h"

Compiler compiler;
IR *compiling;

IR *get_current_ir() {
    return compiling;
}



void compile_with_priority(Priority p) {
    codegen_next();
    CompilerFunction prefixfunction = see_config(compiler.before.type)->prefix;
    if (prefixfunction == NULL) {
        errorPrevious(get_error_text(EXPECT_EXPRESSION));
        return;
    }
    prefixfunction();
    while(p <= see_config(compiler.current.type)->priority){
        codegen_next();
        CompilerFunction infixfunction = see_config(compiler.before.type)->infix;
        infixfunction();
    }
}
void get_expr(){
    compile_with_priority(ASSIGN_PRIORITY);
}

/**
 * Configurations for the compiler, it determines the priority
 * of different tokens and its types.
*/
CompilerConfig configurations[] = {
    [LPAREN_TOKEN]={group,NULL,NO_PRIORITY},
    [RPAREN_TOKEN]={NULL,NULL,NO_PRIORITY},
    [LCURBRACES_TOKEN]={NULL,NULL,NO_PRIORITY},
    [RCURBRACES_TOKEN]={NULL,NULL,NO_PRIORITY},
    [COMMA_TOKEN]={NULL,NULL,NO_PRIORITY},
    [DOT_TOKEN]={NULL,NULL,NO_PRIORITY},
    [SUB_TOKEN]={get_unary,get_binary,TERM_PRIORITY},
    [ADD_TOKEN]={NULL,get_binary,TERM_PRIORITY},
    [LINE_TOKEN]={NULL,NULL,NO_PRIORITY},
    [DIV_TOKEN]={NULL,get_binary,FACTOR_PRIORITY},
    [MUL_TOKEN]={NULL,get_binary,FACTOR_PRIORITY},
    [NOT_TOKEN]={NULL,NULL,NO_PRIORITY},
    [NOT_EQUAL_TOKEN]={NULL,NULL,NO_PRIORITY},
    [ASSIGN_TOKEN]={NULL,NULL,NO_PRIORITY},
    [EQUAL_TOKEN]={NULL,NULL,NO_PRIORITY},
    [GREATER_THAN_TOKEN]={NULL,NULL,NO_PRIORITY},
    [GREATER_THAN_OR_EQUAL_TO_TOKEN]={NULL,NULL,NO_PRIORITY},
    [LESS_THAN_TOKEN]={NULL,NULL,NO_PRIORITY},
    [LESS_THAN_OR_EQUAL_TO_TOKEN]={NULL,NULL,NO_PRIORITY},
    [ID_TOKEN]={NULL,NULL,NO_PRIORITY},
    [STRING_TOKEN]={NULL,NULL,NO_PRIORITY},
    [NUMBER_TOKEN]={get_number,NULL,NO_PRIORITY},
    [AND_TOKEN]={NULL,NULL,NO_PRIORITY},
    [CLASS_TOKEN]={NULL,NULL,NO_PRIORITY},
    [ELSE_TOKEN]={NULL,NULL,NO_PRIORITY},
    [ELIF_TOKEN]={NULL,NULL,NO_PRIORITY},
    [FALSE_TOKEN]={NULL,NULL,NO_PRIORITY},
    [FOR_TOKEN]={NULL,NULL,NO_PRIORITY},
    [FUNCTION_TOKEN]={NULL,NULL,NO_PRIORITY},
    [IF_TOKEN]={NULL,NULL,NO_PRIORITY},
    [NULL_TOKEN]={NULL,NULL,NO_PRIORITY},
    [OR_TOKEN]={NULL,NULL,NO_PRIORITY},
    [TRACE_TOKEN]={NULL,NULL,NO_PRIORITY},
    [RETURN_TOKEN]={NULL,NULL,NO_PRIORITY},
    [SUPER_TOKEN]={NULL,NULL,NO_PRIORITY},
    [THIS_TOKEN]={NULL,NULL,NO_PRIORITY},
    [TRUE_TOKEN]={NULL,NULL,NO_PRIORITY},
    [VARIABLE_TOKEN]={NULL,NULL,NO_PRIORITY},
    [WHILE_TOKEN]={NULL,NULL,NO_PRIORITY},
    [ERROR_TOKEN]={NULL,NULL,NO_PRIORITY},
    [EOF_TOKEN]={NULL,NULL,NO_PRIORITY},
};
CompilerConfig* see_config(TokenTypes p) {
    return &configurations[p];
}
void write_byte(int amount, ...) {
    va_list ap;
    int i;
    uint8_t val;

    va_start(ap, amount);

    for (i = 0; i < amount; i++)
    {
        val = va_arg(ap, int);
        createIR(get_current_ir(), val, compiler.before.pos);
    }

    va_end(ap);
}


void reportCompileError(const char *filename, Token *token, const char *err) {
    printf("\a\nError generated during compilation.\n\t");
    printf("%s\nAt file %s:%i:%i\n", err, filename, token->pos.row, token->pos.col);
}

void reportRuntimeError(const char *filename, Token *token, const char *err) {
    printf("\a\nError generated during runtime.\n");
    printf("%s\nAt file %s:%i:%i\n", err, filename, token->pos.row, token->pos.col);
}

void eat(TokenTypes tok, Error throwIfFailed) {
    if (compiler.current.type == tok)
    {
        codegen_next();
        return;
    }
    errorNow(get_error_text(throwIfFailed));
}

void errorNow(const char *msg)
{
    if (compiler.flag)
        return;
    compiler.flag = true;
    reportCompileError(compiler.filename, &compiler.current, msg);
}

void errorPrevious(const char *msg)
{
    if (compiler.flag)
        return;
    compiler.flag = true;
    reportCompileError(compiler.filename, &compiler.before, msg);
}

void codegen_next()
{
    compiler.before = compiler.current;
    while (1) {
        compiler.current = get_token();
        if (compiler.current.type == IGNORE_TOKEN)
            continue;
        
        if (compiler.current.type != ERROR_TOKEN)
            break;
        else
            errorNow(compiler.current.first);
    }
}

void end_codegen()
{
    write_byte(1,INS_RETURN);
    #ifdef COMPILE_DEBUG_MODE
        if (!compiler.flag) {
            showIR(get_current_ir(), "bytecode");
        }
    #endif
}

void group() {
    get_expr();
    eat(RPAREN_TOKEN, EXPECT_CHAR_RPAREN);
}

uint8_t produce_data(Data dob) {
    int dat = addData(get_current_ir(), dob);
    if (dat > UINT8_MAX) {
        errorPrevious(get_error_text(VALUE_TOO_LARGE));
        return 0;
    }
    return (uint8_t) dat;
}

void write_data(Data dob) {
    write_byte(2, INS_DATA, produce_data(dob));
}
void get_binary() {
    TokenTypes op_type = compiler.before.type;
    CompilerConfig* cfg = see_config(op_type);
    compile_with_priority((Priority)(cfg->priority + 1));
    switch (op_type) {
    case ADD_TOKEN:
        write_byte(1, INS_ADD);
        break;
    case SUB_TOKEN:
        write_byte(1, INS_SUB);
        break;
    case MUL_TOKEN:
        write_byte(1, INS_MUL);
        break;
    case DIV_TOKEN:
        write_byte(1, INS_DIV);
        break;
    default:
        return;
    }
}

void get_number() {
    double dob = strtod(compiler.before.first, NULL);   
    write_data(dob);
}

void get_unary(){
    TokenTypes op = compiler.before.type;
    compile_with_priority(UNARY_PRIORITY);
    switch (op) {
    case SUB_TOKEN:
        write_byte(1, INS_NEGATIVE);
        break;
    
    default:
        return;
    }
}


CodeGenerationResult codegen(const char *fn, const char *src, IR *ir)
{
    compiler.flag = false;
    compiler.filename = fn;
    compiling = ir;
    new_lexer(src);
    codegen_next();
    get_expr();
    eat(EOF_TOKEN, EXPECT_END);
    end_codegen();
    if (compiler.flag)
        return CODEGEN_ERROR;
    else
        return CODEGEN_OK;
}
