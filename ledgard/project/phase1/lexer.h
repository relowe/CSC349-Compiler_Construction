/**
   @file lexer.h
   @author Lee Wittenberg
   @date 2017-05-31
   @version 2.0

   Interface for Lexer class to perform lexical analysis
   for the Ledgard language.
 */
#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <queue>

enum Token_Type {INVALID_TOK, PROG_TOK, BEGIN_TOK, END_TOK, SEMI_TOK,
   COLON_TOK, COMMA_TOK, INTEGER_TOK, BOOLEAN_TOK, ARRAY_TOK, 
   LBRACK_TOK, RBRACK_TOK, OF_TOK, DOTDOT_TOK, ASSIGN_TOK, XCHG_TOK,
   IF_TOK, THEN_TOK, ELSE_TOK, WHILE_TOK, LOOP_TOK, INPUT_TOK, OUTPUT_TOK,
   LPAREN_TOK, RPAREN_TOK, NOT_TOK, TRUE_TOK, FALSE_TOK,
   LT_TOK, LE_TOK, EQ_TOK, NE_TOK, GE_TOK, GT_TOK,
   PLUS_TOK, MINUS_TOK, TIMES_TOK, DIV_TOK, AND_TOK, OR_TOK,
   IDENT_TOK, INT_LITERAL_TOK,
   EOF_TOK};

struct Token
{
   Token_Type tok;      // the token code
   std::string repn;    // the actual token
   int line_number;     // line on which the token occurs
};

class Lexer
{
public:
   Lexer(std::istream& f);    // construct a Lexer from a given input stream
   Token curr();              // get the current token in the input stream
   void pop();                // remove the current token from the stream
   bool empty();              // are there any more tokens?
private:
   std::queue<Token> data;    // tokens found so far
   std::istream& in;          // input stream to tokenize
   int curr_line;             // current line number
};

#endif
