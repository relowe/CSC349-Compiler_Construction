#include <iostream>
#include <iomanip>
#include "lexer.h"
#include "parser.h"
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
    Parse_Node *tree = parse();

    tree->build_symtab();
    tree->check_symbols();

    if (not symtab.undef.empty()) {
        cerr << "Undefined Names:  ";
        print_names(symtab.undef, cerr);
        cerr << endl;
    }
    cout << "Symbol Table:" << endl;
    cout << "-------------" << endl;
    for (auto p = symtab.tab.begin(); p != symtab.tab.end(); p++) {
      cout << "\t" << *p << endl;
    }
}
