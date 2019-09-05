/**
   @file parser.h
   @author Lee Wittenberg
   @date 2017-06-01
   @version 2.0

   Interface for Parser class to parse the Ledgard language.
 */
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "lexer.h"

class Parser
{
public:
   Parser(Lexer& ll) : lexer(ll) {}  // construct a parser from a given lexer
   bool parse();                     // parse the lexical tokens

   // determine if the current token is of a particular type
   bool have(Token_Type t) { return lexer.curr().tok == t; }

   // look at the current lexical token
   Token curr_token() { return lexer.curr(); }

   // move on to the next lexical token
   void next_token() { lexer.pop(); }

   // generate an error if the current token is not as expected
   void mustbe(Token_Type t)
   {
      if (lexer.curr().tok != t) {
         std::cerr << "Unexpected token: \"" << lexer.curr().repn 
                   << "\" found where " + tok_expected[t] << " was expected"
                   << " (line " << lexer.curr().line_number << ")"
                   << std::endl;
         std::exit(1);
      }
   }
private:
   Lexer lexer;
   static std::string tok_expected[];   // names for "expected" tokens
};

#endif
