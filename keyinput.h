//---------------------------------
// File:   keyinput.h
// Author: Kevin Rogers
// This class contains code used to take input and map to the hex keypad used for gameplay.
//---------------------------------

#include <iostream>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

class keyinput {
    int entered;
   public:
    int translateKey(char);
    int getKeys();
    int getInput();
    int getLocation() {return entered;}
};

//----------------------------
// function: translateKey(char)
// purpose:  takes a character and returns an integer corresponding to a value in key[]
//----------------------------
int keyinput::translateKey(char c) {
    int a = 0;
    switch(c) {
        case '1': a = 0; break;  // 1 maps to 1 by placing a 1 in key[0]
        case '2': a = 1; break;  // 2 maps to 2 by placing a 1 in key[1]
        case '3': a = 2; break;  // 3 maps to 3 by placing a 1 in key[2]
        case '4': a = 3; break;  // 4 maps to A by placing a 1 in key[3]
        case 'q': a = 4; break;  // q maps to 4 by placing a 1 in key[4]
        case 'w': a = 5; break;  // w maps to 5 by placing a 1 in key[5]
        case 'e': a = 6; break;  // e maps to 6 by placing a 1 in key[6]
        case 'r': a = 7; break;  // r maps to B by placing a 1 in key[7]
        case 'a': a = 8; break;  // a maps to 7 by placing a 1 in key[8]
        case 's': a = 9; break;  // s maps to 8 by placing a 1 in key[9]
        case 'd': a = 10; break; // d maps to 9 by placing a 1 in key[10]
        case 'f': a = 11; break; // f maps to C by placing a 1 in key[11]
        case 'z': a = 12; break; // z maps to 0 by placing a 1 in key[12]
        case 'x': a = 13; break; // x maps to F by placing a 1 in key[13]
        case 'c': a = 14; break; // c maps to E by placing a 1 in key[14]
        case 'v': a = 15; break; // v maps to D by placing a 1 in key[15]
        default: a = -1;         // anything else results in all zeroes in key[]
    }
    return a;
}

//----------------------------
// function: getKeys()
// purpose:  determine which key is pressed and return the location in
//           key[] that should be set to '1'
//----------------------------
int keyinput::getKeys() {
    char c = getch();
    refresh();
    return translateKey(c);
}

//----------------------------
// function: getInput(int[])
// purpose:  initialize curses library and use above functions;
//           return entire key[] array with at most one value set to '1'
//----------------------------
int keyinput::getInput() {
    WINDOW * mainwin;

    // initialize the curses library
    if ((mainwin = initscr()) == NULL) {
        fprintf(stderr, "Error initializing ncurses.\n");
        exit(EXIT_FAILURE);
    }

    // enable keyboard mapping
    keypad(stdscr, TRUE);

    entered = getKeys();

    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}
