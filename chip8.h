#include <iostream>
#include <string>
using namespace std;


/* CHIP 8 HEADERFILE
*  Largely designed for display testing, so there's a lot missing.
*  There may also be some overlap with the other structure designed by kSpry and kWalsh, so you guys feel free to
*  update this any way you need to in order for it to work with your version.
*/
#ifndef CHIP8_H

class chip8
{
public:
    chip8();
    ~chip8();
    
    bool drawFlag;
    
    void emulate();
    void render();
    bool load(string filename);
    void initialize();
    
    unsigned char win[64 * 32];  //array of pixels
    unsigned char key[16];
    
private:
    unsigned short pCount;				// Program counter
    unsigned short opcode;			// Current opcode
    unsigned short index;			// Index register
    unsigned short stackPtr;				// Stack pointer
    unsigned char  V[16];			// V-regs (V0-VF)
    unsigned short stack[16];		// Stack (16 levels)
    unsigned char  memory[4096];	// Memory (size = 4k)		
    unsigned char  delay_timer;		// Delay timer
    unsigned char  sound_timer;		// Sound timer		


};
#define	CHIP8_H



#endif	/* CHIP8_H */

chip8::chip8(){}
chip8::~chip8(){}

void chip8::initialize()
{
  //NOTE:  In this version, initialize is called when a file is loaded, not in the constructor.  Although I guess
  //       either way would work.
  //FOR TESTING!  Although, I'm pretty sure this is a fairly valid initialize function
	pCount = 0x200;	//reset program counter
	opcode = 0;	//reset opcode
	index = 0;	//reset index
	stackPtr = 0;	//reset stack pointer

	//clear display
	for(int i=0; i<2048; i++)
            win[i] = 0;

        //clear stack
        for(int i=0; i<16; i++)
            stack[i] = 0;
        for(int i=0; i<16; i++)
            key[i] = V[i] = 0;
        //clear memory
        for(int i=0; i<4096; i++)
            memory[i] = 0;
        
       	// Reset timers
	      delay_timer = 0;
	      sound_timer = 0;

        // Clear screen
      	drawFlag = true;
        
}
void chip8::emulate()
{
    //FOR TESTING! Definitely replace the whole of this
    cout << "Emulation happens here." << endl;
    //Fetch Opcode
    //Process Opcode
    //FOR TESTING!  Just making sure that a given coordinate will change color when given input.  Delete this too
    for(int x=8; x<17; x++)
    {
        for(int y=8; y<17; y++)
        {
            win[x*y] = 1;
        }
    }
    
}
void chip8::render()
{
    //I'm still working on adding ncurses functions to represent this that way.  For now, this fills an array with
    //a 0 if the pixel is supposed to be black, and a " " if the pixel is supposed to be white
    //draw array
    for(int x=0; x<32; x++)
    {
        for(int y=0; y<64; y++)
        {
            if(win[(x*64)+y]==0)
                printf("0");  //color pixel black
            else
                printf(" ");  //color pixel white
        }
        printf("\n");
    }
    printf("\n");
}
bool chip8::load(string filename)
{
    initialize();
    //FOR TESTING! To be written as a group, but for now, assume a file is loaded, hence return true
    cout << "Loading..." << endl;
    return true;
}
