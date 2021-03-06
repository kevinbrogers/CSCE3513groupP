//---------------------------------
// File:   main.cpp
// Author: Group P
// IMPORTANT: when compiling in terminal, use command "g++ main.cpp -o main.exe -lncurses"
//---------------------------------

#include "keyinput.h"
#include <stdio.h>
#include <cstdlib>
#include "chip8.h"
#include <ncurses.h>
#include <unistd.h>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

// Display Size
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * main.cpp FINAL VERSION                                                      *
 * This file is the final version of main.cpp.  Main.cpp reads all the files in*
 * the user's folder for ROM files, then asks the user to select which one to  *
 * play.  It then converts this choice to a character array, loads the ROM, and*
 * then proceeds to emulate the cycle.                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


int main() {
    //INITIALIZE:
    //instantiate a new chip8 emulator and new keyinput handler
    chip8 newChip8;
    keyinput keyInput;
    char rom [80];


    //Introduce Emulator for user-friendliness
    printf("Welcome to the CHIP-8 Emulator for Linux!\nTo begin, select one of the available ROMs to load.\nBe sure to type your selection exactly.\nIf a ROM does not appear on the list below, make sure that it is placed in the\nsame folder as the emulator.\nTo exit, press the 'L' key.\n\n");

    //make list of ROMS
    DIR *dir;
    dirent *dire;
    struct stat filestat;

    dir = opendir(".");
    while(dire = readdir(dir))
    {
	if(stat(dire->d_name, &filestat))
		continue;
	if(S_ISDIR(filestat.st_mode))
		continue;
        if(strstr(dire->d_name, ".")==NULL)
	{
		printf("%s", dire->d_name);
		printf("\n");
	}
    }
    closedir(dir);

    //attempt to load rom
    printf("Select a ROM to load: ");
    scanf("%s",rom);

    while(!nc8.loadROM("PONG"))
    {
    printf("Invalid selection.  Make sure selection is spelled exactly.\nSelect a ROM to load: ");
    scanf("%s",rom);
    }

    //Initialize window
    initscr();		//initialize ncurses
    cbreak();		//get input after every character entered
    noecho();		//so input will not automatically print to window
    refresh();		//prepare console for window

    start_color();	//prepare console for colors
    init_pair(1, COLOR_BLACK, COLOR_BLACK); //defining black pixels
    init_pair(2, COLOR_WHITE, COLOR_WHITE); //defining white pixels

    nc8.emWin = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
    wrefresh(nc8.emWin);
    
    //GAME LOOP:
    int ch; 
    while((ch=getch()) != 'l')  //CHANGE TO ESCAPE KEY TO EXIT GAME WINDOW IN FINAL
    {
    	//emulate one cycle
        nc8.emulateCycle();

//	nc8.drawFlag = true;
	//if draw flag is set, update screen
	if(nc8.drawFlag==true)
		nc8.render();

        //store key press state
	if(keyInput.getKeys()!=-1)
		nc8.keys[keyInput.getKeys()] = 1;
	
	//update window
	wrefresh(nc8.emWin);
     }

    //when user decides to end program (by pressing l), destroy window and end ncurses mode
    delwin(nc8.emWin);
    endwin();

     
     //FOR TESTING!  //Because the display just reprints the array and does not
                     //yet make use of ncurses for the window, the following
                     //code tests that key inputs are working correctly.
                     //Final version will integrate seamlessly with display
    
    // get input; this section should be included in the loop so that it runs every time the screen refreshes
/*    keyInput.getInput();
    for (int i = 0; i < 16; i++) // ensure array is full of 0's
        newChip8.keys[i] = 0;
    if (keyInput.getLocation() != -1) // place a 1 in the proper array location
        newChip8.keys[keyInput.getLocation()] = 1;

    // testing to show input is taken properly; not to be included in final program
    cout << "your entry gives the array: ";
    for (int i = 0; i < 16; i++)
        cout << newChip8.keys[i];
    cout << endl;*/


    return 0;
    
}
