#include "MainScreen.h"
#include <string.h>
// #include "fonts_all.h"
// #include "term8x10_font.h"


// #include "tiny3x7sq_font.h"
// #include "testfont.h"
// #include "digi2_19x15full_font.h"
// #include "term11x16_font.h"  //term2_11x16_font.h  //Term2_11x16
// #include "seg7_12x21dig_font.h"

#define LEFT_MARGING 10
#define TOP_MARGING 15
#define AXIS_W 44
#define AXIS_H 44
#define R_OFFSET 64

#define MAIN_RIGHTCOL_POS 85

#define TMP_BUF_LEN 6

// #define SRCEEN_DEBUG

//currentMenu = (const MenuItem *) pgm_read_word(&(currentMenu[currentMenuItemIndexPos].childMenu));

void MainScreen::refreshMain(byte profile, byte radioCH, byte id, int8_t temp, byte pwrRemote, byte pwrLocal ) {
    x=55;
    y=7;
    char buf[TMP_BUF_LEN];

    lcd->cls();
    lcd->setFont(PropPL5x7); 

    lcd->printStr_P(10,y,PSTR("Profile")); 
    sprintf_P(buf,PSTR("%03d"),profile);  
    lcd->printStr(x,y,buf); 

    y+= lcd->fontHeight() + 5;
    lcd->printStr_P(10,y,PSTR("Channel")); 
    //  lcd->printStr_P(10,y,remoteID_n);    
    sprintf_P(buf,PSTR("%03d"),radioCH);  
    lcd->printStr(x,y,buf); 

    //  Remote ID
    y+= lcd->fontHeight() + 5;
    // strcpy_P(buf,remoteID_n); 
    // lcd->printStr(10,y,buf); 
    lcd->printStr_P(10,y,remoteID_n); 
    sprintf_P(buf,PSTR("%03d"),id);  
    lcd->printStr(x,y,buf); 

    //  Set temperature
    y+= lcd->fontHeight() + 5;
    // strcpy_P(buf,temp_n);
    // lcd->printStr(10,y,buf); 
    lcd->printStr_P(10,y,temp_n); 
    sprintf_P(buf,PSTR("%02d"),temp); 
    lcd->printStr(x,y,buf); 
    lcd->drawCircle(x + lcd->strWidth(buf)+2,y+1,1,1); 

    //   Power meters, right scrin part

    x=MAIN_RIGHTCOL_POS;   //   Горизонтальная позиция правой колонки
    y=7;
    // strcpy_P(buf,powerR_n);
    // lcd->printStr(x,y,buf); 
    lcd->printStr_P(x,y,powerR_n); 
    y+= lcd->fontHeight() + 3;  
    lcd->drawBitmap(pwr_empty_bmp,x,y);

    lcd->fillRect(  MAIN_RIGHTCOL_POS + 1, y+1, map (pwrRemote, 1,100,1,16),  8, 1 );
    y=33;

    lcd->printStr_P(x,y,powerL_n);

    y+= lcd->fontHeight() + 3; 
    lcd->drawBitmap(pwr_empty_bmp,x,y);
    lcd->fillRect( MAIN_RIGHTCOL_POS + 1,  y+1, map (pwrLocal, 1,100,1,16),  8,  1 );

    lcd->display();
    // Serial.println(F("Refresh Main"))
}

