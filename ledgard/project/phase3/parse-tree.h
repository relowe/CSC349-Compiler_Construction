/**
   @file parse-tree.h
   @author Lee Wittenberg
   @date 2017-06-01
   @version 2.0

   Classes for constructing a parse tree for the Ledgard language.
 */
#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <sstream>
#include <map>
#include <set>

// forward delarations
class Type_Node;

class Parse_Tree 
{
public:
      // code generator
   virtual void generate(std::ostream& out = std::cout) = 0;
      // for debugging
   virtual void print(int level) = 0;
      // check type matching rules
   virtual bool match_types() = 0;
      // type of current node
   virtual Type_Node* get_type() = 0;
      // build symbol table (only needed for declarations)
   virtual void build_symtab() = 0;
      // check symbol declarations 
   virtual void check_symbols() = 0;
      // inheritable destructor
   virtual ~Parse_Tree() {}
};

class Type_Node : public Parse_Tree
{
public:
   // pointers for type matching (to avoid excess heap use)
   static Type_Node* VOID;
   static Type_Node* INTEGER;
   static Type_Node* BOOLEAN;

   virtual int size() = 0;            // size of data item (in bytes)
   virtual std::string display() = 0; // human-readable rep'n (for error msgs)
   virtual bool is_simple() { return false; }  // whether type is simple or not
                                               // (default is not)
   // every type can be printed using display() member function
   void print(int level)
      { std::cout << std::setw(level) << "" << display() << std::endl; }

   // type rules here can have no mismatches & all generate {void}
   bool match_types() { return true; }
   Type_Node* get_type() { return Type_Node::VOID; }

   // nothing to do with symbol tables here
   void build_symtab() {}
   void check_symbols() {}
};

inline bool is_static(Type_Node *t)
{
   return t == Type_Node::INTEGER or t == Type_Node::BOOLEAN;
}

const int INTEGER_SIZE = 4;         // our integers will be 4 bytes long
const int BOOLEAN_SIZE = 4;         // as will our booleans (for simplicity)

class Void_Type_Node : public Type_Node
{
public:
   void generate(std::ostream& out = std::cout) {}
   int size() { return 0; }
   std::string display() { return "void"; }
};

class Int_Type_Node : public Type_Node
{
public:
   void generate(std::ostream& out = std::cout) {}
   int size() { return INTEGER_SIZE; }
   std::string display() { return "integer"; }
   bool is_simple() { return true; }
};

class Bool_Type_Node : public Type_Node
{
public:
   void generate(std::ostream& out = std::cout) {}
   int size() { return BOOLEAN_SIZE; }
   std::string display() { return "boolean"; }
   bool is_simple() { return true; }
};

class Array_Type_Node : public Type_Node
{
public:
   Array_Type_Node(int lower, int upper, Type_Node* t)
      : lwb(lower), upb(upper), base(t) {}
   void generate(std::ostream& out = std::cout) {}
   int size() { return (upb - lwb + 1) * base->size(); }
   std::string display()
   {
      std::ostringstream o;
      o << "array[" << lwb << ".." << upb << "] of " << base->display();
      return o.str();
   }
   int get_lwb() { return lwb; }
   int get_upb() { return upb; }
   Type_Node* get_base_type() { return base; }
   ~Array_Type_Node() { if (not is_static(base)) { delete base; } }
private:
   int lwb, upb;        // lower and upper bounds, respectively
   Type_Node* base;     // base type of array
};

class Decl_Node : public Parse_Tree
{
public:
   void add_ident(const std::string& s) { idents.push_back(s); }
   void set_type(Type_Node* t) { type = t; }
   void generate(std::ostream& out = std::cout);
   void build_symtab();
   void print(int level)
   {
      typedef std::list<std::string>::iterator iter;
      std::cout << std::setw(level) << "";
      for (iter p = idents.begin(); p != idents.end(); p++) {
         if (p != idents.begin()) { std::cout << ", "; }
         std::cout << *p;
      }
      std::cout << ":" << std::endl;
      type->print(level+1);
   }
   // type rules here can have no mismatches & all generate {void}
   bool match_types() { return true; }
   Type_Node* get_type() { return Type_Node::VOID; }

   // no symbol checking needed here
   void check_symbols() {}
   ~Decl_Node() { if (not is_static(type)) { delete type; } }
private:
   std::list<std::string> idents;       // identifiers being declared
   Type_Node* type;                     // type of identifiers
};

class Stmt_Node : public Parse_Tree
{
public:
   // all statement type match rules generate {void}
   Type_Node* get_type() { return Type_Node::VOID; }
};

class Expr_Node : public Parse_Tree
{
public:
   // expressions need line numbers for reporting type errors
   void set_line(int n) { line_number = n; }
   int get_line() { return line_number; }
protected:
   int line_number;     // line on which operator occurs
};

class Int_Literal_Node : public Expr_Node
{
public:
   Int_Literal_Node(int n) : value(n) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << value << std::endl;
   }
   bool match_types() { return true; }
   Type_Node* get_type() { return Type_Node::INTEGER; }
   void build_symtab() {}
   void check_symbols() {}
