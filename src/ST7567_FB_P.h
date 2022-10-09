#ifndef __ST7567_FB_P_H__
#define __ST7567_FB_P_H__
#include <Arduino.h>
#include <ST7567_FB.h>

class ST7567_FB_P  : public ST7567_FB {
    public:
    ST7567_FB_P(uint8_t dc, uint8_t rst, uint8_t cs) : ST7567_FB(dc,rst,cs){};
    ST7567_FB_P(uint8_t dc, uint8_t rst, uint8_t cs, uint8_t sdi, uint8_t clk) : ST7567_FB(dc,rst,cs,sdi,clk){};
    void printStr_P(int xpos, int ypos, PGM_P msg);
    int strWidth_P(PGM_P str);
};


#endif // !   __ST7567_FB_P_H__
