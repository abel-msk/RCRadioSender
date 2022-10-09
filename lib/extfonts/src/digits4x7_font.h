#ifndef Digits4x7_font_h
#define Digits4x7_font_h

#include "Arduino.h"

const uint8_t Digits4x7[] PROGMEM =
{
(uint8_t)-4, 8, '0', '9'+5,
        0x04, 0x7F, 0x41, 0x41, 0x7F,            //  0
        0x01, 0x7F, 0x00, 0x00, 0x00,            //  1
        0x04, 0x79, 0x49, 0x49, 0x4F,            //  2
        0x04, 0x49, 0x49, 0x49, 0x7F,            //  3
        0x04, 0x0F, 0x08, 0x08, 0x7F,            //  4
        0x04, 0x4F, 0x49, 0x49, 0x79,            //  5
        0x04, 0x7F, 0x49, 0x49, 0x79,            //  6
        0x04, 0x01, 0x01, 0x01, 0x7F,            //  7
        0x04, 0x7F, 0x49, 0x49, 0x7F,            //  8
        0x04, 0x4F, 0x49, 0x49, 0x7F,            //  9
        0x01, 0x14, 0x00, 0x00, 0x00,            //  :
        0x01, 0x40, 0x00, 0x00, 0x00,            //  .
        0x03, 0x08, 0x08, 0x08, 0x00,            //  -
        0x03, 0x08, 0x1C, 0x08, 0x00,            //  +
        0x04, 0x7F, 0x40, 0x40, 0x40             //  L
};

#endif

