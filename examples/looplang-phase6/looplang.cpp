#include <iostream>
#include <iomanip>
#include <cstring>
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

int main(int argc, char **argv)
{
    Parse_Node *tree = parse();
    enum {COMPILE, INTERPRET} mode = INTERPRET;

    //process command line arguments
    for(int i=1; i<argc; i++) {
        if(strcmp(argv[i], "-c")==0) {
            mode = COMPILE;
        }
    }

    if (not symtab.undef.empty()) {
        cerr << "Undefined Names:  ";
        print_names(symtab.undef, cerr);
        cerr << endl;
        return -1;
    }

    if(mode == INTERPRET) {
        tree->exec(nullptr);
    } else {
        tree->generate();
    }
}
