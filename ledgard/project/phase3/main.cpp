#include <iostream>
#include <iomanip>
#include "lexer.h"
#include "parser.h"
#include "parse-tree.h"

using namespace std;

int main()
{
   Lexer ll(cin);
   Parser p(ll);
   p.parse()->print(0);
}
