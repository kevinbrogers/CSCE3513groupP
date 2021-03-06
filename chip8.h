/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * chip8.h FINAL VERSION                                                       *
 * variables that represent the chip8 hardware are mostly made private, while  *
 * the functions that operate on them are made public.                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <ncurses.h>


#ifndef CHIP8_H
#define	CHIP8_H

#define PIXELS (64 * 32)
#define KEYS 16
#define REGISTERS 16
#define STACK 16
#define MEMORY 4096

class chip8
{
public:
    chip8();
    ~chip8();
    
    bool drawFlag;
    
    void emulateCycle();
    void render();
    bool loadROM(const char * filename);
    void init();
    
    WINDOW* emWin;		       // window for display
    unsigned char graphics[PIXELS];  //array of pixels
    unsigned char keys[KEYS];
    
private:
    unsigned short pc;			// Program counter
    unsigned short opcode;		// Current opcode
    unsigned short I;			// Index register
    unsigned short stackPtr;		// Stack pointer
    unsigned char  V[REGISTERS];	// V-regs (V0-VF)
    unsigned short stack[STACK];	// Stack (16 levels)
    unsigned char  memory[MEMORY];	// Memory (size = 4k)		
    unsigned char  delay_timer;		// Delay timer
    unsigned char  sound_timer;		// Sound timer		


};

#endif	/* CHIP8_H */
