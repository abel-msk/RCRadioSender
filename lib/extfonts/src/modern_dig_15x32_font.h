#ifndef modern_dig_15x32_font_h
#define modern_dig_15x32_font_h
#include "Arduino.h"
const uint8_t modern_dig_15x32[] PROGMEM ={
(uint8_t)-15, 32, '0', '0'+10,  // -width, height, firstChar, lastChar
        0x0F, 0x00, 0xFE, 0x7F, 0x00, 0xE0, 0x01, 0x80, 0x07, 0x18, 0x00, 0x00, 0x18, 0x04, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x20, 0x18, 0x00, 0x00, 0x18, 0xE0, 0x01, 0x80, 0x07, 0x00, 0xFE, 0x7F, 0x00,  // Code for char 0
        0x0f, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char 1
        0x0f, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0x00, 0x00, 0xA0, 0x18, 0x00, 0x00, 0x90, 0x04, 0x00, 0x00, 0x8C, 0x02, 0x00, 0x00, 0x82, 0x01, 0x00, 0x80, 0x81, 0x01, 0x00, 0x40, 0x80, 0x01, 0x00, 0x30, 0x80, 0x01, 0x00, 0x08, 0x80, 0x01, 0x00, 0x06, 0x80, 0x02, 0x80, 0x01, 0x80, 0x0C, 0x60, 0x00, 0x80, 0x30, 0x1C, 0x00, 0x80, 0xC0, 0x03, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,  // Code for char 2
        0x0F, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x30, 0x01, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x18, 0x00, 0x80, 0x01, 0x16, 0x00, 0x80, 0x81, 0x11, 0x00, 0x40, 0x61, 0x10, 0x00, 0x40, 0x19, 0x20, 0x00, 0x20, 0x07, 0x40, 0x00, 0x18, 0x00, 0x80, 0x07, 0x07, 0x00, 0x00, 0xF8, 0x00,  // Code for char 3
        0x0F, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x80, 0x21, 0x00, 0x00, 0x60, 0x20, 0x00, 0x00, 0x18, 0x20, 0x00, 0x00, 0x06, 0x20, 0x00, 0x80, 0x01, 0x20, 0x00, 0x60, 0x00, 0x20, 0x00, 0x18, 0x00, 0x20, 0x00, 0x06, 0x00, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00,  // Code for char 4
        0x0F, 0x00, 0x00, 0x00, 0x0C, 0xC0, 0x3F, 0x00, 0x30, 0x3F, 0x10, 0x00, 0x40, 0x01, 0x08, 0x00, 0x40, 0x01, 0x08, 0x00, 0x80, 0x01, 0x04, 0x00, 0x80, 0x01, 0x04, 0x00, 0x80, 0x01, 0x04, 0x00, 0x80, 0x01, 0x08, 0x00, 0x80, 0x01, 0x08, 0x00, 0x40, 0x01, 0x10, 0x00, 0x40, 0x01, 0x20, 0x00, 0x20, 0x00, 0x40, 0x00, 0x18, 0x00, 0x80, 0x07, 0x07, 0x00, 0x00, 0xF8, 0x00,  // Code for char 5
        0x0f, 0x00, 0xFE, 0xFF, 0x01, 0xE0, 0x01, 0x07, 0x0E, 0x18, 0xC0, 0x00, 0x30, 0x04, 0x20, 0x00, 0x40, 0x02, 0x20, 0x00, 0x40, 0x02, 0x10, 0x00, 0x80, 0x01, 0x10, 0x00, 0x80, 0x01, 0x10, 0x00, 0x80, 0x01, 0x20, 0x00, 0x40, 0x02, 0x20, 0x00, 0x40, 0x02, 0x40, 0x00, 0x20, 0x0C, 0x80, 0x01, 0x18, 0x10, 0x00, 0x0E, 0x07, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char 6
        0x0f, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x1C, 0x01, 0x00, 0x80, 0x03, 0x01, 0x00, 0x70, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x01, 0xC0, 0x01, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x81, 0x03, 0x00, 0x00, 0x71, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char 7
        0x0F, 0x00, 0x00, 0xE0, 0x03, 0xE0, 0x00, 0x1C, 0x1C, 0x1C, 0x07, 0x03, 0x20, 0x02, 0x88, 0x00, 0x40, 0x02, 0x50, 0x00, 0x40, 0x01, 0x50, 0x00, 0x80, 0x01, 0x20, 0x00, 0x80, 0x01, 0x20, 0x00, 0x80, 0x01, 0x20, 0x00, 0x80, 0x01, 0x50, 0x00, 0x80, 0x02, 0x50, 0x00, 0x40, 0x02, 0x88, 0x00, 0x40, 0x1C, 0x07, 0x03, 0x20, 0xE0, 0x00, 0x1C, 0x1C, 0x00, 0x00, 0xE0, 0x03,  // Code for char 8
        0x0f, 0x80, 0x3F, 0x00, 0x00, 0x70, 0xC0, 0x00, 0x18, 0x08, 0x00, 0x03, 0x20, 0x04, 0x00, 0x04, 0x40, 0x02, 0x00, 0x04, 0x80, 0x02, 0x00, 0x08, 0x80, 0x01, 0x00, 0x08, 0x80, 0x01, 0x00, 0x08, 0x80, 0x02, 0x00, 0x08, 0x40, 0x02, 0x00, 0x04, 0x40, 0x04, 0x00, 0x02, 0x30, 0x18, 0x00, 0x01, 0x0C, 0x60, 0x80, 0x00, 0x03, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char 9
        0x05, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0xC0, 0x01, 0x80, 0x03, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char :
        };

#endif
