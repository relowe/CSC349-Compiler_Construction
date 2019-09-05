/**
   @file symtab.cpp
   @author put your name here
   @date set and update date as necessary
   @version set and update version number as necessary

   Symbol table building and checking routines
 */
#include "parse-tree.h"
#include "symtab.h"

using namespace std;

Symbol_Table symtab;    // global symbol table

/**
   Add identifiers to a symbol table for this program; add any
   defined more than once to a set of such identifiers found so far.
 */
void Prog_Node::build_symtab()
{
   for (auto p = decls.begin(); p != decls.end(); p++)
   {
      (*p)->build_symtab();
   }
}

/**
   Check a Prog_Node for undefined identifiers; add any found
   to a set of such identifiers found so far.
 */
void Prog_Node::check_symbols()
{
   for (auto p = stmts.begin(); p != stmts.end(); p++)
   {
      (*p)->check_symbols();
   }
}

/**
   Check a Binop_Node for undefined identifiers; add any found
   to a set of such identifiers found so far.
 */
void Binop_Node::check_symbols()
{
   // put your code here
}

/**
   Check a Unop_Node for undefined identifiers; add any found
   to a set of such identifiers found so far.
 */
void Unop_Node::check_symbols()
{
   // put your code here
}

/**
   Add identifiers to a symbol table for this declaration; add any
   declared more than once to a set of such identifiers found so far.
 */
void Decl_Node::build_symtab()
{
   // put your code here
}

/**
   Check a Vble_Node for undefined identifiers; add any found
   to a set of such identifiers found so far.
 */
void Vble_Node::check_symbols()
{
   // put your code here
}

/**
   Check an Assign_Node for undefined identifiers; add any found
   to a set of such identifiers found so far.
 */
void Assign_Node::check_symbols()
{
   // put your code here
}

/**
   Check an Xchg_Node for undefined identifiers; add any found
   to a set of such identifiers found so far.
 */
void Xchg_Node::check_symbols()
{
   // put your code here
}

/**
   Check a If_Node for undefined identifiers; add any found
   to a set of such identifiers found so far.
 */
void If_Node::check_symbols()
{
   // put your code here
}

/**
   Check a While_Node for undefined identifiers; add any found
   to a set of such identifiers found so far.
 */
void While_Node::check_symbols()
{
   // put your code here
}

/**
   Check a IO_Node for undefined identifiers; add any found
   to a set of such identifiers found so far.
 */
void IO_Node::check_symbols()
{
   // put your code here
}
