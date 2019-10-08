//lexical analyzer for the L++ language

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//Token Types
enum Token_Type { INVALID_TOK, INTEGER_TOK, OPERATOR_TOK,
                  LPAREN_TOK, RPAREN_TOK, EOF_TOK };
static const char*token_label[] = { "INVALID", "INTEGER", "OPERATOR",
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


int main()
{
    //scan and print all lexemes
    do { 
        //lex the next symbol
        next_symbol();

        //print out the symbol
        cout << token_label[symbol.type] << '\t' << symbol.text << endl;
    } while(symbol.type != EOF_TOK);
}


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

    //run the DFA for the regular subset of L++
    if(cin.eof() or cin.peek() == '\n') {
        symbol.type=EOF_TOK;
    } else if(isdigit(cin.peek())) {
        lex_integer();
    } else if(cin.peek() == '+' or cin.peek() == '*') {
        symbol.type=OPERATOR_TOK;
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

    cerr << "Unexpected token: " << token_label[symbol.type] << " \"" 
         << symbol.text << "\"" << endl;
}
