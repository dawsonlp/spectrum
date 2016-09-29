#ifndef __spectrum_screen_h__
#define __spectrum_screen_h__

#include <stdbool.h>



typedef unsigned char byte;
const byte flashmask = 128;
const byte brightmask = 64;
const byte papermask = 8 + 16 + 32;
const byte inkmask = 4 + 2 + 1;

const byte dim 200
const byte bri 255

byte  speccy_palette[48] = {
    0,0,0,       //grb = 0
    0,0,dim,     //grb = 1
    dim,0,0,     //grb = 2
    dim,0,dim,   //grb = 3
    0,dim,0,     //grb = 4
    0,dim,dim,   //grb = 5
    dim,dim,0,   //grb = 6
    dim,dim,dim, //grb = 7
    0,0,0,       //grb = 0
    0,0,bri,     //grb = 1
    bri,0,0,     //grb = 2
    bri,0,bri,   //grb = 3
    0,bri,0,     //grb = 4
    0,bri,bri,   //grb = 5
    bri,bri,0,   //grb = 6
    bri,bri,bri, //grb = 7
};


typedef struct {
    byte ink;
    byte paper;
    bool flash;
} spectrum_attributes;



void show_attr( const spectrum_attributes * const attr);
const byte * unpack_line(const byte bmp[32], const byte attrs[32], byte res[256]);

const spectrum_attributes * unpack_attr(const byte bits, spectrum_attributes * res);

const byte * unpack_screen_byte(const byte bmp,const byte attr, byte * res);

const byte * unpack_line(const byte * bmp, const byte * attrs, byte * res);


const byte * unpack_section(const byte * bmp, const byte * attrs, byte * result);


const byte * unpack_speccy_screen(const byte * screen_bytes, byte * result);



#endif       

