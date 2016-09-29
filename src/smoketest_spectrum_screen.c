#include "spectrum_screen.h"

void show_pixel(const byte pixel){
    printf("%u|",pixel);
}

void test_line(){
    byte bmp[32] = { 0,1,2,4, 255, 123, 1,1,1,1,1,255,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    byte attrs[32] = {56, 56, 1,2,7,7,7,7,7,7,7,7,7,128+64+32+7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7};
    byte res[256];
    unpack_line(bmp, attrs, res);
    for (int i = 0; i < 256; i++)
        show_pixel(res[i]);
}

void test_screen(){
    byte bmp[6912];
    memset(bmp, 0, 6912);
    byte result[49152];
    memset(result, 0, 49152);
    int avoidoptimization = 0;
    for (int f = 0; f< 10000; f++){
        unpack_speccy_screen(bmp, result);
        avoidoptimization = avoidoptimization + result[53];
    }
    printf("\ndone %d\n", avoidoptimization);
    show_pixel(result[53]);
}

void main(){
    test_line();
    test_screen();
}

