// This file contains data structures for parse trees for the loop
// language
#include <vector>
#include <string>
#include <iomanip>
#include "lexer.h"
#ifndef PARSE_TREE_H
#define PARSE_TREE_H


//forward declarations
class Parse_Node;
class Statement_List_Node;
class Statement_Node;
class Assignment_Stmnt_Node;
class Loop_Stmnt_Node;
class Print_Stmnt_Node;
class Expression_Node;
class Condition_Node;
class Operand_Node;
class Token_Node;

//The basic parser node abstract class
class Parse_Node 
{
public:
    virtual void print(int level)=0;
    virtual ~Parse_Node() { }
};


class Program_Node : public Parse_Node 
{
public:
    Program_Node(Statement_List_Node* slist) : slist(slist) { }

    virtual void print(int level);

    ~Program_Node();
private:
    Statement_List_Node *slist;
};


class Statement_List_Node : public Parse_Node
{
public:
    virtual void append(Statement_Node *statement);
    virtual void print(int level);

    ~Statement_List_Node();
private:
    std::vector<Statement_Node *> list;
};


class Statement_Node : public Parse_Node 
{
    //Just an article of polymorphism...
};


class Assignment_Stmnt_Node : public Statement_Node
{
public: 
    Assignment_Stmnt_Node(Operand_Node *identifier, Expression_Node *expr) : 
      identifier(identifier), expr(expr) { }

    virtual void print(int level);

    ~Assignment_Stmnt_Node();
private:
    Operand_Node *identifier;
    Expression_Node *expr;
};


class Loop_Stmnt_Node : public Statement_Node
{
public:
    Loop_Stmnt_Node(Condition_Node *cond, Statement_List_Node *slist)
     :  cond(cond), slist(slist) { }
    

    virtual void print(int level);
    ~Loop_Stmnt_Node();
private:
    Condition_Node *cond;
    Statement_List_Node *slist;
};


class Print_Stmnt_Node : public Statement_Node
{
public:
    Print_Stmnt_Node(Expression_Node *expr) : expr(expr) { }

    virtual void print(int level);

    ~Print_Stmnt_Node();
private:
    Expression_Node *expr;
};


class Expression_Node : public Statement_Node 
{
public:
    Expression_Node(Operand_Node *left, Token_Node *binop,
                    Expression_Node *right)
     : left(left), binop(binop), right(right){ }
    Expression_Node(Operand_Node *left) :
        Expression_Node(left, nullptr, nullptr) { }
                    
    virtual void print(int level);
    ~Expression_Node();
private:
    Operand_Node *left;
    Token_Node *binop;
    Expression_Node *right;
};


class Condition_Node : public Parse_Node
{
public:
    Condition_Node(Expression_Node *left, Token_Node *comp,
                   Expression_Node *right) :
        left(left), comp(comp), right(right) { }

    virtual void print(int level);
    ~Condition_Node();
private:
    Expression_Node *left;
    Token_Node *comp;
    Expression_Node *right;
};


class Token_Node : public Parse_Node
{
public:
    Token_Node(Token tok) : tok(tok) { }

    Token get_token() { return tok; }

    virtual void print(int level) 
    {
        std::cout << std::setw(level) <<  "" << tok << std::endl;
    }
private:
    Token tok;
};


class Operand_Node : public Token_Node
{
public:
    Operand_Node(Token tok) : Token_Node(tok) {} 
};
#endif
