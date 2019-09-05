#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include "lexer.h"
#include "parser.h"
#include "parse-tree.h"
#include "symtab.h"

using namespace std;

void print_names(const set<string>& s, ostream& out)
{
   for (set<string>::iterator p = s.begin(); p != s.end(); p++) {
      if (p != s.begin()) { out << ", "; }
      out << *p;
   }
}

int main()
{
   Lexer ll(cin);
   Parser p(ll);
   Parse_Tree* t = p.parse();

   t->build_symtab();
   t->check_symbols();
   
   if (not symtab.dupls.empty())
   {
      cerr << "Duplicate Names:  ";
      print_names(symtab.dupls, cerr);
      cerr << endl;
   }

   if (not symtab.undef.empty())
   {
      cerr << "Undefined Names:  ";
      print_names(symtab.undef, cerr);
      cerr << endl;
   }

   if (t->match_types())
   {
      t->generate();
   }
}
