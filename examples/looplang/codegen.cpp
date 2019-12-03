#include <iostream>
#include "parse_tree.h"
#include "symtab.h"

using namespace std;

//label counter for the code generator
static int label_num = 1;

void Program_Node::generate()
{

    cout << "\t\t.section .bss" << endl;

    //code for declarations
    for(auto itr = symtab.tab.begin(); itr != symtab.tab.end(); itr++) {
        cout << "\t.lcomm " << *itr << ", 4" << endl;
    }

    cout << "\t.section .text" << endl
         << "\t.globl _start" << endl
         << "\t_start:" << endl;

    //statement code
    slist->generate();

    //termination code
    cout << "\txorl %ebx,%ebx" << endl
         << "\tmovl $1,%eax" << endl
         << "\tint $0x80" << endl;
}


void Statement_List_Node::generate()
{
    for(auto itr = list.begin(); itr != list.end(); itr++) {
        (*itr)->generate();
    }
}


void Assignment_Stmnt_Node::generate()
{
    //< code for variable's address >
    string name = identifier->get_token().repn;
    cout << "\txorl %esi,%esi" << endl
         << "\tleal " << name << "(%esi),%eax" << endl
         << "\tpushl %eax" << endl;

    //< code for the expression >
    expr->generate();

    cout << "\tpopl %eax" << endl
         << "\tpopl %ebx" << endl
         << "\tmovl %eax,(%ebx)" << endl;
}


void Loop_Stmnt_Node::generate()
{
    int l1 = label_num++;
    int l2 = label_num++;

    //start the loop
    cout << "label"<< l1 << " :" << endl;

    //<code for the condition>
    cond->generate();

    cout << "\tpopl %eax" << endl
         << "\ttest %eax,%eax" << endl
         << "\tjz label" << l2 << endl;

    //<code for the body statements>
    slist->generate();

    cout << "\tjmp label" << l1 << endl;
    cout << "label" << l2 << " :" << endl;
}


void Print_Stmnt_Node::generate()
{
    //<code for the expression’s value>
    expr->generate();

    cout << "\tpopl %eax" << endl
         << "\tcall print_dec" << endl
         << "\tcall print_newline" << endl;
}

void Expression_Node::generate()
{
    //generate for the left operand 
    left->generate();

    if(binop == nullptr) {
        //done!
        return;
    }

    //generate for the right operand
    right->generate();

    //apply the operator
    string op;
    switch(binop->get_token().type)
    {
    case PLUS_TOK:
        op = "\taddl";
        break;
    case MINUS_TOK:
        op = "\tsubl";
    }

    cout << "\tpopl %ebx" << endl
         << "\tpopl %eax" << endl
         << op << "\t %ebx,%eax" << endl
         << "\tjo overflow" << endl
         << "\tpushl %eax" << endl;
}


void Condition_Node::generate()
{
    //<code for left operand>
    left->generate();

    //<code for right operand>
    right->generate();

    //get the right comparison (negation of)
    string op;
    switch(comp->get_token().type)
    {
    case LESS_TOK:
        op = "\tjge";
        break;
    case LESS_EQUAL_TOK:
        op = "\tjg";
        break;
    case GREATER_TOK:
        op = "\tjle";
        break;
    case GREATER_EQUAL_TOK:
        op = "\tjl";
        break;
    case EQUAL_TOK:
        op = "\tjne";
        break;
    case NOT_EQUAL_TOK:
        op = "\tje";
        break;
    }

    cout << "\tpopl %ebx" << endl
         << "\tpopl %eax" << endl
         << "\txorl %ecx,%ecx" << endl
         << "\tcmpl %ebx,%eax" << endl
         << op << "\t 1f" << endl
         << "\tincl %ecx" << endl
         << "1:\tpushl %ecx" << endl;
}


void Operand_Node::generate()
{
    Token t = get_token();

    if(t.type == IDENTIFIER_TOK) {
        //value of a variable
        cout << "\txorl %esi,%esi" << endl
             << "\tleal " << t.repn << "(%esi),%eax" << endl
             << "\tpushl %eax" << endl
             << "\tpopl %eax" << endl
             << "\tpushl (%eax)" << endl;
    } else {
        //value of a literal
        cout << "\tpushl $" << t.repn << endl;
    }
}
