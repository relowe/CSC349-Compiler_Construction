#include <iostream>
#include <vector>
#include "lexer.h"
#include "parse_tree.h"

/////////////////////////
// Program Node
/////////////////////////
void Program_Node::print(int level)
{
    std::cout << std::setw(level) << "" << "Program" << std::endl;
    slist->print(level+1);
}


Program_Node::~Program_Node() 
{ 
    delete slist; 
}



/////////////////////////
// Statement List Node 
/////////////////////////
void Statement_List_Node::append(Statement_Node *statement) 
{
    list.push_back(statement);
}


void Statement_List_Node::print(int level) 
{
    for(auto itr = list.begin(); itr != list.end(); itr++) {
        (*itr)->print(level+1);
    }
}

Statement_List_Node::~Statement_List_Node() 
{
    for(auto itr = list.begin(); itr != list.end(); itr++) {
        delete *itr;
    }
}


/////////////////////////
// Statement Node 
/////////////////////////


/////////////////////////
// Assignment Stmnt Node
/////////////////////////
void Assignment_Stmnt_Node::print(int level) 
{
    identifier->print(level+1);
    std::cout << std::setw(level) << "" << "=" << std::endl;
    expr->print(level+1);
}

Assignment_Stmnt_Node::~Assignment_Stmnt_Node() 
{ 
    delete expr; 
    delete identifier;
}


/////////////////////////
// Loop Stmnt Node
/////////////////////////
void Loop_Stmnt_Node::print(int level) 
{
    std::cout << std::setw(level) << "" << "while" << std::endl;
    cond->print(level+1);
    slist->print(level+1);
}

Loop_Stmnt_Node::~Loop_Stmnt_Node() 
{ 
    delete cond; 
    delete slist; 
}


/////////////////////////
// Print Stmnt Node
/////////////////////////
void Print_Stmnt_Node::print(int level) 
{
    std::cout << std::setw(level) << "" << "print" << std::endl;
    expr->print(level+1);
}

Print_Stmnt_Node::~Print_Stmnt_Node() 
{ 
    delete expr; 
}


/////////////////////////
// Expression Node
/////////////////////////
void Expression_Node::print(int level)
{
    //print operand binop expression form
    if(binop != nullptr) {
        left->print(level+1);
        binop->print(level);
        right->print(level+1);
    } else {
        //single operand form
        left->print(level);
    }
}

Expression_Node::~Expression_Node()
{
    delete left;
    if(binop != nullptr) {
        delete binop;
        delete right;
    }
}


/////////////////////////
// Condition Node
/////////////////////////
void Condition_Node::print(int level) 
{
    left->print(level+1);
    comp->print(level);
    right->print(level+1);
}

Condition_Node::~Condition_Node()
{
    delete left;
    delete comp;
    delete right;
}