private:
   int value;
};

class Bool_Literal_Node : public Expr_Node
{
public:
   // we really only need one of each of these (and can reuse them in the
   // tree)
   static Expr_Node* TRUE;
   static Expr_Node* FALSE;

   Bool_Literal_Node(bool b) : value(b) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << std::boolalpha << value
                << std::endl;
   }
   bool match_types() { return true; }
   Type_Node* get_type() { return Type_Node::BOOLEAN; }
   void build_symtab() {}
   void check_symbols() {}
private:
   bool value;
};

inline bool is_static(Expr_Node *e)
{
   return e == Bool_Literal_Node::TRUE or e == Bool_Literal_Node::FALSE;
}

class Binop_Node : public Expr_Node
{
public:
   void build_symtab() {}
   void check_symbols();
   ~Binop_Node()
      {
         if (not is_static(left)) { delete left; }
         if (not is_static(right)) { delete right; }
      }
protected:
   Binop_Node(Expr_Node* l, Expr_Node* r) : left(l), right(r) {}
   Expr_Node* left;     // left operand
   Expr_Node* right;    // right operand
};

class LT_Node : public Binop_Node
{
public:
   LT_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "<"
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class LE_Node : public Binop_Node
{
public:
   LE_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "<="
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class EQ_Node : public Binop_Node
{
public:
   EQ_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "=="
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class NE_Node : public Binop_Node
{
public:
   NE_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "!="
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class GE_Node : public Binop_Node
{
public:
   GE_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << ">="
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class GT_Node : public Binop_Node
{
public:
   GT_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << ">"
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class Plus_Node : public Binop_Node
{
public:
   Plus_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "+"
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class Minus_Node : public Binop_Node
{
public:
   Minus_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "-"
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class Times_Node : public Binop_Node
{
public:
   Times_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "*"
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class Div_Node : public Binop_Node
{
public:
   Div_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "/"
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class And_Node : public Binop_Node
{
public:
   And_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "and"
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class Or_Node : public Binop_Node
{
public:
   Or_Node(Expr_Node* l, Expr_Node* r) : Binop_Node(l, r) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "or"
                << " (" << line_number << ")" << std::endl;
      left->print(level + 1);
      right->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class Unop_Node : public Expr_Node
{
public:
   void build_symtab() {}
   void check_symbols();
   ~Unop_Node() { if (not is_static(operand)) { delete operand; } }
protected:
   Unop_Node(Expr_Node* x) : operand(x) {}
   Expr_Node* operand;
};

class Not_Node : public Unop_Node
{
public:
   Not_Node(Expr_Node* x) : Unop_Node(x) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "not"
                << " (" << line_number << ")" << std::endl;
      operand->print(level + 1);
   }
   bool match_types();
   Type_Node* get_type();
};

class Vble_Node : public Expr_Node
{
public:
   Vble_Node(const std::string& id) : identifier(id) {}
   void add_subscript(Expr_Node* x) { subscripts.push_back(x); }
      // generate code for the variable's value
   void generate(std::ostream& out = std::cout);
      // generate code for the variable's address
   void gen_addr(std::ostream& out = std::cout);
   void print(int level)
   {
      typedef std::list<Expr_Node*>::iterator iter;
      std::cout << std::setw(level) << "" << identifier
           << (subscripts.size() == 0 ? "" : "[]")
           << " (" << line_number << ")" << std::endl;
      for (iter p = subscripts.begin(); p != subscripts.end(); p++)
         { (*p)->print(level + 1); }
   }
   bool match_types();
   Type_Node* get_type();
   void build_symtab() {}
   void check_symbols();
   ~Vble_Node()
      {
         for (auto p = subscripts.begin(); p != subscripts.end(); p++) {
            if (not is_static(*p)) { delete *p; }
         }
      }
private:
   std::string identifier;
   std::list<Expr_Node*> subscripts;
};

class Assign_Node : public Stmt_Node
{
public:
   Assign_Node(Vble_Node* lhs, Expr_Node* rhs)
      : variable(lhs), expression(rhs) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "Assignment:" << std::endl;
      variable->print(level+1);
      std::cout << std::setw(level) << "" << ":="
                << " (" << line_number << ")" << std::endl;
      expression->print(level+1);
   }
   bool match_types();
   void build_symtab() {}
   void check_symbols();
   void set_line(int n) { line_number = n; }
   ~Assign_Node()
      {  delete variable;
         if (not is_static(expression)) { delete expression; } }
private:
   Vble_Node* variable;
   Expr_Node* expression;
   int line_number;           // line on which := token occurs
};

class Xchg_Node : public Stmt_Node
{
public:
   Xchg_Node(Vble_Node* lhs, Vble_Node* rhs)
      : left(lhs), right(rhs) {}
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      std::cout << std::setw(level) << "" << "Exchange:" << std::endl;
      left->print(level+1);
      std::cout << std::setw(level) << "" << ":=:"
                << " (" << line_number << ")" << std::endl;
      right->print(level+1);
   }
   bool match_types();
   void build_symtab() {}
   void check_symbols();
   void set_line(int n) { line_number = n; }
   ~Xchg_Node() { delete left; delete right; }
private:
   Vble_Node* left;
   Vble_Node* right;
   int line_number;           // line on which :=: token occurs
};

class If_Node : public Stmt_Node
{
public:
   If_Node(Expr_Node* e) : condition(e) {}
   void add_then(Stmt_Node* s) { then_part.push_back(s); }
   void add_else(Stmt_Node* s) { else_part.push_back(s); }
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      typedef std::list<Stmt_Node*>::iterator iter;
      std::cout << std::setw(level) << "" << "If:" << std::endl;
      condition->print(level + 1);
      std::cout << std::setw(level) << "" << "Then:" << std::endl;
      for (iter p = then_part.begin(); p != then_part.end(); p++)
         { (*p)->print(level + 1); }
      if (not else_part.empty()) {
         std::cout << std::setw(level) << "" << "Else:" << std::endl;
         for (iter p = else_part.begin(); p != else_part.end(); p++)
            { (*p)->print(level + 1); }
      }
   }
   bool match_types();
   void build_symtab() {}
   void check_symbols();
   ~If_Node()
      {
         if (not is_static(condition)) { delete condition; }
         for (auto p = then_part.begin(); p != then_part.end(); p++) {
            delete *p;
         }
         for (auto p = else_part.begin(); p != else_part.end(); p++) {
            delete *p;
         }
      }
private:
   Expr_Node* condition;
   std::list<Stmt_Node*> then_part, else_part;
};

class While_Node : public Stmt_Node
{
public:
   While_Node(Expr_Node* e) : condition(e) {}
   void add_stmt(Stmt_Node* s) { body.push_back(s); }
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      typedef std::list<Stmt_Node*>::iterator iter;
      std::cout << std::setw(level) << "" << "While:" << std::endl;
      condition->print(level + 1);
      std::cout << std::setw(level) << "" << "Loop:" << std::endl;
      for (iter p = body.begin(); p != body.end(); p++)
         { (*p)->print(level + 1); }
   }
   bool match_types();
   void build_symtab() {}
   void check_symbols();
   ~While_Node()
      {
         if (not is_static(condition)) { delete condition; }
         for (auto p = body.begin(); p != body.end(); p++) {
            delete *p;
         }
      }
private:
   Expr_Node* condition;            // condition on which to loop
   std::list<Stmt_Node*> body;      // statements to repeat
};

class IO_Node : public Stmt_Node
{
public:
   void add_vble(Vble_Node* v) { vbles.push_back(v); }
   bool match_types();
   void build_symtab() {}
   void check_symbols();
   ~IO_Node()
      { for (auto p = vbles.begin(); p != vbles.end(); p++) { delete *p; } }
protected:
   std::list<Vble_Node*> vbles;     // variables to print/read into
};

class Input_Node : public IO_Node 
{
public:
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      typedef std::list<Vble_Node*>::iterator iter;
      std::cout << std::setw(level) << "" << "Input:" << std::endl;
      for (iter p = vbles.begin(); p != vbles.end(); p++)
         { (*p)->print(level + 1); }
   }
};

class Output_Node : public IO_Node 
{
public:
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      typedef std::list<Vble_Node*>::iterator iter;
      std::cout << std::setw(level) << "" << "Output:" << std::endl;
      for (iter p = vbles.begin(); p != vbles.end(); p++)
         { (*p)->print(level + 1); }
   }
};

class Prog_Node : public Parse_Tree
{
public:
   void add_decl(Decl_Node* d) { decls.push_back(d); }
   void add_stmt(Stmt_Node* d) { stmts.push_back(d); }
   void generate(std::ostream& out = std::cout);
   void print(int level)
   {
      typedef std::list<Decl_Node*>::iterator d_iter;
      typedef std::list<Stmt_Node*>::iterator s_iter;
      std::cout << std::setw(level) << "" << "Program:" << std::endl;
      for (d_iter p = decls.begin(); p != decls.end(); p++)
         { (*p)->print(level + 1); }
      std::cout << std::setw(level) << "" << "begin" << std::endl;
      for (s_iter p = stmts.begin(); p != stmts.end(); p++)
         { (*p)->print(level + 1); }
      std::cout << std::setw(level) << "" << "end" << std::endl;
   }
   bool match_types();
   void build_symtab();
   void check_symbols();

   // a program itself has no inherent type
   Type_Node* get_type() { return Type_Node::VOID; }
   ~Prog_Node()
      {
         for (auto p = decls.begin(); p != decls.end(); p++) { delete *p; }
         for (auto p = stmts.begin(); p != stmts.end(); p++) { delete *p; }
      }
private:
   std::list<Decl_Node*> decls;     // declarations in program
   std::list<Stmt_Node*> stmts;     // statements in program
};

#endif