void MainScreen::refreshCalibration(int16_t LH, int16_t LV, int16_t RH, int16_t RV) {
    char buf[TMP_BUF_LEN];
    lcd->cls();
    lcd->setFont(PropPL5x7); 

    // --------- Left pane
    // y+= lcd->fontHeight() + 5;
    x=10;
    // strcpy_P(buf,LH_n);
    // lcd->printStr(x,2,buf); 
    lcd->printStr_P(x,2,LH_n); 
    x+=lcd->strWidth_P(LH_n);

    sprintf_P(buf,PSTR("%d"),LH); 
    lcd->printStr(x,2,buf); 
    x+=lcd->strWidth(buf);

    if ( x < 30) x=32;
    // strcpy_P(buf,LV_n);
    // lcd->printStr(x,2,buf); 
    // x+=lcd->strWidth(buf);
    lcd->printStr_P(x,2,LV_n); 
    x+=lcd->strWidth_P(LV_n);

    sprintf(buf,"%d",LV); 
    lcd->printStr(x,2,buf); 
    x+=lcd->strWidth(buf);

    // --------- Right pane
    x=R_OFFSET + 10;
    // strcpy_P(buf,RH_n);
    // lcd->printStr(x,2,buf); 
    // x+=lcd->strWidth(buf);
    lcd->printStr_P(x,2,RH_n); 
    x+=lcd->strWidth_P(RH_n);    

    sprintf_P(buf,PSTR("%d "),RH); 
    lcd->printStr(x,2,buf); 
    x+=lcd->strWidth(buf);

    if ( x < R_OFFSET+32) {
        x=R_OFFSET+32;
    }
    // strcpy_P(buf,RV_n);
    // lcd->printStr(x,2,buf); 
    // x+=lcd->strWidth(buf);
    lcd->printStr_P(x,2,RV_n); 
    x+=lcd->strWidth_P(RV_n);   

    sprintf_P(buf,PSTR("%d "),RV); 
    lcd->printStr(x,2,buf); 
    x+=lcd->strWidth(buf);

    lcd->drawLine(LEFT_MARGING+AXIS_W/2,
        TOP_MARGING,    
        LEFT_MARGING+AXIS_W/2,
        TOP_MARGING+AXIS_H,
        1); // Left Vertical
    lcd->drawLine(LEFT_MARGING,
        TOP_MARGING + AXIS_H/2, 
        LEFT_MARGING+AXIS_W, 
        TOP_MARGING+AXIS_H/2, 
        1);               // Left Horisontal
    lcd->drawLine(R_OFFSET+LEFT_MARGING+AXIS_W/2,   
        TOP_MARGING,     
        R_OFFSET+LEFT_MARGING+AXIS_W/2, 
        TOP_MARGING+AXIS_H, 
        1);  //   Right Vertical
    lcd->drawLine(R_OFFSET+LEFT_MARGING,
        TOP_MARGING + AXIS_H/2, 
        R_OFFSET+LEFT_MARGING+AXIS_W,
        TOP_MARGING+AXIS_H/2,
        1);        //   Right Horisontal
    

    for(y = 13; y < 64; y += 4) {
        for (x = LEFT_MARGING - 2 ; x < 128 - LEFT_MARGING + 6; x+=4)
        {
            if ( x < 60 | x > 70 ) { 
            // lcd->drawLineHfast(x,x+2,y,1);
                lcd->drawPixel(x,y,1);
            }
        }        
    }

    // for(byte i = LEFT_MARGING; i < 128 - LEFT_MARGING; i += 4) {
    //     lcd->drawLineVfastD(i,16,64,1);
    // }


    //    Left position view
    lcd->fillCircle(
        map(LH+INPUT_RANGE,
            0,
            INPUT_RANGE*2,
            LEFT_MARGING,
            LEFT_MARGING+AXIS_W),
             // Left border +  X pos + rad
        map(LV+INPUT_RANGE,
            0,
            INPUT_RANGE*2,
            TOP_MARGING,
            TOP_MARGING+AXIS_H), //  Top border  + Y pos + rad
        2,                                             //  Radius
        1                                              //  Width
    );

    //    Right position view
    lcd->fillCircle(
        map(RH+INPUT_RANGE,
            0,
            INPUT_RANGE*2,
            R_OFFSET + LEFT_MARGING,
            R_OFFSET + LEFT_MARGING+AXIS_W), // Left border +  X pos + rad
        map(RV+INPUT_RANGE,
            0,
            INPUT_RANGE*2,
            TOP_MARGING,
            TOP_MARGING+AXIS_H), //  Top border  + Y pos + rad
        2,                                             //  Radius
        1                                              //  Width
    );

    // Serial.print(F("RV : "));
    // Serial.print(RV);
    // Serial.print(F(" | "));
    // Serial.print(RV+INPUT_RANGE);
    // Serial.print(F(", Res : "));
    // Serial.print(
    //         map(RV+INPUT_RANGE,
    //         0,
    //         INPUT_RANGE*2,
    //         TOP_MARGING,
    //         TOP_MARGING+AXIS_H));
    // Serial.println();

#ifdef SRCEEN_DEBUG
    Serial.print(RH);
    Serial.print(F("\t"));
    Serial.print(RH+INPUT_RANGE);
    Serial.print(F("\t"));
    Serial.print(0);
    Serial.print(F("\t"));
    Serial.print(INPUT_RANGE*2);
    Serial.print(F("\t"));
    Serial.print(R_OFFSET + LEFT_MARGING);
    Serial.print(F("\t"));
    Serial.println(R_OFFSET + LEFT_MARGING+AXIS_W);
#endif

    lcd->display();
}

