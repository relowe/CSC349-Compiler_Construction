/**
   @file codegen.cpp
   @author put your name here
   @date set & update date as necessary
   @version set & update version number as necessary

   Code generation routines, generating 32-bit x86 assembly code,
   from a parse tree.  The parse tree is assumed to be error-free.
   To avoid register allocation issues, all code is stack-based.
   Library routines "read_bool," "read_dec," "print_bool," "print_dec,"
   and "print_newline" are assumed to be provided at link time.
   The former two return the value read in EAX, and the next two
   expect the value to be printed in EAX.  "print_newline" requires
   no parameters.
 */
#include <iostream>
#include <sstream>
#include <string>
#include "parse-tree.h"
#include "symtab.h"

using namespace std;

/**
   Generate an unused label for generated code.  A static counter
   is incremented for each label created to ensure that all labels
   are unique.

   @return  a unique string value of the form "labeln", where n is
            a positive integer
 */
string new_label()
{
   static int count = 0;  // counter to keep track of labels generated
   ostringstream result;
   result << "label" << ++count;
   return result.str();
}

/**
   Generate code for a Ledgard program.  Generate the "prologue"
   for the data (".bss") section, then the code for the declarations,
   then the "prologue" for the instructions (.text) section, then
   the code for the statements in the program, and finally, the code
   to return control to the operating system once the program ends.

   @param out  the output stream for the generated code
 */
void Prog_Node::generate(ostream& out)
{
   // data prologue
#ifdef __MACH__
   out << "\t.data"       << endl;
#else
   out << ".section .bss" << endl;
#endif

   // generate code for declarations
   for (list<Decl_Node*>::iterator p = decls.begin(); p != decls.end(); p++)
   {
      (*p)->generate(out);
   }
   out << endl;

   // instructions prologue
#ifdef __MACH__
   out << "\t.text"        << endl;
#else
   out << ".section .text" << endl;
#endif
   out << ".globl  _start" << endl;
   out << "_start:"        << endl;

   // generate code for statements
   for (list<Stmt_Node*>::iterator p = stmts.begin(); p != stmts.end(); p++)
   {
      (*p)->generate(out);
   }
   out << endl;

   // return to OS
#ifdef __MACH__
   out << "\tpushl   $0"        << endl;
   out << "\tmovl    $1,%eax"   << endl;
   out << "\tpushl   %eax"      << endl;
#else
   out << "\txorl    %ebx,%ebx" << endl;
   out << "\tmovl    $1,%eax"   << endl;
#endif
   out << "\tint     $0x80"     << endl;
}

/**
   Generate code for a declaration.  Each identifer in the declaration
   is declared with a ".lcomm" declaration allocating enough space for
   the declared variable.

   @param out  the output stream for the generated code
 */
void Decl_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for a '<' operation.  Generate code for each of
   the operands, then to compare the two top values on the stack and
   push the result (either 1 or 0 -- "true" or "false", respectively)
   on the stack.

   @param out  the output stream for the generated code
 */
void LT_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for a '<=' operation.  Generate code for each of
   the operands, then to compare the two top values on the stack and
   push the result (either 1 or 0 -- "true" or "false", respectively)
   on the stack.

   @param out  the output stream for the generated code
 */
void LE_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for a '==' operation.  Generate code for each of
   the operands, then to compare the two top values on the stack and
   push the result (either 1 or 0 -- "true" or "false", respectively)
   on the stack.

   @param out  the output stream for the generated code
 */
void EQ_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for a '!=' operation.  Generate code for each of
   the operands, then to compare the two top values on the stack and
   push the result (either 1 or 0 -- "true" or "false", respectively)
   on the stack.

   @param out  the output stream for the generated code
 */
void NE_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for a '>' operation.  Generate code for each of
   the operands, then to compare the two top values on the stack and
   push the result (either 1 or 0 -- "true" or "false", respectively)
   on the stack.

   @param out  the output stream for the generated code
 */
