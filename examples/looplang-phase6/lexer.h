//Definitions for the lexical analyzer
#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <string>

enum Token_Type { INVALID_TOK=0, ASSIGN_TOK, PLUS_TOK, MINUS_TOK, LESS_TOK,
                  LESS_EQUAL_TOK, GREATER_TOK, GREATER_EQUAL_TOK, EQUAL_TOK,
                  NOT_EQUAL_TOK, INTEGER_TOK, IDENTIFIER_TOK, WHILE_TOK,
                  END_TOK, PRINT_TOK, EOF_TOK}; 
struct Token {
    Token_Type type;  //type of the token
    std::string repn; //representation of the token
};

//lexer interface
void next_symbol();        //get the next symbol
Token curr_symbol();       //return the current symbol
bool have(Token_Type t);   //if we have the token, advance and return true 
                           //false (with no advance) o.w.
void mustbe(Token_Type t); //like have, but prints error message on failure
std::ostream & operator<<(std::ostream &os, Token t);
#endif
