#define ST7567
#include <ArduinoLogger.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <PCF8574.h>
#include "testFont.h"
#include <Wire.h>
#ifdef ST7567
#include "ST7567_FB.h"
#endif
#ifdef U8X8 
#include <U8x8lib.h>
#endif
#include <EncButton.h>  //https://github.com/GyverLibs/EncButton


//  
#define csPin 7
#define dcPin A0
#define rstPin 9

byte EncAPin = 4;
byte EncBPin = 5;

#define BTN_S1 5
#define BTN_S2 6
#define BTN_S3 4
#define BTN_S4 7
#define BTN_S5 3
#define BTN_S6 2
#define BTN_S7 0
#define BTN_S8 1

// from PropFonts library
// #include "c64enh_font.h"

#define PCF8574_INITIAL_VALUE 0xFF

#define TEST_DISP


#define csPin 7
#define dcPin A0
#define rstPin 9

#ifdef U8X8
// U8X8_ST7567_PI_132X64_4W_SW_SPI u8x8(13, 11, 7, A6, 9);
// U8X8_ST7565_LX12864_4W_SW_SPI u8x8(13, 11, 7, A6, 9);
// U8X8_ST7567_ENH_DG128064_4W_SW_SPI u8x8(13, 11, 7, A6, 9);
// U8X8_ST7567_ENH_DG128064I_4W_SW_SPI u8x8(13, 11, 7, A6, 9);
// U8X8_ST7567_OS12864_4W_SW_SPI u8x8(13, 11, 7, A6, 9);
// U8X8_ST7567_JLX12864_4W_SW_SPI u8x8(13, 11, 7, A6, 9);
// U8X8_ST7567_122X32_4W_SW_SPI u8x8(13, 11, 7, A6, 9);

// U8X8_ST7567_PI_132X64_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7565_LX12864_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_ENH_DG128064_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_ENH_DG128064I_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_OS12864_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_JLX12864_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_122X32_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_HEM6432_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_122X32_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_64X32_4W_HW_SPI u8x8(7, A6, 9);

// U8X8_ST7567_PI_132X64_2ND_4W_HW_SPI u8x8(7, A6, 9); 
// U8X8_ST7567_JLX12864_2ND_4W_HW_SPI u8x8(7, A6, 9); 
// U8X8_ST7567_ENH_DG128064_2ND_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_ENH_DG128064I_2ND_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_OS12864_2ND_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_64X32_2ND_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_HEM6432_2ND_4W_HW_SPI u8x8(7, A6, 9);
// U8X8_ST7567_122X32_2ND_4W_HW_SPI u8x8(7, A6, 9);

//U8X8_ST7567_PI_132X64_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);  // Pax Instruments Shield, LCD_BL=6
//U8X8_ST7567_PI_132X64_4W_HW_SPI u8x8(/* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);  // Pax Instruments Shield, LCD_BL=6
//U8X8_ST7567_JLX12864_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);  
//U8X8_ST7567_JLX12864_4W_HW_SPI u8x8(/* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8); 
//U8X8_ST7567_122X32_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);  
//U8X8_ST7567_122X32_4W_HW_SPI u8x8(/* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8); 
//U8X8_ST7567_OS12864_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8);  
//U8X8_ST7567_OS12864_4W_HW_SPI u8x8(/* cs=*/ 7, /* dc=*/ 9, /* reset=*/ 8); 
//U8X8_ST7567_ENH_DG128064_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); 
//U8X8_ST7567_ENH_DG128064_4W_HW_SPI u8x8(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); 
//U8X8_ST7567_ENH_DG128064I_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); 
//U8X8_ST7567_ENH_DG128064I_4W_HW_SPI u8x8(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); 
#endif

#ifdef ST7567
/* Constructor 
U8X8_ST7565_LX12864_4W_SW_SPI(clock, data, cs, dc [, reset])
Paranms:  
Clock - /SCL/;                4; SCK_3 ; SCK  ;  D13  ; PB5
Data -  /SDA or MOSI or SI/;  5; MOSI_3; MOSI ;  D11  ; PB3
cs -    /CS/;                 1; SS2_3 ; SS2  ;  D7   ; PD7  
dc -    /A0/;                 3; A6_3  ; A6   ;  D8   ; PC6
Reset - /RES/;                2; AP9_3;  AP9  ;  D9   ; PB1
*/
ST7567_FB lcd(dcPin, rstPin, csPin);
#endif

EncButton<EB_TICK, VIRT_ENCBTN> enc;

PCF8574 pcf1(0x20);  // 40h Read; 41h write;  (20h)
PCF8574 pcf2(0x21); // 48h Read; 49h Write;  (24h)

