#include <iostream>
#include <iomanip>
#include "lexer.h"
#include "parser.h"

using namespace std;

int main()
{
    Parse_Node * tree = parse();
    cout << setfill('|');
    tree->print(0);
}
