// Syntax analyzer for the l programming language
#include <iostream>

using namespace std;

//lexer stuff
char symbol=-1;          //lookahead buffer
const char LAMBDA=0x00;  //empty symbol
void next_symbol();
void mustbe(char s);
bool have(char s);


//production functions
void program();
void expression();
void expression_tail();
void term();
void term_tail();
void factor();
void unit();


int main()
{
    program();
}



/////////////////////////
// Lexer Functions
/////////////////////////

//get the next symbol
void next_symbol()
{
    //stop at the end of input
    if(symbol == LAMBDA) { return; }

    symbol = cin.get();  //get the next symbol

    //detect lambda
    if(cin.eof() || symbol == '\n') {
        symbol = LAMBDA;
    }
}


//apply the mustbe constraint
void mustbe(char s)
{
    if(have(s)) {
        return;
    }

    if(symbol == LAMBDA) {
        cerr << "Unexpected end of input." << endl;
    } else {
        cerr << "Unexpected symbol '" << symbol << "'" << endl;
    }
}


//have constraint
bool have(char s)
{
    if(symbol == s) {
        next_symbol();
        return true;
    }

    return false;
}


/////////////////////////
// Prouction Functions
/////////////////////////
void program()
{
    next_symbol();  //get things going
    expression();
    mustbe(LAMBDA);
}


void expression()
{
    term();
    expression_tail();
}


void expression_tail()
{
    if(have(LAMBDA)) { return; }

    if(have('+')) {
        term();
        expression_tail();
    }
}


void term()
{
    factor();
    term_tail();
}


void term_tail()
{
    if(have(LAMBDA)) { return; }

    if(have('*')) {
        factor();
        term_tail();
    }
}


void factor()
{
    if(have('(')) {
        expression();
        mustbe(')');
        return;
    }

    unit();
}


void unit()
{
    if(have('0')) return;
    if(have('1')) return;
    if(have('2')) return;
    if(have('3')) return;
    if(have('4')) return;
    if(have('5')) return;
    if(have('6')) return;
    if(have('7')) return;
    if(have('8')) return;
    mustbe('9');
}