void GE_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for a '>=' operation.  Generate code for each of
   the operands, then to compare the two top values on the stack and
   push the result (either 1 or 0 -- "true" or "false", respectively)
   on the stack.

   @param out  the output stream for the generated code
 */
void GT_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for a '+' operation.  Generate code for each
   of the operands, then to add the two top values on the stack
   and push the result on the stack.

   @param out  the output stream for the generated code
 */
void Plus_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for for a '-' operation.  Generate code for each
   of the operands, then to subtract the two top values on the stack
   and push the result on the stack.

   @param out  the output stream for the generated code
 */
void Minus_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for for a '*' operation.  Generate code for each
   of the operands, then to multiply the two top values on the stack
   and push the result on the stack.

   @param out  the output stream for the generated code
 */
void Times_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for for a '/' operation.  Generate code for each
   of the operands, then to divide the two top values on the stack
   and push the result on the stack.

   @param out  the output stream for the generated code
 */
void Div_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for for an 'and' operation.  Generate code for
   each of the operands, then to "logical and" the two top values on
   the stack and push the result on the stack.

   @param out  the output stream for the generated code
 */
void And_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for for an 'or' operation.  Generate code for
   each of the operands, then to "logical or" the two top values on
   the stack and push the result on the stack.

   @param out  the output stream for the generated code
 */
void Or_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for for a 'not' operation.  Generate code for
   the operand, then to "logical not" the top value on the stack and
   push the result on the stack.

   @param out  the output stream for the generated code
 */
void Not_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for an integer literal.  Generate code to push
   its value on the stack.

   @param out  the output stream for the generated code
 */
void Int_Literal_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for an boolean literal.  Generate code to push
   its value (1 for "true", 0 for "false") on the stack.

   @param out  the output stream for the generated code
 */
void Bool_Literal_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for a variable.  Generate code for the variable's
   address, then to push the value at that address on the stack.

   @param out  the output stream for the generated code
 */
void Vble_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for variable's address.  Use ESI to calculate
   the displacement from the base address.  For each subscript,
   generate the code for the index and to check it for a range
   error.  Then to multiply the index (less the array's lower bound)
   by the size of the base type (to get the displacement
   represented by the index) and add this to ESI.  Once the final
   displacement has been calculated, generate the code to push
   the address of the variable plus the displacement in ESI onto
   the stack.

   @param out  the output stream for the generated code
 */
void Vble_Node::gen_addr(ostream& out)
{
   // put your code here
}

/**
   Generate code for an assignment statement.  Generate code for
   the variable's address, then for the expression, and finally to
   move the value on top of the stack to the variable's address.

   @param out  the output stream for the generated code
 */
void Assign_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for an exchange statement.  Generate code for
   the left variable's address, then for the right variable's address,
   and finally to move the value at the left variable's address to the
   right variable's address and vice versa.

   @param out  the output stream for the generated code
 */
void Xchg_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for an if statement.  Generate code for
   the condition, and to jump to the first label if the
   condition is false.  Then generate code for the statements in
   the then-part, a jump to the second label, the first label,
   the statements in the else-part, and finally, the second label.

   @param out  the output stream for the generated code
 */
void If_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for a while statement.  Generate code for
   the first label, the condition, and to jump to the second label
   if the condition is false.  Then generate code for the statements in
   the body, a jump to the first label, and finally, the second label.

   @param out  the output stream for the generated code
 */
void While_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for an input statement.  For each variable
   specified, generate the address of that variable, a call to
   "read_bool" or "read_dec" (depending on the variable's type),
   and code to store the value read at the variable's address.

   @param out  the output stream for the generated code
 */
void Input_Node::generate(ostream& out)
{
   // put your code here
}

/**
   Generate code for an output statement.  For each variable
   specified, generate code for the value of that variable, then
   to pass that value to "print_bool" or "print_dec", depending
   on the variable's type.  Finally, generate a call to
   "print_newline".

   @param out  the output stream for the generated code
 */
void Output_Node::generate(ostream& out)
{
   // put your code here
}