void MainScreen::refreshMessage(PGM_P msg, byte value, bool isValue) {
    char buf[TMP_BUF_LEN];

    lcd->cls();
    lcd->setFont(Small4x5PL);
    lcd->drawTriangle( 5,4,2,7,5,10,1);
    // strcpy_P(buf,SAVE_n);
    lcd->printStr_P(7,5, SAVE_n);
    lcd->drawTriangle(5,53,2,56,5,59,1);
    // strcpy_P(buf,CANC_n);
    lcd->printStr_P(8,54, CANC_n);
    // lcd->setFont(PropPL5x7); 

    lcd->setFont(MSG_FONT); 
    // strcpy_P(buf,msg);
    lcd->printStr_P(ALIGN_CENTER,17, msg);
        
    sprintf_P(buf,PSTR("%2d"),value);   
    lcd->printStr(ALIGN_CENTER,17 + lcd->fontHeight() + 4, buf);

    lcd->display();
}

void MainScreen::refreshYesNo(PGM_P msg, bool yes_no) {
    char buf[TMP_BUF_LEN];

    lcd->cls();
    lcd->setFont(Small4x5PL);
    lcd->drawTriangle(5,4,2,7,5,10,1);
    // strcpy_P(buf,SAVE_n);
    // lcd->printStr(7,5, buf);
    lcd->printStr_P(7,5, SAVE_n);
    lcd->drawTriangle(5,53,2,56,5,59,1);
    lcd->printStr_P(8,54, CANC_n);
    // strcpy_P(buf,CANC_n);
    // lcd->printStr(8,54, buf);

    lcd->setFont(MSG_FONT); 
    lcd->printStr_P(ALIGN_CENTER,17, msg);
    
    if (yes_no)  lcd->printStr_P(ALIGN_CENTER,17+ lcd->fontHeight() + 4, yes_n);
    else  lcd->printStr_P(ALIGN_CENTER,17+ lcd->fontHeight() + 4, no_n);

    // lcd->printStr(ALIGN_CENTER,17 + lcd->fontHeight() + 4, buf);
    lcd->display();
}


void MainScreen::refreshYesNo(char* msg, bool yes_no) {
    char buf[TMP_BUF_LEN];

    lcd->cls();
    lcd->setFont(Small4x5PL);
    lcd->drawTriangle( 5,4,2,7,5,10,1);
    // strcpy_P(buf,SAVE_n);
    // lcd->printStr(7,5, buf);    
    lcd->printStr_P(7,5, SAVE_n);
    lcd->drawTriangle(5,53,2,56,5,59,1);
    // strcpy_P(buf,CANC_n);
    // lcd->printStr(8,54, buf);
    lcd->printStr_P(8,54, CANC_n);

    lcd->setFont(MSG_FONT); 
    // strcpy_P(buf,msg);
    // lcd->printStr(ALIGN_CENTER,17, buf);
    lcd->printStr_P(ALIGN_CENTER,17, msg);

    if (yes_no) 
        lcd->printStr_P(ALIGN_CENTER,17+ lcd->fontHeight() + 4, yes_n);
        // strcpy_P(buf,yes_n);
    else     
        lcd->printStr_P(ALIGN_CENTER,17+ lcd->fontHeight() + 4, no_n);
        // strcpy_P(buf,no_n);

    // lcd->printStr(ALIGN_CENTER,17 + lcd->fontHeight() + 4, buf);
    lcd->display();
}

