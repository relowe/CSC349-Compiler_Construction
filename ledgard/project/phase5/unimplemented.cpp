/**
   @file unimplemented.cpp
   @author Lee Wittenberg
   @date 2017-06-04
   @version 2.0

   Unimplemented member functions for this stage of the project.
   All functions simply throw a runtime error.
 */
#include <stdexcept>
#include "parse-tree.h"

using namespace std;

void Decl_Node::generate(ostream& out)
{
   throw runtime_error("Decl_Node::generate() is not yet implemented");
}

void LT_Node::generate(ostream& out)
{
   throw runtime_error("LT_Node::generate() is not yet implemented");
}

void LE_Node::generate(ostream& out)
{
   throw runtime_error("LE_Node::generate() is not yet implemented");
}

void EQ_Node::generate(ostream& out)
{
   throw runtime_error("EQ_Node::generate() is not yet implemented");
}

void NE_Node::generate(ostream& out)
{
   throw runtime_error("NE_Node::generate() is not yet implemented");
}

void GE_Node::generate(ostream& out)
{
   throw runtime_error("GE_Node::generate() is not yet implemented");
}

void GT_Node::generate(ostream& out)
{
   throw runtime_error("GT_Node::generate() is not yet implemented");
}

void Plus_Node::generate(ostream& out)
{
   throw runtime_error("Plus_Node::generate() is not yet implemented");
}

void Minus_Node::generate(ostream& out)
{
   throw runtime_error("Minus_Node::generate() is not yet implemented");
}

void Times_Node::generate(ostream& out)
{
   throw runtime_error("Times_Node::generate() is not yet implemented");
}

void Div_Node::generate(ostream& out)
{
   throw runtime_error("Div_Node::generate() is not yet implemented");
}

void And_Node::generate(ostream& out)
{
   throw runtime_error("And_Node::generate() is not yet implemented");
}

void Or_Node::generate(ostream& out)
{
   throw runtime_error("Or_Node::generate() is not yet implemented");
}

void Not_Node::generate(ostream& out)
{
   throw runtime_error("Not_Node::generate() is not yet implemented");
}

void Int_Literal_Node::generate(ostream& out)
{
   throw runtime_error("Int_Literal_Node::generate() is not yet implemented");
}

void Bool_Literal_Node::generate(ostream& out)
{
   throw runtime_error("True_Node::generate() is not yet implemented");
}

void Vble_Node::generate(ostream& out)
{
   throw runtime_error("Vble_Node::generate() is not yet implemented");
}

void Vble_Node::gen_addr(ostream& out)
{
   throw runtime_error("Vble_Node::gen_addr() is not yet implemented");
}

void Assign_Node::generate(ostream& out)
{
   throw runtime_error("Assign_Node::generate() is not yet implemented");
}

void Xchg_Node::generate(ostream& out)
{
   throw runtime_error("Xchg_Node::generate() is not yet implemented");
}

void If_Node::generate(ostream& out)
{
   throw runtime_error("If_Node::generate() is not yet implemented");
}

void While_Node::generate(ostream& out)
{
   throw runtime_error("If_Node::generate() is not yet implemented");
}

void Input_Node::generate(ostream& out)
{
   throw runtime_error("Input_Node::generate() is not yet implemented");
}

void Output_Node::generate(ostream& out)
{
   throw runtime_error("Output_Node::generate() is not yet implemented");
}

void Prog_Node::generate(ostream& out)
{
   throw runtime_error("Prog_Node::generate() is not yet implemented");
}
