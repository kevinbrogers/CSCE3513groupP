//---------------------------------
// File:   main.cpp
// Author: Group P
// IMPORTANT: when compiling in terminal, use command "g++ main.cpp -o main.exe -lncurses"
//---------------------------------

#include <iostream>
#include "keyinput.h"
//added includes
#include <stdio.h>
#include <string>  //can be changed at a different time; for containing filename
#include "chip8.h"

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
    
    
    //Amanda: Added a working array that changes from 0 to " " when drawFlag is true.  However, I'm not familiar with 
    //        ncurses.  Since kRogers uses them for his files, I am currently giving myself a crash course in how to use
    //        them to render this array in a window.  For now, it will reprint the array every time the array is changed.
    //        That should be enough for a demo, but I'm still going to try to get that window working.
    //variables
    string filename;  //will have user select at somepoint; during testing pick 1 game to load
    int displayx = 32;
    int displayy= 64;
    chip8 newChip8;


    //set up render system with curses
    
    //initialize chip8 system and load game into memory
    if(!newChip8.load(filename))
        return 1;
    
    int count=0;  //FOR TESTING, delete in final version
    //emulate loop
    while(count < 2)  //FOR DISPLAY TESTING!  Change to "true" for actual game loop
    {
    	//emulate one cycle
        newChip8.emulate();

	//if draw flag is set, update screen
	if(newChip8.drawFlag)
		newChip8.render();

        count++;
	//store key press state
	//newChip8.setKeys();
     }

    return 0;
    
}
