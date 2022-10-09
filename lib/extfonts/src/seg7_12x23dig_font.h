#ifndef Seg7_12x23_font_h
#define Seg7_12x23_font_h
#include "Arduino.h"
const uint8_t Seg7_12x23[] PROGMEM =
{
(uint8_t)-12, 24, ' ', ':',
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char  
        0x06, 0x00, 0x00, 0x00, 0xC0, 0x07, 0x00, 0xE0, 0x7F, 0x06, 0xE0, 0x7F, 0x06, 0xE0, 0x7F, 0x06, 0xC0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char !
        0x08, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char "
        0x0A, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0xC0, 0xFF, 0x03, 0xC0, 0xFF, 0x03, 0xC0, 0xFF, 0x03, 0x00, 0x24, 0x00, 0xC0, 0xFF, 0x03, 0xC0, 0xFF, 0x03, 0xC0, 0xFF, 0x03, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char #
        0x0A, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x00, 0x80, 0xC7, 0x01, 0x80, 0x8D, 0x01, 0xE0, 0xFF, 0x07, 0xE0, 0xFF, 0x07, 0xE0, 0xFF, 0x07, 0x80, 0x71, 0x01, 0x80, 0xE3, 0x01, 0x00, 0xE3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char $
        0x0A, 0x00, 0x00, 0x00, 0xC0, 0x03, 0x06, 0x60, 0x86, 0x07, 0x60, 0xE6, 0x03, 0xC0, 0xFB, 0x00, 0x00, 0x3E, 0x00, 0x80, 0xCF, 0x03, 0xE0, 0x63, 0x06, 0xE0, 0x60, 0x06, 0x20, 0xC0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char %
        0x0A, 0x00, 0x00, 0x00, 0xC0, 0xE3, 0x03, 0xE0, 0xF7, 0x07, 0x60, 0x3E, 0x06, 0x20, 0x1C, 0x04, 0x60, 0x3E, 0x06, 0xE0, 0xF7, 0x07, 0xC0, 0xE3, 0x03, 0x00, 0x70, 0x07, 0x00, 0x30, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char &
        0x06, 0xF8, 0x00, 0x00, 0xFC, 0x01, 0x00, 0x8C, 0x01, 0x00, 0x8C, 0x01, 0x00, 0xFC, 0x01, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char '
        0x06, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xC0, 0xFF, 0x07, 0xE0, 0xFF, 0x0F, 0xE0, 0x00, 0x0F, 0x20, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char (
        0x06, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08, 0xE0, 0x00, 0x0F, 0xE0, 0xFF, 0x0F, 0xC0, 0xFF, 0x07, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char )
        0x0A, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x54, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x38, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x54, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char *
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x80, 0xBB, 0x03, 0x80, 0xBB, 0x03, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,  // Code for char +
        0x03, 0x00, 0x00, 0xB0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ,
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,  // Code for char -
        0x03, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char .
        0x0C, 0x00, 0x00, 0x78, 0x00, 0x00, 0x7E, 0x00, 0x80, 0x1F, 0x00, 0xE0, 0x07, 0x00, 0xF8, 0x01, 0x00, 0x7E, 0x00, 0x80, 0x1F, 0x00, 0xE0, 0x07, 0x00, 0xF8, 0x01, 0x00, 0x7E, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x06, 0x00, 0x00,  // Code for char /
        0x0C, 0xFC, 0xEF, 0x7F, 0xFA, 0xC7, 0xBF, 0xF6, 0x83, 0xDF, 0x0E, 0x00, 0xE0, 0x0E, 0x00, 0xE0, 0x0E, 0x00, 0xE0, 0x0E, 0x00, 0xE0, 0x0E, 0x00, 0xE0, 0x0E, 0x00, 0xE0, 0xF6, 0x83, 0xDF, 0xFA, 0xC7, 0xBF, 0xFC, 0xEF, 0x7F,  // Code for char 0
        0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x83, 0x1F, 0xF8, 0xC7, 0x3F, 0xFC, 0xEF, 0x7F,  // Code for char 1
        0x0C, 0x00, 0xE0, 0x7F, 0x02, 0xD0, 0xBF, 0x06, 0xB8, 0xDF, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0xF6, 0x3B, 0xC0, 0xFA, 0x17, 0x80, 0xFC, 0x0F, 0x00,  // Code for char 2
        0x0C, 0x00, 0x00, 0x00, 0x02, 0x10, 0x80, 0x06, 0x38, 0xC0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0xF6, 0xBB, 0xDF, 0xFA, 0xD7, 0xBF, 0xFC, 0xEF, 0x7F,  // Code for char 3
        0x0C, 0xFC, 0x0F, 0x00, 0xF8, 0x17, 0x00, 0xF0, 0x3B, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x00, 0xF0, 0xBB, 0x1F, 0xF8, 0xD7, 0x3F, 0xFC, 0xEF, 0x7F,  // Code for char 4
        0x0C, 0xFC, 0x0F, 0x00, 0xFA, 0x17, 0x80, 0xF6, 0x3B, 0xC0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x06, 0xB8, 0xDF, 0x02, 0xD0, 0xBF, 0x00, 0xE0, 0x7F,  // Code for char 5
        0x0C, 0xFC, 0xEF, 0x7F, 0xFA, 0xD7, 0xBF, 0xF6, 0xBB, 0xDF, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x06, 0xB8, 0xDF, 0x02, 0xD0, 0xBF, 0x00, 0xE0, 0x7F,  // Code for char 6
        0x0C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x0E, 0x00, 0x00, 0xF6, 0x83, 0x1F, 0xFA, 0xC7, 0x3F, 0xFC, 0xEF, 0x7F,  // Code for char 7
        0x0C, 0xFC, 0xEF, 0x7F, 0xFA, 0xD7, 0xBF, 0xF6, 0xBB, 0xDF, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0xF6, 0xBB, 0xDF, 0xFA, 0xD7, 0xBF, 0xFC, 0xEF, 0x7F,  // Code for char 8
        0x0C, 0xFC, 0x0F, 0x00, 0xFA, 0x17, 0x80, 0xF6, 0x3B, 0xC0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0x0E, 0x38, 0xE0, 0xF6, 0xBB, 0xDF, 0xFA, 0xD7, 0xBF, 0xFC, 0xEF, 0x7F,  // Code for char 9
        0x03, 0x80, 0x03, 0x07, 0x80, 0x03, 0x07, 0x80, 0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00   // Code for char :
        };

#endif
