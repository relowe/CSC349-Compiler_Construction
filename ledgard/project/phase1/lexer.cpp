/**
   @file lexer.cpp
   @author put your name here
   @date set & update date as necessary
   @version set & update version number as necessary

   Implementation of Lexer class.
 */
#include <iostream>
#include "lexer.h"

using namespace std;

/**
   Lexer constructor.

   @param f  file to read tokens from
 */
Lexer::Lexer(istream& f): in(f), curr_line(0)
{
   // put your code here
}

const Token ENDFILE = { EOF_TOK, "<End-of-file>" };

/**
   Report the current token being examined.  Read (and tokenize)
   from input stream if necessary).

   @return  the current source token (ENDFILE if no tokens left)
 */
Token Lexer::curr()
{
   // put your code here
}

/**
   Remove the current token from the input stream.
 */
void Lexer::pop() { if (curr().tok != EOF_TOK) { data.pop(); } }

/**
   Determine whether or not there are any more tokens in the source
   file.

   @return  true iff there are no more tokens to process
 */
bool Lexer::empty() { return curr().tok == EOF_TOK; }
