
#ifndef CHIP8_H
#define	CHIP8_H

#define PIXELS (64 * 32)
#define KEYS 16
#define REGISTERS 16
#define STACK 16
#define MEMORY 4096

class chip8 {
        public:
            chip8();
            ~chip8();
            
            bool drawFlag;
            unsigned char graphics[PIXELS];    // 64 by 32 pixels
            unsigned char keys[KEYS];          // keyboard inputs
            
            void emulateCycle();
            void render();
            bool loadROM(const char * filename);
           
    
        private:
            unsigned short pc;          // Program Counter
            unsigned short opcode;      // Current opcode
            unsigned short I;           // Register index
            unsigned short sp;          // Stack pointer
    
            unsigned char V[REGISTERS];        // Registers (V0-VF)
            unsigned stack[STACK];         // Stack (16 levels)
            unsigned memory[MEMORY];      // Memory 4 kilobytes
            
            unsigned delayTimer;        // Delay timer
            unsigned soundTimer;        // Sound timer
            
            void init();
};




#endif	/* CHIP8_H */