bool pinState =true;

void setup() {
    Serial.begin(115200);
    //  Connect  GPIO I2C extender.
    logger.add (Serial, LOG_LEVEL_VERBOSE); // This will log everything on Serial
    inf << "Logger started" << endl;

    // inf <<  "PCF8574_LIB_VERSION:\t" << PCF8574_LIB_VERSION << endl;
    Wire.begin();
    SPI.begin();
    delay(500);

    // inf << "Scaning for i2c sensors..." << endl;
    // int count=0;
    // for (byte i = 0; i < 255; i++)
    // {
    //     // trace << "Check " << String(i) << " Address" << endl;
    //     Wire.beginTransmission(i);
    //     if (Wire.endTransmission() == 0) {
    //         trace << "Found i2c addrerss" << hex << i << endl;
    //         count++;
    //         delay(1);
    //     }
    // }

    //   Init display  
    // inf << "Initilize LCD Display " << endl;


    // pinMode(csPin, OUTPUT);
    // pinMode(dcPin, OUTPUT);
    // pinMode(A7, OUTPUT);

#ifdef U8X8    
    // u8x8.begin();
    // u8x8.setPowerSave(0);
    // u8x8.setContrast(150);
    // // u8x8.clearDisplay();
    // u8x8.clear();
    //
#endif    

#ifdef ST7567
    lcd.init();
    lcd.setContrast(0);
    // lcd.cls();
    lcd.setFont(testFont);
    // lcd.printStr(ALIGN_CENTER, 28, (char*)ccc);
    //   lcd.drawRectD(0,0,128,64,1);
 #endif

    //
    //  Initialize first PCF8574 chips
    //
    pcf1.begin(0xFF);
    inf << "pcf1." << hex << pcf1.getAddress() << " ";
    if (!pcf1.isConnected()) {
        inf << "not connected, " << "Err=" << dec << pcf1.lastError();
        }
    else { 
        inf << "connected !!!, ";
        trace << "pcf1." << hex << pcf1.getAddress() << " bits: "<< bin << pcf1.read8();
        }
    inf << endl;

    pcf2.begin(0x00);
    inf << "pcf2." << hex << pcf2.getAddress() << " ";
    if (!pcf2.isConnected()) {
        inf << "not connected, " << "Err=" << dec << pcf2.lastError();
        }
    else { 
        inf << "connected !!!, ";
        trace << "pcf2." << hex << pcf2.getAddress() << " bits: "<< bin << pcf2.read8();
        }
    inf << endl;

    // Read initial buttom state
    byte enc2Btn = pcf2.read8();
    inf << "Encoder state: "<< bin << enc2Btn << ", Pin A-" << (enc2Btn & (1 << EncAPin)) > 0;
    inf << ", Pin B-" << (enc2Btn & (1 << EncBPin)) > 0;

    delay(500);

}

void loop() {

    //
    //   Read button statuses
    //
    byte enc2Btn = pcf2.read8();

    //  
    //   Process Encoder
    //
    bool endBtn_A =  (enc2Btn & (1 << EncAPin)) > 0;
    bool endBtn_B = (enc2Btn & (1 << EncBPin)) > 0;

    byte action = enc.tick(endBtn_A, endBtn_B);
    if (action) {
        trace << "Encoder state: "<< bin << enc2Btn << ", Pin A-" << endBtn_A;
        trace << ", Pin B-" << endBtn_B << endl;
        trace << "Encoder Action " << action << endl;
        enc.resetState();
    }
    // inf << "Loop..." << endl;

#ifdef TEST_DISP
#ifdef U8X8
    // u8x8.setFont(u8x8_font_chroma48medium8_r);
    // u8x8.drawString(0,0,"Hello World!");
    // u8x8.drawString(0,0,"Line 0");
    // u8x8.drawString(0,8,"Line 8");
    // u8x8.drawString(0,9,"Line 9");
    //   u8x8.refreshDisplay();		// only required for SSD1606/7  
    // err << "u8x8 Error: " << u8x8.getWriteError() << endl;
#endif 

#ifdef ST7567
    const char *ccc = "Hello world";
    // lcd.drawRectD(0,0,128,64,1);
    // lcd.drawRect(18,20,127-18*2,63-20*2,1);
    lcd.setFont(testFont);
    lcd.printStr(ALIGN_CENTER, 28, (char*)ccc);
    // lcd.display();
#endif
#endif

    // delay(5000);
    // Checr encoder's status
    //enc.tick(pcf2.digitalRead(P4),pcf2.digitalRead(P5), pcf2.digitalRead(P6));

}