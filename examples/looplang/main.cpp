#include <iostream>
#include "lexer.h"

using namespace std;

int main()
{
    do {
        next_symbol();
        cout << curr_symbol() << endl;
    } while(not have(EOF_TOK));
}
