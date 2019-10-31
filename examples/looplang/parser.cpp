#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "parse_tree.h"

//Function Prototypes
Program_Node *parse_program();
Statement_List_Node *parse_statement_list(Token_Type end);
Statement_Node *parse_statement();
Statement_Node *parse_identifier_expression();
Loop_Stmnt_Node *parse_loop_stmnt();
Print_Stmnt_Node *parse_print_stmnt();
Expression_Node *parse_expression();
Operand_Node *parse_operand();
Token_Node *parse_operator();
Condition_Node *parse_condition();
Token_Node *parse_comparison();

/*
< program > ::= < statement-list >
*/
Program_Node *parse_program() 
{
    next_symbol();
    Program_Node *result = new Program_Node(parse_statement_list(EOF_TOK));
    
    //verification
    mustbe(EOF_TOK);
    return result;
}


/*

< statement-list > ::= < statement > |
                      < statement > < statement-list >
*/
Statement_List_Node *parse_statement_list(Token_Type end)
{
    Statement_List_Node *result = new Statement_List_Node();
    do {
        result->append(parse_statement());
    } while(not have(end));

    return result;
}


/*
< statement > ::= < identifier-expression > |
                 < loop-stmnt > |
                 < print-stmnt > |
                 < expression >
*/
Statement_Node *parse_statement()
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
Loop_Stmnt_Node *parse_loop_stmnt()
{
    //consume the while
    mustbe(WHILE_TOK);
    next_symbol();

    Loop_Stmnt_Node *result = 
      new Loop_Stmnt_Node(parse_condition(),
                          parse_statement_list(END_TOK));

    //consume the end
    mustbe(END_TOK);
    next_symbol();

    return result;
}

/*
< print-stmnt > ::= print < expression >
*/
Print_Stmnt_Node *parse_print_stmnt() 
{
    //consume the print token
    mustbe(PRINT_TOK);
    next_symbol();

    return new Print_Stmnt_Node(parse_expression());
}


/*
< expression > ::= < operand > |
                  < operand > < operator > < expression >
*/
Expression_Node *parse_expression()
{
    Operand_Node * left = parse_operand();
    Token_Node * op = parse_operator();

    if(op != nullptr) {
        return new Expression_Node(left,
                                   op,
                                   parse_expression());
    }

    //end of expression
    return new Expression_Node(left);
}


/*
< identifier-expression > ::= < identifier > < identifier-expression-tail >

< identifier-expression-tail > ::= < operator > < expression > |  
                                   = < expression > |
                                   LAMBDA
*/
Statement_Node *parse_identifier_expression()
{
    //consume the identifier
    mustbe(IDENTIFIER_TOK);
    Operand_Node *left = parse_operand();

    //detect operator case
    Token_Node *op;
    if((op = parse_operator()) != nullptr) {
        return new Expression_Node(left,
                                   op, 
                                   parse_expression());
    } else if(have(ASSIGN_TOK)) {
        next_symbol();
        return new Assignment_Stmnt_Node(left, parse_expression());
    }

    return new Expression_Node(left);
}

/*
< operand > ::= < identifier > | < integer >
*/
Operand_Node * parse_operand()
{
    Operand_Node *result;

    //consume the operand
    if(have(IDENTIFIER_TOK) or have(INTEGER_TOK)) {
        result = new Operand_Node(curr_symbol());
        next_symbol();
    } else {
        mustbe(INTEGER_TOK); //force the error
    }

    return result;
}

/*
< operator > ::= + | -
*/
Token_Node *parse_operator()
{
    //consume the operator
    if(have(PLUS_TOK) or have(MINUS_TOK)) {
        Token_Node *result = new Token_Node(curr_symbol());
        next_symbol();
        return result;
    }

    return nullptr;
}

/*
< condition > ::= < expression > < comparison > < expression >
*/
Condition_Node *parse_condition()
{
    return new Condition_Node( parse_expression(),
                               parse_comparison(),
                               parse_expression() );
}


/*
< comparison > ::= < | <= | > | >= | == | !=
*/
Token_Node *parse_comparison()
{
    //TODO: CLEANUP
    if(have(LESS_TOK) or have(LESS_EQUAL_TOK)) {
    } else if(have(GREATER_TOK) or have(GREATER_EQUAL_TOK)) {
    } else if(have(EQUAL_TOK)) {
    } else {
        mustbe(NOT_EQUAL_TOK);
    }

    Token_Node *result = new Token_Node(curr_symbol());
    next_symbol();
    return result;
}


Parse_Node *parse()
{
    return parse_program();    
}
