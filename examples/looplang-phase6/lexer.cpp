// Lexical analyzer for loop lang
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "lexer.h"

using namespace std;

static const char* TOKEN_LABEL[] = { "INVALID_TOK", "ASSIGN_TOK", "PLUS_TOK",
                                     "MINUS_TOK", "LESS_TOK", "LESS_EQUAL_TOK",
                                     "GREATER_TOK", "GREATER_EQUAL_TOK",
                                     "EQUAL_TOK", "NOT_EQUAL_TOK", "INTEGER_TOK",
                                     "IDENTIFIER_TOK", "WHILE_TOK", "END_TOK",
                                     "PRINT_TOK", "EOF_TOK"}; 
static Token cur;  //the current symbol


///////////////////////////////////
//helper functions for the lexer
///////////////////////////////////

static void lt() 
{
    cur.repn = cin.get();

    //check for <=
    if(cin.peek() == '=') {
        //<= 
        cur.repn += cin.get();
        cur.type = LESS_EQUAL_TOK;
    } else {
        cur.type = LESS_TOK;
    }
}


static void gt() 
{
    cur.repn = cin.get();

    //check for >=
    if(cin.peek() == '=') {
        //>= 
        cur.repn += cin.get();
        cur.type = GREATER_EQUAL_TOK;
    } else {
        cur.type = GREATER_TOK;
    }
}


static void eq()
{
    cur.repn = cin.get();

    //check for ==
    if(cin.peek() == '=') {
        //== 
        cur.repn += cin.get();
        cur.type = EQUAL_TOK;
    } else {
        cur.type = ASSIGN_TOK;
    }
}


//!= processor
static void neq()
{
    cur.repn = cin.get();

    if(cin.peek() != '=') {
        cur.type = INVALID_TOK;
        return;
    }

    //consume the =
    cur.repn += cin.get();
    cur.type = NOT_EQUAL_TOK;
}


//integers
static void integer()
{
    //blank integer 
    cur.repn = "";
    cur.type = INTEGER_TOK;

    do {
        //add the digit to the repn
        cur.repn+= cin.get();
    } while(isdigit(cin.peek()));
}


//identifiers
static void identifier()
{
    //set our type correctly
    cur.type = IDENTIFIER_TOK;

    //consume the identifier
    while(isalnum(cin.peek())) {
        cur.repn += cin.get();
    }
}


//keyword
static void keyword(string k, Token_Type t)
{
    //start with empty string
    cur.repn = "";

    //consume until we no longer match
    for(int i=0; i<k.length(); i++) {
        //look for mismatch
        if(cin.peek() != k[i]) {
            identifier();
            return;
        }
        cur.repn += cin.get();
    }

    //detect the end of this chain
    if(isalnum(cin.peek())) {
        identifier();
        return;
    }

    //yay it's the keyword!
    cur.type = t; 
}


//get the next symbol
void next_symbol()
{
    //skip spaces
    while(isspace(cin.peek())) { cin.get(); }

    //detect end of file
    if(cin.eof()) {
        cur.type = EOF_TOK;
        cur.repn = "";
        return;
    }

    char c = cin.peek();
    if(c == '+') {
        //the plus token
        cur.type=PLUS_TOK;
        cur.repn = cin.get();
    } else if(c == '-') {
        //the minus token
        cur.type=MINUS_TOK;
        cur.repn = cin.get();
    } else if(c == '<') {
        //< group
        lt();
    } else if(c == '>') {
        // > group
        gt();
    } else if(c == '=') {
        // = group
        eq();
    } else if(c == '!') {
        // !=
        neq();
    } else if(isdigit(c)) {
        integer();
    } else if(c == 'w') {
        keyword("while", WHILE_TOK);
    } else if(c == 'e') {
        keyword("end", END_TOK);
    } else if(c == 'p') {
        keyword("print", PRINT_TOK);
    } else if(isalpha(c)) {
        cur.repn = "";
        identifier();
    } else {
        cur.type = INVALID_TOK;
        cur.repn = cin.get();
    }
}


//return the current symbol
Token curr_symbol()
{
    return cur;
}

//if we have the token, advance and return true 
//false (with no advance) o.w.
bool have(Token_Type t)  
{
    if(cur.type == t) {
        return true;
    }

    return false;
}

//like have, but prints error message on failure
void mustbe(Token_Type t)
{
    if(have(t)) {
        return;
    }

    //halt on error
    cerr << "Unexpected token: " << cur << endl;
    exit(1);
}


//print the token
std::ostream & operator<<(std::ostream &os, Token t)
{
    return os << TOKEN_LABEL[t.type] << ": \"" << t.repn << "\"";
}
