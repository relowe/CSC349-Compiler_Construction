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

bool LT_Node::match_types()
{
   throw runtime_error("LT_Node::match_types() is not yet implemented");
}

Type_Node* LT_Node::get_type()
{
   throw runtime_error("LT_Node::get_type() is not yet implemented");
}

void LE_Node::generate(ostream& out)
{
   throw runtime_error("LE_Node::generate() is not yet implemented");
}

bool LE_Node::match_types()
{
   throw runtime_error("LE_Node::match_types() is not yet implemented");
}

Type_Node* LE_Node::get_type()
{
   throw runtime_error("LE_Node::get_type() is not yet implemented");
}

void EQ_Node::generate(ostream& out)
{
   throw runtime_error("EQ_Node::generate() is not yet implemented");
}

bool EQ_Node::match_types()
{
   throw runtime_error("EQ_Node::match_types() is not yet implemented");
}

Type_Node* EQ_Node::get_type()
{
   throw runtime_error("EQ_Node::get_type() is not yet implemented");
}

void NE_Node::generate(ostream& out)
{
   throw runtime_error("NE_Node::generate() is not yet implemented");
}

bool NE_Node::match_types()
{
   throw runtime_error("NE_Node::match_types() is not yet implemented");
}

Type_Node* NE_Node::get_type()
{
   throw runtime_error("NE_Node::get_type() is not yet implemented");
}

void GE_Node::generate(ostream& out)
{
   throw runtime_error("GE_Node::generate() is not yet implemented");
}

bool GE_Node::match_types()
{
   throw runtime_error("GE_Node::match_types() is not yet implemented");
}

Type_Node* GE_Node::get_type()
{
   throw runtime_error("GE_Node::get_type() is not yet implemented");
}

void GT_Node::generate(ostream& out)
{
   throw runtime_error("GT_Node::generate() is not yet implemented");
}

bool GT_Node::match_types()
{
   throw runtime_error("GT_Node::match_types() is not yet implemented");
}

Type_Node* GT_Node::get_type()
{
   throw runtime_error("GT_Node::get_type() is not yet implemented");
}

void Plus_Node::generate(ostream& out)
{
   throw runtime_error("Plus_Node::generate() is not yet implemented");
}

bool Plus_Node::match_types()
{
   throw runtime_error("Plus_Node::match_types() is not yet implemented");
}

Type_Node* Plus_Node::get_type()
{
   throw runtime_error("Plus_Node::get_type() is not yet implemented");
}

void Minus_Node::generate(ostream& out)
{
   throw runtime_error("Minus_Node::generate() is not yet implemented");
}

bool Minus_Node::match_types()
{
   throw runtime_error("Minus_Node::match_types() is not yet implemented");
}

Type_Node* Minus_Node::get_type()
{
   throw runtime_error("Minus_Node::get_type() is not yet implemented");
}

void Times_Node::generate(ostream& out)
{
   throw runtime_error("Times_Node::generate() is not yet implemented");
}

bool Times_Node::match_types()
{
   throw runtime_error("Times_Node::match_types() is not yet implemented");
}

Type_Node* Times_Node::get_type()
{
   throw runtime_error("Times_Node::get_type() is not yet implemented");
}

void Div_Node::generate(ostream& out)
{
   throw runtime_error("Div_Node::generate() is not yet implemented");
}

bool Div_Node::match_types()
{
   throw runtime_error("Div_Node::match_types() is not yet implemented");
}

Type_Node* Div_Node::get_type()
{
   throw runtime_error("Div_Node::get_type() is not yet implemented");
}

void And_Node::generate(ostream& out)
{
   throw runtime_error("And_Node::generate() is not yet implemented");
}

bool And_Node::match_types()
{
   throw runtime_error("And_Node::match_types() is not yet implemented");
}

Type_Node* And_Node::get_type()
{
   throw runtime_error("And_Node::get_type() is not yet implemented");
}

void Or_Node::generate(ostream& out)
{
   throw runtime_error("Or_Node::generate() is not yet implemented");
}

bool Or_Node::match_types()
{
   throw runtime_error("Or_Node::match_types() is not yet implemented");
}

Type_Node* Or_Node::get_type()
{
   throw runtime_error("Or_Node::get_type() is not yet implemented");
}

void Not_Node::generate(ostream& out)
{
   throw runtime_error("Not_Node::generate() is not yet implemented");
}

bool Not_Node::match_types()
{
   throw runtime_error("Not_Node::match_types() is not yet implemented");
}

Type_Node* Not_Node::get_type()
{
   throw runtime_error("Not_Node::get_type() is not yet implemented");
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

bool Vble_Node::match_types()
{
   throw runtime_error("Vble_Node::match_types() is not yet implemented");
}

Type_Node* Vble_Node::get_type()
{
   throw runtime_error("Vble_Node::get_type() is not yet implemented");
}

void Assign_Node::generate(ostream& out)
{
   throw runtime_error("Assign_Node::generate() is not yet implemented");
}

bool Assign_Node::match_types()
{
   throw runtime_error("Assign_Node::match_types() is not yet implemented");
}

void Xchg_Node::generate(ostream& out)
{
   throw runtime_error("Xchg_Node::generate() is not yet implemented");
}

bool Xchg_Node::match_types()
{
   throw runtime_error("Xchg_Node::match_types() is not yet implemented");
}

void If_Node::generate(ostream& out)
{
   throw runtime_error("If_Node::generate() is not yet implemented");
}

bool If_Node::match_types()
{
   throw runtime_error("If_Node::match_types() is not yet implemented");
}

void While_Node::generate(ostream& out)
{
   throw runtime_error("If_Node::generate() is not yet implemented");
}

bool While_Node::match_types()
{
   throw runtime_error("If_Node::match_types() is not yet implemented");
}

void Input_Node::generate(ostream& out)
{
   throw runtime_error("Input_Node::generate() is not yet implemented");
}

void Output_Node::generate(ostream& out)
{
   throw runtime_error("Output_Node::generate() is not yet implemented");
}

bool IO_Node::match_types()
{
   throw runtime_error("Input_Node::match_types() is not yet implemented");
}

void Prog_Node::generate(ostream& out)
{
   throw runtime_error("Prog_Node::generate() is not yet implemented");
}

bool Prog_Node::match_types()
{
   throw runtime_error("Prog_Node::match_types() is not yet implemented");
}

