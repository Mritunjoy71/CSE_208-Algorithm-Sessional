/*
**********************************************************************************
*   Author   : mausy131                                                          *
*   Homepage : www.youtube.com/mausy131                                          *
*   Copyright: ©2013 mausy131. Under the GNU license version 3.0                 *
*   Notes    : Please comment, rate, subscribe and report broken links please!   *
**********************************************************************************
*/

#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

static const char alphanum[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";  // chars we need for generation

int stringLength = sizeof(alphanum) - 1;

char genRandom(){

    return alphanum[rand() % stringLength];
}

string randomword(){

    //SetConsoleTitle("Random text string Generator. ©mausy131 2013");

    srand(time(0));
    std::string Str;

    int length = 0;

    cout << "Enter the length of the string:" << endl;
    cin >> length;

    for(unsigned int i = 0; i < length; ++i){
    //cout << genRandom << endl;          // You can delete the // and put // for Str += genRandom
    Str += genRandom();     // All characters in genRandom will be copied to Str.
                            // I did this because I needed it for a project.

    }
    //cout << "This is your random serial:" << endl;
    //cout << Str << endl;   // Str holds the same as genRandom since all the characters have been copied. You can comment this out with the // if you use cout << genRandom();
     return str;


cout << endl;
system("PAUSE");
return 0;
}

















