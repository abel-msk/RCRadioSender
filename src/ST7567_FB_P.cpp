#include "ST7567_FB_P.h"


void ST7567_FB_P::printStr_P(int xpos, int ypos, PGM_P msg) {
    byte i=0;
    int x = xpos;
    int y = ypos;
    int wd = 0;

    for ( i = 0; i < strlen_P(msg); i++) {
        wd += charWidth(pgm_read_byte(msg+i));
    }

    if(x==-1) // right = -1
        x = scrWd - wd;
    else if(x<0) // center = -2
        x = (scrWd  - wd) / 2;
    if(x<0) x = 0; // left

    for ( i = 0; i < strlen_P(msg); i++) {
    
        int wd = printChar(x,y,pgm_read_byte(msg+i));
        x+=wd;
        if(cr && x>=scrWd) { 
            x=0; 
            y+=cfont.ySize; 
            if(y>scrHt) y = 0;
        }
    }
}

int ST7567_FB_P::strWidth_P(PGM_P str)
{
    int wd = 0;
    for ( int i = 0; i < strlen_P(str); i++) {
        wd += charWidth(pgm_read_byte(str+i));
    }
    // while (*str) wd += charWidth(*str++);
    return wd;
}