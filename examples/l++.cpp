//syntax analyzer for the L++ language

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//Token Types
//NOTE: We had to conver the operator into times and plus because
//      the syntax analyzer needs it to distinguish productions.
enum Token_Type { INVALID_TOK, INTEGER_TOK, PLUS_TOK, TIMES_TOK,
                  LPAREN_TOK, RPAREN_TOK, EOF_TOK };
static const char*token_label[] = { "INVALID", "INTEGER", "PLUS", "TIMES",
                         "LPAREN", "RPAREN", "EOF" };
struct Token {
    Token_Type type;
    string text;
};


//lexer interface
Token symbol;
void next_symbol();
bool have(Token_Type type);
void mustbe(Token_Type type);


//production functions
void program();
void expression();
void expression_tail();
void term();
void term_tail();
void factor();


int main()
{
    program();
}


/////////////////////////
// Lexer Functions
/////////////////////////
void 
lex_integer()
{
    //set the type
    symbol.type = INTEGER_TOK;

    //consume and store the int
    do {
        //get the digit
        symbol.text += cin.get();
    } while(isdigit(cin.peek()));
}


void 
next_symbol()
{
    symbol.text="";

    //NOTE: We are going to skip space in an effort to be more user friendly.
    while(cin.peek() == ' ') cin.get();

    //run the DFA for the regular subset of L++
    if(cin.eof() or cin.peek() == '\n') {
        symbol.type=EOF_TOK;
    } else if(isdigit(cin.peek())) {
        lex_integer();
    } else if(cin.peek() == '+') {
        symbol.type=PLUS_TOK;
        symbol.text = cin.get();
    } else if(cin.peek() == '*') {
        symbol.type=TIMES_TOK;
        symbol.text = cin.get();
    } else if(cin.peek() == '(') {
        symbol.type=LPAREN_TOK;
        symbol.text = cin.get();
    } else if(cin.peek() == ')') {
        symbol.type=RPAREN_TOK;
        symbol.text = cin.get();
    } else {
        symbol.type=INVALID_TOK;
        symbol.text = cin.get();
    }
}


bool 
have(Token_Type type)
{
    if(symbol.type == type) {
        next_symbol();
        return true;
    }

    return false;
}



void
mustbe(Token_Type type)
{
    if(have(type)) {
        return;
    }

    //error reporting
    if(symbol.type == EOF_TOK) {
        cerr << "Unexpected end of input." << endl;
    } else {
        cerr << "Unexpected token: " << token_label[symbol.type] << " \"" 
             << symbol.text << "\"" << endl;
    }

    cerr << "  I was expecting a " << token_label[type] << endl;
}


/////////////////////////
// Prouction Functions
/////////////////////////
void program()
{
    next_symbol();  //get things going
    expression();
    mustbe(EOF_TOK);
}


void expression()
{
    term();
    expression_tail();
}


void expression_tail()
{
    if(have(PLUS_TOK)) {
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
    if(have(TIMES_TOK)) {
        factor();
        term_tail();
    }
}


void factor()
{
    if(have(LPAREN_TOK)) {
        expression();
        mustbe(RPAREN_TOK);
        return;
    }

    mustbe(INTEGER_TOK);
}
