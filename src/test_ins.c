#include <stdint.h>
#include <stdio.h>

typedef unsigned char byte;

typedef struct {
    byte hi;
    byte lo;
} word;

typedef struct {
    word w0;
    word w1;
    word w2;
    word w3;
} quadword;

typedef union {
    quadword qw;
    int64_t  qwtot;
} mainregfile;

typedef byte memory[65536];



typedef struct {
    word WZ;//Used internally only, for loading addresses, one byte at a time
    word BC;
    word DE;
    word HL;
    word WZx;
    word BCx;
    word DEx;
    word HLx;
    word AF;
    word AFx;
    word IX;
    word IY;
    word PC;
    word SP;
    word IR;
    word interrupt_status; //Combine im, iff1, iff2 and access via bitmasks.
    int64_t tcycles;
    memory * mem;
} Z80Registers;

typedef Z80Registers * (Z80Instr *)(Z80Registers *);

const int16_t InSpectrumScreenMemBlock = 0xc00;

Z80Registers * ld_op(Z80Registers * z80, byte instr){
    //determine source, dest from bitmap of instr
    //Encoding is 01 SRC DEST, SRC and DEST have same encoding from
    //0 to 7: b, c, d, e, h, l, (HL), a
    byte src = instr & 0x7
    byte dst = (instr >> 3) & 0x7;
    byte val;
    if (src < 6)
        val = *((byte *)z80 + src); //too ugly - need a better one
    //Have a read_val(src) and a write_val(dest, val) that take account
    //of the (hl) extra read time etc.
    else if (src == 7)
        val = &(z80->AF.asByte.hi); //or whatever the address of a is
    else{    
    //load from (hl)
    
        val = 0; //todo
    }
    if (dest) < 6 {
            byte * destptr = (byte *)z80 + dest 
            z80->tcycles += 4; 
        } else {

        }
    } 
    return z80;
}

//Specific implementation for Sinclair spectrum, if the ULA is 
//REading a byte then there is a delay...
Z80Registers * readbyte(Z80Registers * z80, word addr){
    //Get byte into Z reg and increment tcycles by any delay.
    //
    //
    if ((addr.asWord & InSpectrumScreenMemBlock)== 0x800){
        //There may be a delay   
        z80->tcycles++;//TODO: Implement a correct delay that checks the tcycles
                       //and adds correct delay only if ULA is actually reading from 
                       //RAM at the time.
    }
      
    return z80;
}

Z80Registers * writebyte(Z80Registers * z80, word addr, byte val){
    return z80;
}

typedef Z80Registers * (*Z80Instr)(Z80Registers *);//Function pointers for instructions
const Z80Instr std[256] = {exx}; //Don't really want to do 256 instructions, so need to double dispatch

void swap(word * a, word * b){
    word save = *a;
    *a = *b;
    *b = save;
}

void swap_q(int64_t * a, int64_t * b){
    int64_t save = *a;
    *a = *b;
    *b = save;
}

Z80Registers * exx(Z80Registers * z80){
    swap_q((int64_t *)&z80->WZ,(int64_t *) &z80->WZx);
    z80->tcycles += 13; //no interrupt implications here
    return z80;
}

Z80Registers * run_instruction(Z80Registers * z80){
    //find correct instruction to run and call it...
    return z80;
}

int main(){
    printf("Reg file: %ld bytes\n", sizeof(Z80Registers));
}
