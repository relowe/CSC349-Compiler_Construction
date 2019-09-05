/**
   @file parser.cpp
   @author put your name here
   @date set & update date as necessary
   @version set & update version number as necessary

   Implementation of Parser class.
*/
#include <string>
#include "lexer.h"
#include "parser.h"

using namespace std;

// forward declarations for mutual recursion
bool parse_stmt(Parser& p);

/**
   Use a given parser to parse a Ledgard statement

   @parm p  the parser object to use
   @return  true iff a statement was successfully parsed
 */
bool parse_stmt(Parser& p)
{
   // put your code here
}

/**
   Use a given parser to parse a Ledgard declaration

   @parm p  the parser object to use
   @return  true iff a declaration was successfully parsed
 */
bool parse_decl(Parser& p)
{
   // put your code here
}

/**
   Use a given parser to parse a Ledgard program

   @parm p  the parser object to use
   @return  true iff a program was successfully parsed
 */
bool parse_program(Parser& p)
{
   p.mustbe(PROG_TOK); p.next_token();
   bool result = parse_decl(p);
   while (not p.have(BEGIN_TOK)) {
      result = result and parse_decl(p);
   }
   p.mustbe(BEGIN_TOK); p.next_token();
   do {
      result = result and parse_stmt(p);
   } while (not p.have(END_TOK));
   p.next_token();
   p.mustbe(SEMI_TOK); p.next_token();
   return result;
}

/**
   Use this parser to parse a Ledgard program

   @return  true iff the program was successfully parsed
 */
bool Parser::parse()
{
   bool result = parse_program(*this);
   mustbe(EOF_TOK);
   return result;
}

// don't modify this table; it's necessary to make error messages come
// out right
string Parser::tok_expected[] = {   // names for "expected" tokens
   "\"unknown\"",       // INVALID_TOK
   "\"program\"",       // PROG_TOK
   "\"begin\"",         // BEGIN_TOK
   "\"end\"",           // END_TOK
   "\";\"",             // SEMI_TOK
   "\":\"",             // COLON_TOK
   "\",\"",             // COMMA_TOK
   "<type>",            // INTEGER_TOK
   "<type>",            // BOOLEAN_TOK
   "<type>",            // ARRAY_TOK 
   "\"[\"",             // LBRACK_TOK
   "\"]\"",             // RBRACK_TOK
   "\"of\"",            // OF_TOK
   "\"..\"",            // DOTDOT_TOK
   "\":= or :=:\"",     // ASSIGN_TOK
   "\":= or :=:\"",     // XCHG_TOK
   "<statement start>", // IF_TOK
   "\"then\"",          // THEN_TOK
   "\"else\"",          // ELSE_TOK
   "<statement>",       // WHILE_TOK
   "\"loop\"",          // LOOP_TOK
   "<statement>",       // INPUT_TOK
   "<statement>",       // OUTPUT_TOK
   "<expression>",      // LPAREN_TOK
   "\")\"",             // RPAREN_TOK
   "\"not\"",           // NOT_TOK
   "<boolean literal>", // TRUE_TOK
   "<boolean literal>", // FALSE_TOK
   "<operator>",        // LT_TOK
   "<operator>",        // LE_TOK
   "<operator>",        // EQ_TOK
   "<operator>",        // NE_TOK
   "<operator>",        // GE_TOK
   "<operator>",        // GT_TOK
   "<operator>",        // PLUS_TOK
   "<operator>",        // MINUS_TOK
   "<operator>",        // TIMES_TOK
   "<operator>",        // DIV_TOK
   "<operator>",        // AND_TOK
   "<operator>",        // OR_TOK
   "<identifier>",      // IDENT_TOK
   "<integer literal>", // INT_LITERAL_TOK
   "<end-of-file>",     // EOF_TOK
};
