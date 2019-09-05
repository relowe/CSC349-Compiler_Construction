/**
   @file typecheck.cpp
   @author put your name here
   @date set & update date as necessary
   @version set & update version number as necessary

   Type checking routines.
 */
#include <iostream>
#include <set>
#include "parse-tree.h"
#include "symtab.h"
#include "typecheck.h"

using namespace std;

set<int> reported;   // lines with already reported errors

/*
   Determine if an Prog_Node is valid with regard to matching types.
   The types must match in all the statements in the body.
   Report any errors found.

   @return  true iff the program is valid wrt types
 */
bool Prog_Node::match_types()
{
   bool result = true;
   for (auto p = stmts.begin(); p != stmts.end(); p++)
   {
      result = (*p)->match_types() and result;
   }
   return result;
}

/*
   Determine if an While_Node is valid with regard to matching types.
   The condition must be a valid boolean expression and the types must
   match in all the statements in the body.
   Report any errors found.

   @return  true iff the while statement is valid wrt types
 */
bool While_Node::match_types()
{
   Type_Node* t = condition->get_type();
   bool result = (t == Type_Node::BOOLEAN);
   if (not result) {
      if (reported.count(condition->get_line()) == 0) {
         report_type_error(condition->get_line());
         reported.insert(condition->get_line());
      }
   } else { result = condition->match_types(); }
   for (auto p = body.begin(); p != body.end(); p++) {
      result = (*p)->match_types() and result;
   }
   return result;
}

/**
   Determine the type of a Plus_Node.  The '+' operator always returns
   an integer value.

   @return  integer
 */
Type_Node* Plus_Node::get_type()
{
   return Type_Node::INTEGER;
}

/**
   Determine if two types are compatible.
   They are compatible if they are the same or one of them is VOID
   (i.e., an error was found at a lower level and should not be repeated)

   @param t1  first type to check

   @param t2  second type to check
   @return  true iff t1 and t2 are compatible
 */
bool compatible(Type_Node* t1, Type_Node* t2)
{
   return (t1 == t2 or t1 == Type_Node::VOID or t2 == Type_Node::VOID);
}

/**
   Determine if two types match for the purpose of an integer
   binary operation, and report an error if they don't.  The
   types match if they are both integer or if one is void (which
   means that a type match check failed on a sub-expression).

   @param line  the source line on which operation occurs
   @param t1  the first type to check
   @param t2  the second type to check
   @return  true iff t1 and t2 match
 */
bool integer_binop_match(int line, Type_Node* t1, Type_Node* t2)
{
   if (not compatible(t1, Type_Node::INTEGER)) {
      if (reported.count(line) == 0) {
         report_type_error(line);
         reported.insert(line);
      }
   }
   if (not compatible(t2, Type_Node::INTEGER)) {
      if (reported.count(line) == 0) {
         report_type_error(line);
         reported.insert(line);
      }
   }
   return compatible(t1, Type_Node::INTEGER)
         and compatible(t2, Type_Node::INTEGER);
}

/**
   Determine if the operands of a Plus_Node match:  are both
   integer and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both integer and
            the types of any sub-expressions match
 */
bool Plus_Node::match_types()
{
   bool result = left->match_types();
   result = right->match_types() and result;
   result = integer_binop_match(line_number, 
               left->get_type(), right->get_type()) and result;
   return result;
}

/**
   Determine if the operands of an LT_Node match:  are both
   integer and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both integer and
            the types of any sub-expressions match
 */
bool LT_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a LT_Node.  The '<' operator always returns
   a boolean value.

   @return  boolean
 */
Type_Node* LT_Node::get_type()
{
   // put your code here
}

/**
   Determine if the operands of an LE_Node match:  are both
   integer and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both integer and
            the types of any sub-expressions match
 */
bool LE_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a LE_Node.  The '<=' operator always returns
   a boolean value.

   @return  boolean
 */
Type_Node* LE_Node::get_type()
{
   // put your code here
}

/**
   Determine if the operands of an EQ_Node match:  are both
   the same and both simple types, and the types of all
   sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both simple and the
            same, and the types of any sub-expressions match
 */
bool EQ_Node::match_types()
{
   // put your code here
}

/**
   Determine if the operands of an NE_Node match:  are both
   the same and both simple types, and the types of all
   sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both simple and the
            same, and the types of any sub-expressions match
 */
bool NE_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a EQ_Node.  The '==' operator always returns
   a boolean value.

   @return  boolean
 */
Type_Node* EQ_Node::get_type()
{
   // put your code here
}

/**
   Determine the type of a NE_Node.  The '!=' operator always returns
   a boolean value.

   @return  boolean
 */
