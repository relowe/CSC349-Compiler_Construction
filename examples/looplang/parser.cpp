#include <iostream>
#include "lexer.h"
#include "parser.h"

//Function Prototypes
bool parse_program();
bool parse_statement_list(Token_Type end);
bool parse_statement();
bool parse_identifier_expression();
bool parse_loop_stmnt();
bool parse_print_stmnt();
bool parse_expression();
bool parse_operand();
bool parse_operator();
bool parse_condition();
bool parse_comparison();

/*
< program > ::= < statement-list >
*/
bool parse_program() 
{
    next_symbol();
    bool result = parse_statement_list(EOF_TOK);
    
    //verification
    mustbe(EOF_TOK);
    return result;
}


/*

< statement-list > ::= < statement > |
                      < statement > < statement-list >
*/
bool parse_statement_list(Token_Type end)
{
    do {
        parse_statement();
    } while(not have(end));

    return true;
}


/*
< statement > ::= < identifier-expression > |
                 < loop-stmnt > |
                 < print-stmnt > |
                 < expression >
*/
bool parse_statement()
{
    if(have(WHILE_TOK)) {
        return parse_loop_stmnt();
    } else if(have(PRINT_TOK)) {
        return parse_print_stmnt();
    } else if(have(IDENTIFIER_TOK)) {
        return parse_identifier_expression();
    } else {
        return parse_expression();
    }
}


/*
< loop-stmnt > ::= while < condition > < statement-list > end
*/
bool parse_loop_stmnt()
{
    //consume the while
    mustbe(WHILE_TOK);
    next_symbol();

    bool result = parse_condition() and parse_statement_list(END_TOK);

    //consume the end
    mustbe(END_TOK);
    next_symbol();

    return result;
}

/*
< print-stmnt > ::= print < expression >
*/
bool parse_print_stmnt() 
{
    //consume the print token
    mustbe(PRINT_TOK);
    next_symbol();

    return parse_expression();
}


/*
< expression > ::= < operand > |
                  < operand > < operator > < expression >
*/
bool parse_expression()
{
    parse_operand();

    if(parse_operator()) {
        return parse_expression();
    }

    //end of expression
    return true;
}


/*
< identifier-expression > ::= < identifier > < identifier-expression-tail >

< identifier-expression-tail > ::= < operator > < expression > |  
                                   = < expression > |
                                   LAMBDA
*/
bool parse_identifier_expression()
{
    //consume the identifier
    mustbe(IDENTIFIER_TOK);
    next_symbol();

    //detect operator case
    if(parse_operator()) {
        return parse_expression();
    } else if(have(ASSIGN_TOK)) {
        next_symbol();
        return parse_expression();
    }

    return true;
}

/*
< operand > ::= < identifier > | < integer >
*/
bool parse_operand()
{
    //consume the operand
    if(have(IDENTIFIER_TOK) or have(INTEGER_TOK)) {
        next_symbol();
    } else {
        mustbe(INTEGER_TOK); //force the error
    }

    return true;
}

/*
< operator > ::= + | -
*/
bool parse_operator()
{
    //consume the operator
    if(have(PLUS_TOK) or have(MINUS_TOK)) {
        next_symbol();
        return true;
    }

    return false;
}

/*
< condition > ::= < expression > < comparison > < expression >
*/
bool parse_condition()
{
    bool result;

    result = parse_expression();
    result = result and parse_comparison();
    result = result and parse_expression();

    return result;
}


/*
< comparison > ::= < | <= | > | >= | == | !=
*/
bool parse_comparison()
{
    if(have(LESS_TOK) or have(LESS_EQUAL_TOK)) {
        next_symbol();
        return true;
    } else if(have(GREATER_TOK) or have(GREATER_EQUAL_TOK)) {
        next_symbol();
        return true;
    } else if(have(EQUAL_TOK)) {
        next_symbol();
        return true;
    } else {
        mustbe(NOT_EQUAL_TOK);
        next_symbol();
        return true;
    }
}


bool parse()
{
    return parse_program();    
}
