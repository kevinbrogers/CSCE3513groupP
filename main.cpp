//---------------------------------
// File:   main.cpp
// Author: Group P
// IMPORTANT: when compiling in terminal, use command "g++ main.cpp -o main.exe -lncurses"
//---------------------------------

#include <iostream>
#include "keyinput.h"
#include <stdio.h>
#include <cstdlib>
#include "chip8.h"
using namespace std;

// Display Size
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * main.cpp DEMO VERSION                                                       *
 * This file is the demo version of main.cpp.  It shows the functionality of   *
 * all working parts and has comments for non-functional requirments to be     *
 * implemented later.  This is just to prove that all the parts work.  Main.cpp*
 * takes a filename, converts it into a character, loads the ROM, and then     *
 * proceeds to emulate ten cycles, each of which are printed in a new array,   *
 * to make sure that the display, input, and system itself is working correctly*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main() {
    //instantiate a new chip8 emulator and new keyinput handler
    chip8 newChip8;
    keyinput keyInput;
    
    //set up render system with ncurses
    initscr();
    cbreak(); //get input after every character entered
    noecho(); //so input will not be printed to screen
    refresh(); //prepare console for writing
    start_color(); //prepare console for printing in color
    newChip8.emWin = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0); //set size of window
//    box(newChip8.emWin, 0, 0);  //use this to test that a window is displaying at all
    wrefresh(newChip8.emWin);
    getch();
    
    //Final version will allow the user to select from a number of ROMS.  For Demo,
    //we're just using pong as an example
    //Load ROM.  If loadROM fails to load the file, return 1
    if(!newChip8.loadROM("Pong"))
        return 1;
        
    //emulate loop
    //In the final design, while should be set to true, so the system will keep
    //looping indefinitely, so long as the game is running.  For our Demo, we are
    //only allowing it to loop 10 times because that should be enough to prove
    //functionality
    int count=0;  //REMOVE IN FINAL VERSION
    while(count < 10)  //CHANGE TO TRUE IN FINAL VERSION
    {
    	//emulate one cycle
        newChip8.emulateCycle();

	//if draw flag is set, update screen
	if(newChip8.drawFlag)
		newChip8.render();
        
        //store key press state
	//newChip8.setKeys();

        count++;  //REMOVE IN FINAL VERSION
        
     }
     
     //FOR TESTING!  //Because the display just reprints the array and does not
                     //yet make use of ncurses for the window, the following
                     //code tests that key inputs are working correctly.
                     //Final version will integrate seamlessly with display
    
    // get input; this section should be included in the loop so that it runs every time the screen refreshes
    keyInput.getInput();
    for (int i = 0; i < 16; i++) // ensure array is full of 0's
        newChip8.keys[i] = 0;
    if (keyInput.getLocation() != -1) // place a 1 in the proper array location
        newChip8.keys[keyInput.getLocation()] = 1;

    // testing to show input is taken properly; not to be included in final program
    cout << "your entry gives the array: ";
    for (int i = 0; i < 16; i++)
        cout << newChip8.keys[i];
    cout << endl;


    return 0;
    
}
