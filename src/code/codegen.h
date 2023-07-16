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
 * codegen.h
 * Declares the functionality needed to generate IR(Intermediate
 * Representation). It takes in a series of tokens and compile
 * it into IR. The IR can then be executed by the Language
 * Runtime. Specific implementation can be found in codegen.c
 * in the same directory as this file.
 * 
 */

#ifndef codegen_header
#define codegen_header
#include "../runtime/runtime.h"
#include "../ir/ir.h"
#include "../error/error.h"
#include "../types/types.h"
#include "lexer.h"

typedef void (*CompilerFunction)();

/**
 * Struct that represents a compiler
*/
typedef struct {
    Token current; // Token that is currently being compiled
    Token before; // Token that was being compiled before current
    bool flag; // Boolean flag whether the compiler has error or no
    const char *filename; // The name of the file
} Compiler;

typedef enum {  // From low priority
    NO_PRIORITY,
    ASSIGN_PRIORITY,
    OR_PRIORITY,
    AND_PRIORITY,
    EQ_PRIORITY,
    COMP_PRIORITY,
    TERM_PRIORITY,
    FACTOR_PRIORITY,
    UNARY_PRIORITY,
    FUNCALL_PRIORITY,
    PRIMARY_EXPR_PRIORITY
} Priority; // To high priority

/**
 * Struct that represents configurations for the compiler.
*/
typedef struct
{
    CompilerFunction prefix; // Not null if it is a prefix expression
    CompilerFunction infix; // Not null if it is a infix expression
    Priority priority; // Priority of the expression
} CompilerConfig;

/**
 * Represents whether the execution is successful or not.
*/
typedef enum {
    /**
     * Error during compilation
    */
    CODEGEN_ERROR,

    /**
     * Flawlessly finished compilation
    */
    CODEGEN_OK
} CodeGenerationResult;

/**
 * Function that compiles the code with the given priority
 * level in the arguments.
*/
void compile_with_priority(Priority p);

/**
 * Check to see the priority configuration level of the given
 * Token Type.
*/
CompilerConfig* see_config(TokenTypes p);

/**
 * Compiles a unary expression.
*/
void get_unary();

/**
 * Compiles for predefined values such as boolean values
 * and null values.
*/
void get_value();

/**
 * Function for handle parentheses
*/
void get_group();

/**
 * Get the IR currently working with
*/
IR* get_current_ir();

/**
 * This function write some bytecode. When using, please
 * specifiy the amount in the first argument and then everything
 * else is a type of the uint8_t or a member of the InsCode enum.
*/
void write_byte(int amount,...);

/**
 * Compile data into instruction code
*/
uint8_t produce_data(Data dob);

/**
 * Write some bytes but in the form of Data
*/
void write_data(Data dob);

/**
 * Report the current token as an error
*/
void errorNow(const char* msg);

/**
 * Report the previous token as an error
*/
void errorPrevious(const char* msg);

/**
 * Go to the next token
*/
void codegen_next();

/**
 * Compiles a single number literal
*/
void get_number();

/**
 * Compiles a binary expression
*/
void get_binary();

/**
 * Compile an expression.
*/
void get_expr();

/**
 * Compiles a declaration using the function.
*/
void get_declaration();

/**
 * Compiles a sentence using this function.
*/
void get_sentence();

/**
 * Compiles an expression in a sentence
*/
void get_expr_in_sentence();

/**
 * Compiles a trace sentence using this function.
*/
void get_trace_sentence();

/**
 * Check to see if the current token type can be the given
 * argument.
*/
bool be(TokenTypes tokenType);

/**
 * Helper function of the be function
*/
bool checkTokenType(TokenTypes tokenType);

/**
 * This function eat the next token and check to see if that
 * token's type match the token type in the argument. If so,
 * nothing happens, if not, throw the error.
*/
void eat(TokenTypes tok, Error throwIfFailed);

/**
 * Takes in the file name, source code, then transform it
 * into a series of tokens before producing IR.
*/
CodeGenerationResult codegen(const char* filename, const char* src, IR* ir);
#endif
