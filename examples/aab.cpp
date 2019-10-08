// An implementation of the regular language aa.*b+
// Written for readability, not effeciency!
// Author: Robert Lowe (c) 2019 No Rights Reserved
#include <iostream>
#include <string>

using namespace std;

//returns true only for strict matches
bool match(const string &str);


int main()
{
    string s;

    //read a string
    getline(cin, s);


    //test it
    if(match(s)) {
        cout << "ACCEPT" << endl;
    } else {
        cout << "REJECT" << endl;
    }
}


//returns true only for strict matches
bool 
match(const string &str)
{
    enum { START, S1, S2, S3 } state = START;
    
    //iterate over the strings
    for(auto itr = str.begin(); itr != str.end(); itr++) {
        if(state == START) {  //handle start transitions
            if(*itr == 'a') {
                state = S1;
            } else {
                return false;  //invalid!
            }
        } else if(state == S1) { //handle s1 transitions
            if(*itr == 'a') {
                state = S2;
            } else {
                return false; //invalid!
            }
        } else if(state == S2) { 
            if(*itr == 'b') {
                state = S3;
            }

            //remain in S2 for any other character
        } else if(state == S3) {
            if(*itr != 'b') { //reject anything other than b
                return false;
            }
        }
    }

    //handle accept
    if(state == S3) {
        return true;
    } else {
        return false;
    }
}
