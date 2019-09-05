/**
   @file parser.cpp
   @author put your name here
   @date set & update date as necessary
   @version set & update version number as necessary

   Implementation of Parser class, building a parse tree.
*/
#include <string>
#include <cstdlib>
#include "lexer.h"
#include "parser.h"
#include "parse-tree.h"

using namespace std;

// pointers for type matching (to avoid excess heap use)
// [do not modify these next three lines]
Type_Node* Type_Node::VOID = new Void_Type_Node();
Type_Node* Type_Node::INTEGER = new Int_Type_Node();
Type_Node* Type_Node::BOOLEAN = new Bool_Type_Node();

// values for boolean literals
// [do not modify these next two lines]
Expr_Node* Bool_Literal_Node::TRUE = new Bool_Literal_Node(true);
Expr_Node* Bool_Literal_Node::FALSE = new Bool_Literal_Node(false);

// forward declarations for mutual recursion
Stmt_Node* parse_stmt(Parser& p);

/**
   Use a given parser to parse a Ledgard statement

   @parm p  the parser object to use
   @return  the parse tree for the parsed statement
 */
Stmt_Node* parse_stmt(Parser& p)
{
   // put your code here
}

/**
   Use a given parser to parse a Ledgard declaration

   @parm p  the parser object to use
   @return  the parse tree for the parsed declaration
 */
Decl_Node* parse_decl(Parser& p)
{
   // put your code here
}

/**
   Use a given parser to parse a Ledgard program

   @parm p  the parser object to use
   @return  the parse tree for the parsed program
 */
Prog_Node* parse_program(Parser& p)
{
   p.mustbe(PROG_TOK); p.next_token();
   Prog_Node* result = new Prog_Node();
   do {
      result->add_decl(parse_decl(p));
   } while (not p.have(BEGIN_TOK));
   p.mustbe(BEGIN_TOK); p.next_token();
   do {
      result->add_stmt(parse_stmt(p));
   } while (not p.have(END_TOK));
   p.next_token();
   p.mustbe(SEMI_TOK); p.next_token();
   return result;
}

/**
   Use this parser to parse a Ledgard program

   @return  the parse tree for the parsed program
 */
Parse_Tree* Parser::parse()
{
   Parse_Tree* result = parse_program(*this);
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
