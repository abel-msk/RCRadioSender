#ifndef __MAIN_SCREEN__
#define __MAIN_SCREEN__
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "ST7567_FB_P.h"
#include "config.h"

// #include "vga8x15_font.h"
#include "proppl5x7_font.h"
#include "small4x5_font.h"



#define SCR_LBL_BUFF_LEN 16

  
// #define MSG_FONT vga8x15 
#define MSG_FONT PropPL5x7
#define MANU_FONT PropPL5x7
#define SMALL_FONT Small4x5PL


// PROGMEM const char connetc_n[] = "Connect";  
PROGMEM const char remoteID_n[] = "RemoteID";    
PROGMEM const char level_n[] = "Signal";   
PROGMEM const char temp_n[] = "Board t";  
PROGMEM const char powerR_n[] = "Remote";  
PROGMEM const char powerL_n[] = "Local"; 

PROGMEM const char LH_n[] = "H:"; 
PROGMEM const char LV_n[] = "V:"; 
PROGMEM const char RH_n[] = "H:"; 
PROGMEM const char RV_n[] = "V:"; 

PROGMEM const char INC_n[] = "incr"; 
PROGMEM const char DEC_n[] = "decr";
PROGMEM const char SAVE_n[] = "Save"; 
PROGMEM const char CANC_n[] = "Cancel";


PROGMEM const char ON_n[] = "ON"; 
PROGMEM const char OFF_n[] = "OFF"; 
PROGMEM const char yes_n[] = "Yes"; 
PROGMEM const char no_n[] = "No"; 


PROGMEM const char profile_n[] = "Cur profile";
PROGMEM const char remoteid_n[] = "Remote ID";
PROGMEM const char sleept_n[] = "Sleep timer";

PROGMEM const char key1_n[] = "Left top btn code";
PROGMEM const char key2_n[] = "Left bot btn code";
PROGMEM const char key3_n[] = "Right top btn code";
PROGMEM const char key4_n[] = "Right bot btn code";

PROGMEM const char swapjs_n[] = "Swap Joystics";

PROGMEM const char save_prof_n[] = "Save profile %1d";

PROGMEM const char unknown[] = "--";  

PROGMEM const byte local_level_pos[2]  = {73,33};
PROGMEM const byte remote_level_pos[2] = {103,33};

//  drawBitmap

// const uint8_t PROGMEM pwr_empty_bmp[] = {  // w, h, data
//     20, 10,
//     0xFC, 0x84, 0xFF, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0xFF, 
//     0x0, 0x0, 0x3, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3,
// };

const uint8_t PROGMEM pwr_empty_bmp[] = {  // w, h, data
    20, 10,
    0xFF, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0xFF, 0x84, 0xFC, 
    0x3, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, 0x0, 0x0
};

const uint8_t PROGMEM sig_level_bmp[] = {  // w, h, data
    20, 10,
    0xFF, 0x1, 0x1, 0x1, 0xFF, 0x4, 0x4, 0x4, 0xFC, 0x10, 0x10, 0x10, 0xF0, 0x40, 0x40, 0x40, 0xC0, 0x0, 0x0, 0x0, 
    0x3, 0x2, 0x2, 0x2, 0x3, 0x2, 0x2, 0x2, 0x3, 0x2, 0x2, 0x2, 0x3, 0x2, 0x2, 0x2, 0x3, 0x3, 0x3, 0x3, 
};

const uint8_t PROGMEM sig_level2_bmp[] = {  // w, h, data
    17, 9,
    0xFF, 0x1, 0x1, 0x1, 0xFF, 0x4, 0x4, 0x4, 0xFC, 0x10, 0x10, 0x10, 0xF0, 0x40, 0x40, 0x40, 0xC0, 
    0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 
};

class MainScreen {


    public:
    ST7567_FB_P* lcd;
    byte x=0;
    byte y=0;

    MainScreen(ST7567_FB_P* l):lcd(l){}
    void refreshMain(byte profile, byte radioCH, byte id, int8_t temp, byte pwrRemote, byte pwrLocal );
    void refreshCalibration(int16_t LH, int16_t LV, int16_t RH, int16_t RV) ;
    void refreshMessage(PGM_P msg, byte value, bool isValue = true);
    void refreshYesNo(char* msg, bool yes_no);
    void refreshYesNo(PGM_P msg, bool yes_no);
    // void printStr_P(int xpos, int ypos, PGM_P msg);
};

#endif