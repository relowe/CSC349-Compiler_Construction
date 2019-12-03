//Implementation of symbol table functions for looplang
//Design based on the ledgard symbol table by Lee Wittenberg
//Adapted for looplang by Robert Lowe
#include "parse_tree.h"
#include "symtab.h"

using namespace std;


Symbol_Table symtab;

void Program_Node::build_symtab()
{
    slist->build_symtab();
}


void Program_Node::check_symbols()
{
    slist->check_symbols();
}


void Statement_List_Node::build_symtab()
{
    for(auto itr = list.begin(); itr != list.end(); itr++) {
        (*itr)->build_symtab();
    }
}


void Statement_List_Node::check_symbols()
{
    for(auto itr = list.begin(); itr != list.end(); itr++) {
        (*itr)->check_symbols();
    }
}


void Assignment_Stmnt_Node::build_symtab()
{
    identifier->build_symtab();
}


void Assignment_Stmnt_Node::check_symbols()
{
    expr->check_symbols();
}


void Loop_Stmnt_Node::build_symtab()
{
    slist->build_symtab();
}

void Loop_Stmnt_Node::check_symbols()
{
    cond->check_symbols();
    slist->check_symbols();
}


void Expression_Node::check_symbols()
{
    left->check_symbols();
    if(right != nullptr) {
        right->check_symbols();
    }
}


void Condition_Node::check_symbols()
{
    left->check_symbols();
    right->check_symbols();
}


void Operand_Node::build_symtab()
{
    Token t = get_token();

    //insert this if it is an identifier
    if(t.type == IDENTIFIER_TOK) {
        symtab.tab.insert(t.repn);
    }
}

void Operand_Node::check_symbols()
{
    Token t = get_token();

    //insert undefined identifiers
    if(t.type == IDENTIFIER_TOK and symtab.tab.count(t.repn) == 0) {
        symtab.undef.insert(t.repn);
    }
}
