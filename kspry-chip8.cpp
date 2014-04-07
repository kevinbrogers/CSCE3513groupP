#include "chip8.h"
#include <cstdlib>
#include <stdio.h>
#include <time.h>

chip8::chip8()
{
    
}

chip8::~chip8()
{
    
}

void chip8::init()
{
    pc     = 0x200;
    opcode = 0;
    I      = 0;
    sp     = 0;
    
    // Clear Display
    for (int i = 0; i < PIXELS; ++i)
        graphics[i] = 0;
    
    // Clear stack, registers, and keys
    for (int i = 0; i < STACK; ++i) {
        stack[i] = 0;
        V[i] = 0;
        keys[i] = 0;
    }
    
    // Clear memory
    for (int i = 0; i < MEMORY; ++i)
        memory[i] = 0;
    
    // load fontset
        //insert code here
    
    // Reset timers
    delayTimer = 0;
    soundTimer = 0;
    
    // Clear Screen once
    drawFlag = true;
    
    srand(time(NULL));
}

void chip8::emulateCycle()
{
    //insert opcode switch case here
    
    // Update timers
    if (delayTimer > 0)
        --delayTimer;
    
    if (soundTimer > 0)
    {
        if (soundTimer == 1)
            //make some noise
            
        --soundTimer;
    }
}

void chip8::render()
{
    // Draw code goes here
    
}

bool chip8::loadROM(const char* filename)
{
    init();
    //cout loading... "filename"
    
    //open file
    
    //check fie size
    
    //allocate memory to contain the whole file
    
    //copy file into buffer
    
    //copy buffer into Chip8 memory
    
    // cose file, free buffer
    
    return true; // will return false in previous lines if error
}


