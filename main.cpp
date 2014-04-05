//---------------------------------
// File:   main.cpp
// Author: Group P
// IMPORTANT: when compiling in terminal, use command "g++ main.cpp -o main.exe -lncurses"
//---------------------------------

#include <iostream>
#include "keyinput.h"

using namespace std;

int main() {
    int keys[16]; // array to show which key is pressed; access to this array is necessary for opcodes EX9E, EXA1, and FX0A
    keyinput keyInput;

    // get input; this section should be included in the loop so that it runs every time the screen refreshes
    keyInput.getInput();
    for (int i = 0; i < 16; i++) // ensure array is full of 0's
        keys[i] = 0;
    if (keyInput.getLocation() != -1) // place a 1 in the proper array location
        keys[keyInput.getLocation()] = 1;

    // testing to show input is taken properly; not to be included in final program
    cout << "your entry gives the array: ";
    for (int i = 0; i < 16; i++)
        cout << keys[i];
    cout << endl;
}
