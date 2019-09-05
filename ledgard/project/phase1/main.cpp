#include <iostream>
#include <iomanip>
#include "lexer.h"

using namespace std;

int main()
{
   Lexer ll(cin);

   while (not ll.empty()) 
   {
      cout << setw(5) << ll.curr().line_number << ":  "
           << ll.curr().repn << " (" << ll.curr().tok << ")" << endl;
      ll.pop();
   }
}
