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
	//combine 2 bites for the full opcode
	opcode = memory[pc] << 8 | memory[pc+1];
   
   //opcode switch case starts here
	
	switch(opcode & F000) // checks left most 4 bits 
	{
		case 0x0000: //none of the left most 4 bits of the opcode are 1
				switch(opcode & 0x000F)//check right most 4 bits 
					{
						case 0x0000: // opcode 0x00E0 meant to clear the screen
							for(int i = 0 ; i < 2048; ++i)
								graphics[i] = 0x0;
							drawFlag = true;
							pc += 2;
						break;
					
						case 0x000E: // E value in the right most 4 bits op 0x00EE
						--sp;
						pc = stack[sp];
						pc +=2;
						break;
					}
		break;
		
		case 0x1000: //op 0x1NNN
			pc = opcode & 0x0FFF;
		break;
		
		case 0x2000: // op 0x2NNN
			stack[sp] = pc;			
			++sp;					
			pc = opcode & 0x0FFF;	
		break;
		
		case 0x3000: // op 0x3XNN
			if(V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
				pc += 4;
			else
				pc += 2;
		break;
		
		case 0x4000: //  op 0x4XNN
			if(V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
				pc += 4;
			else
				pc += 2;
		break;
		
		case 0x5000: // op 0x5XY0
			if(V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
				pc += 4;
			else
				pc += 2;
		break;
		
		case 0x6000: //  op 0x6XNN
			V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
			
			pc += 2;
		break;
		
		case 0x7000: // op 0x7XNN
			V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
			pc += 2;
		break;
		//many more opcodes to be checked for and executed
		// the ones implemented here are already are 00E0 clearing the screen, 00EE returns from a subroutine
		// 1NNN jumping the address to NNN, 2NNN which calls subroutine NNN, 3xnn skips next instruction if VX equals NN , 
		// 4XNN skips next instruction if VX and NN are not equal, 5XY0 skips next instruction if VX equals VY
		// 6XNN sets VX equal to NN, and 7XNN adds NN to VX
	}
	
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
    printf("Loading: %s...\n", filename);
    
    // Open file
    FILE * file = fopen(filename, "r");
    if (file == NULL) {
        fputs("File error", stderr);
        return false;
    }
    
    //check fie size
    fseek(file, 0, SEEK_END);
    long fSize = ftell(file);
    rewind(file);
    printf("Filesize: %d\n", (int)fSize);
    
    //allocate memory to contain the whole file
    char * buffer = (char*)malloc(sizeof(char) * fSize);
    if (buffer == NULL) {
        fputs("Memory error", stderr);
        return false;
    }
    
    //copy file into buffer
    size_t result = fread(buffer, 1, fSize, file);
    if (result != fSize) {
        fputs("Reading error", stderr);
        return false;
    }
    
    //copy buffer into Chip8 memory
    if ((4096 - 512) > fSize) {
        for (int i = 0; i < fSize; ++i)
            memory[i + 512] = buffer[i];
    }
    else
        printf("Error: ROM too big for memory");
    
    // close file, free buffer
    fclose(file);
    free(buffer);
    
    // will return false in previous lines if error
    printf("ROM successfully loaded\n");
    return true; 
}

