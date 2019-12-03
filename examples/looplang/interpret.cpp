// interpreter for looplang
#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "parse_tree.h"

using namespace std;

map<string, int> variable;  //my variables

void Program_Node::exec(void *result)
{
    slist->exec(result);
}


void Statement_List_Node::exec(void *result)
{
    int r;
    for(auto itr = list.begin(); itr != list.end(); itr++) {
        (*itr)->exec(&r);
    }
}


void Assignment_Stmnt_Node::exec(void *result)
{
    string name;
    int val;

    //get the variable name
    name = identifier->get_token().repn;

    //get the value
    expr->exec(&val);

    //do the assignment
    variable[name] = val;
}


void Loop_Stmnt_Node::exec(void *result) 
{
    bool go;

    do {
        cond->exec(&go);
        if(go) {
            slist->exec(result);
        }
    } while(go);
}


void Print_Stmnt_Node::exec(void *result)
{
    int val;

    expr->exec(&val);
    cout << setw(12) << val << endl;
}


void Expression_Node::exec(void *result)
{
    int left_result;
    int right_result;
    int *r = (int*) result;

    //get the left result
    left->exec(&left_result);

    //we may be done
    if(binop == nullptr) {
        *r = left_result;
        return;
    }

    //get the right hand side
    right->exec(&right_result);

    //apply the operator
    switch(binop->get_token().type)
    {
    case PLUS_TOK:
        *r = left_result + right_result;
        break;
    case MINUS_TOK:
        *r = left_result - right_result;
    }
}


void Condition_Node::exec(void *result)
{
    int left_result;
    int right_result;
    bool *r = (bool*) result;

    //get the left and right sides
    left->exec(&left_result);
    right->exec(&right_result);

    switch(comp->get_token().type)
    {
    case LESS_TOK:
        *r = left_result < right_result;
        break;
    case LESS_EQUAL_TOK:
        *r = left_result <= right_result;
        break;
    case GREATER_TOK:
        *r = left_result > right_result;
        break;
    case GREATER_EQUAL_TOK:
        *r = left_result >= right_result;
        break;
    case EQUAL_TOK:
        *r = left_result == right_result;
        break;
    case NOT_EQUAL_TOK:
        *r = left_result != right_result;
        break;
    }
}   


void Operand_Node::exec(void *result)
{
    int *r = (int*) result;
    Token t = get_token();

    if(t.type == IDENTIFIER_TOK) {
        *r = variable[t.repn];
    } else {
        *r = atoi(t.repn.c_str());
    }
}
