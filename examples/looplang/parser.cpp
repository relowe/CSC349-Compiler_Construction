#include <iostream>
#include "lexer.h"
#include "parser.h"

//Function Prototypes
bool parse_program();
bool parse_statement_list();
bool parse_statement();
bool parse_assignment_stmnt();
bool parse_loop_stmnt();
bool parse_print_stmnt();
bool parse_expression();
bool parse_operand();
bool parse_operator();
bool parse_condition();

/*
< program > ::= < statement-list >
*/
bool parse_program() 
{
    next_symbol();  //get things going
    bool result = parse_statement_list();
    
    //verification
    mustbe(EOF_TOK);
    return result;
}


/*

< statement-list > ::= < statement > |
                      < statement > < statement-list >
*/
bool parse_statement_list()
{
    do {
        parse_statement();
    } while(not have(EOF_TOK));

    return true;
}


/*
< statement > ::= < assignment-stmnt > |
                 < loop-stmnt > |
                 < print-stmnt > |
                 < integer > < operator > <operand> | 
                 < identifier > < operator > < operand >
*/
bool parse_statement()
{
    if(have(WHILE_TOK)) {
        return parse_loop_stmnt();
    } else if(have(PRINT_TOK)) {
        return parse_print_stmnt();
    } else if(have(IDENTIFIER_TOK)) {
        if(have(ASSIGN_TOK)) {
            return parse_expression();
        } else {
            parse_operator();
            return parse_operand();
        }
    } else {
        mustbe(INTEGER_TOK);
        parse_operator();
        return parse_operand();
    }
}


/*
< assignment-stmnt > ::= < identifier > = < expression >

< loop-stmnt > ::= while < condition > < statement-list > end

< print-stmnt > ::= print < expression >

< expression > ::= < operand > |
                  < operand > < operator > < expression >

< operand > ::= < identifier > | < integer >

< operator > ::= + | -

< condition > ::= < expression > < comparison > < expression >

< comparison > ::= < | <= | > | >= | == | !=

< identifier > ::= < letter > | < letter > < identifier' >

< identifier' > ::= \lambda | 
                    < identifier > < digit >  |
                    < identifier > < letter >

< integer > ::= < digit > | < digit > < integer >

< digit >  ::= 0|1|2|3|4|5|6|7|8|9

< letter > ::= a-z | A-Z
*/

bool parser()
{
    return parse_program();    
}
