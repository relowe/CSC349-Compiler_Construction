#include <iostream>
#include <iomanip>
#include "lexer.h"
#include "parser.h"

using namespace std;

int main()
{
   Lexer ll(cin);
   Parser p(ll);

   cout << boolalpha << p.parse() << endl;
}