Type_Node* NE_Node::get_type()
{
   // put your code here
}

/**
   Determine if the operands of a GE_Node match:  are both
   integer and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both integer and
            the types of any sub-expressions match
 */
bool GE_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a GE_Node.  The '>=' operator always returns
   a boolean value.

   @return  boolean
 */
Type_Node* GE_Node::get_type()
{
   // put your code here
}

/**
   Determine if the operands of a GT_Node match:  are both
   integer and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both integer and
            the types of any sub-expressions match
 */
bool GT_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a GT_Node.  The '>' operator always returns
   a boolean value.

   @return  boolean
 */
Type_Node* GT_Node::get_type()
{
   // put your code here
}

/**
   Determine if the operands of a Minus_Node match:  are both
   integer and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both integer and
            the types of any sub-expressions match
 */
bool Minus_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a Minus_Node.  The '-' operator always returns
   an integer value.

   @return  integer
 */
Type_Node* Minus_Node::get_type()
{
   // put your code here
}

/**
   Determine if the operands of a Times_Node match:  are both
   integer and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both integer and
            the types of any sub-expressions match
 */
bool Times_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a Times_Node.  The '*' operator always returns
   an integer value.

   @return  integer
 */
Type_Node* Times_Node::get_type()
{
   // put your code here
}

/**
   Determine if the operands of a Div_Node match:  are both
   integer and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both integer and
            the types of any sub-expressions match
 */
bool Div_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a Div_Node.  The '/' operator always returns
   an integer value.

   @return  integer
 */
Type_Node* Div_Node::get_type()
{
   // put your code here
}

/**
   Determine if the operands of an And_Node match:  are both
   boolean and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both boolean and
            the types of any sub-expressions match
 */
bool And_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a And_Node.  The 'and' operator always returns
   a boolean value.

   @return  boolean
 */
Type_Node* And_Node::get_type()
{
   // put your code here
}

/**
   Determine if the operands of an Or_Node match:  are both
   boolean and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both boolean and
            the types of any sub-expressions match
 */
bool Or_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a Or_Node.  The 'or' operator always returns
   a boolean value.

   @return  boolean
 */
Type_Node* Or_Node::get_type()
{
   // put your code here
}

/**
   Determine if the operand of a NotNode match:  is
   boolean and the types of any sub-expressions match.
   Report any errors found.

   @return  true iff the the two operands are both boolean and
            the types of any sub-expressions match
 */
bool Not_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a Not_Node.  The 'not' operator always returns
   a boolean value.

   @return  boolean
 */
Type_Node* Not_Node::get_type()
{
   // put your code here
}

/**
   Determine if a Vble_Node is valid with regard to types.  The
   identifier must have been declared, the subscripts must all be
   integer expressions, and the number of subscripts must match
   the number of subscripts declared (if any).
   Report any errors found.

   @return  true iff the identifier has been declared, the subscripts
            are all valid integer expressions, and the number of
            subscripts matches the number of subscripts declared
 */
bool Vble_Node::match_types()
{
   // put your code here
}

/**
   Determine the type of a Vble_Node.  The symbol table must be
   searched for the identifier.  For each subscript, the chain of base
   types in the symbol table must be traversed to determine the type of
   the variable.  If there are too many subscripts for the variable's
   declared type, it is considered to be void.

   @return  the type of the specified variable
 */
Type_Node* Vble_Node::get_type()
{
   // put your code here
}

/*
   Determine if an Assign_Node is valid with regard to matching types.
   The left-hand side must be a variable of a simple type (boolean or 
   integer) and the right-hand side must be an expression of the same type.
   Report any errors found.

   @return  true iff the assignment statement is valid wrt types
 */
bool Assign_Node::match_types()
{
   // put your code here
}

/*
   Determine if an Xchg_Node is valid with regard to matching types.
   The left-hand side must be a variable of a simple type (boolean or 
   integer) and the right-hand side must be a variable of the same type.
   Report any errors found.

   @return  true iff the assignment statement is valid wrt types
 */
bool Xchg_Node::match_types()
{
   // put your code here
}

/*
   Determine if an If_Node is valid with regard to matching types.
   The condition must be a valid boolean expression and the types must
   match in all the statements in both the then and else parts.
   Report any errors found.

   @return  true iff the if statement is valid wrt types
 */
bool If_Node::match_types()
{
   // put your code here
}

/*
   Determine if an IO_Node is valid with regard to matching types.
   All the variables in the statement must be valid with regard to types.
   Report any errors found.

   @return  true iff the I/O statement is valid wrt types
 */
bool IO_Node::match_types()
{
   // put your code here
}
