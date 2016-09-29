#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "spectrum_screen.h"

const spectrum_attributes * unpack_attr(const byte bits, spectrum_attributes * res){
    byte bright = (bits & brightmask) >> 3; //ie 8 or 0
    res->ink = (bits & inkmask) + bright;
    res->paper = ((bits & papermask) >> 3) + bright;
    res->flash = (bits & flashmask) == 128;
    return res;
}

const byte * unpack_screen_byte(const byte bmp,const byte attr, byte * res){
    spectrum_attributes attrs;
    unpack_attr(attr, &attrs);
    byte bit = 128;
    for (int x = 0; x<8; x++){
        res[x]=(bmp & bit)?  attrs.ink: attrs.paper;
        bit = bit >> 1;
    }
    return res;
}

/*
 *  * take 32 bitmap bytes, 32 attributes bytes and return 256 bytes with the
 *   * correct screen color in them
 *    */
const byte * unpack_line(const byte * bmp, const byte * attrs, byte * res){
    for (int i = 0; i<32; i++){
        unpack_screen_byte(bmp[i], attrs[i], (byte *)(res + (i*8)));
    }
    return res;
}


/*
 *  * Takes 2048 bitmap bytes representing 64 lines
 *   * and 256 attribute bytes for the same section - returns
 *    * an array of 16384 bytes of bytes meant as palette index values
 *     */
const byte * unpack_section(const byte * bmp, const byte * attrs, byte * result){
    for (int block = 0; block < 8; block++){
        const byte * attr = attrs + (block * 32);
        int startpix = block * 32;
        for (int line = 0; line<8; line++){
            int pix1 = startpix + (line * 32 * 8);
            int full_offset = pix1*8;
            unpack_line(bmp + pix1, attr, result + full_offset);
        }
    }
    return result;

}

const byte * unpack_speccy_screen(const byte * screen_bytes, byte * result){
    /*6912 bytes consisting of 6144 screen bytes and 768 attribute bytes
     *      * returning 16384 * 3 = 49152 */
    for(int sect =0; sect < 3; sect++){
        int pixstart = sect * 2048;
        int attrstart = 6144 + sect * 256;
        unpack_section( 
                screen_bytes + pixstart, 
                screen_bytes + attrstart, 
                result + (16384 * sect)
                );
    }
    return result;    
}

void show_attr(const spectrum_attributes * const attr){
    printf("attributes: %i, %i, %i\n", attr->ink, attr->paper, attr->flash);
}

