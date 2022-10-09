#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <PCF8574.h>
#include <EEPROM.h>
// #include "fonts_all.h"
// #include "testFont.h"
// #include "term2_11x16_font.h"
// #include "term2_8x10cent_font.h"
// #include "c64enh2_font.h"
//#include "term2_8x10_font.h"
// #include "term2_8x14_font.h"
// #include "vga2_8x15_font.h"

#include <EncButton.h>  //https://github.com/GyverLibs/EncButton
#include "ST7567_FB_P.h"
// #include <ArduinoLogger.h>
#include "MenuTree.h"
#include "MainScreen.h"
#include "MenuData.h"


#include <RF24.h>  // https://nRF24.github.io/RF24
#include <nRF24L01.h>
#include "config.h"
#include <printf.h>

#define DEBUG_2
// #define DEBUG_CALIBR
// #define USE_FKEYS
// #define USE_RADIO

#define ENC_LEFT 1
#define ENC_RIGHT 2
#define ENC_NONE 0

#define csPin 7
#define dcPin A0
#define rstPin 9
#define USE_HW_SPI

#define EncAPin 4
#define EncBPin 5
#define ExitBtnPin 1
#define EntBtnPin 2

// #define Fkey1Pin 
// #define Fkey2Pin 
// #define Fkey3Pin 
// #define Fkey4Pin 

#define BTN_TOUT 300
#define DISPLAY_TOUT 15000

#define RVUP_S2_Pin 6
#define RVDW_S1_Pin 5
#define LVUP_S4_Pin 7
#define LVDW_S3_Pin 4
#define RHRI_S7_Pin 0
#define RHLE_S8_Pin 1
#define LHLE_S5_Pin 3
#define LHRI_S6_Pin 2

#define RIGHT_HORIZ_PIN A7
#define RIGHT_VERT_PIN A1

#define LEFT_UP_KEYID 1
#define LEFT_DW_KEYID 2
#define RIGH_UP_KEYID 3
#define RIGH_DW_KEYID 4

#define USE_RADIO_ACK
// #define SEND_RATE 1000

#define DISP_MAIN 1
#define DISP_CHANNEL 2
#define DISP_CALIBR 3
#define DISP_MENU 4
#define DISP_PROFILE_CH 5
#define DISP_ID_CH 6
#define DISP_SLPTM_CH 7

#define DISP_KEY0_CH 8
#define DISP_KEY1_CH 9
#define DISP_KEY2_CH 10
#define DISP_KEY3_CH 11

#define DISP_SWPJS_CH 12
#define DISP_SAVE 13

#define DISP_ERROR 14


const char err_not_connect[] PROGMEM = "not connected."; 
const char coma_tab[] PROGMEM = ", \t ";
const char delim[]  PROGMEM = " | ";

const char* const string_table[] PROGMEM = { err_not_connect, coma_tab, delim };

#define print_P(i) Serial.print((__FlashStringHelper*)pgm_read_word(string_table + i))
#define print_tab  print_P(1);
#define print_delim print_P(2);

#define _getT() (millis() & 0xFFFF)
#define _checkT(x) ((millis() & 0xFFFF) - x)
#define _getVal(x,y) ((x & (1 << y)) > 0)

#define _getTop(x) (x & 0xF )
#define _getBot(x) ((x & (0xF << 4)) >> 4)

#define _setTop(x,y) ((x & 0x0F) | (y & 0xF0))
#define _setBot(x,y) ((x << 4) | (y & 0x0F))

#define _getKey(store,pos) ((store >> pos*2) & 3)
#define _setKey(store,pos,val) ( ((val & 3) << (pos*2)) | (store & ~(3 << (pos*2))) )
#define _getBoolKey(store,pos) ((store >> pos) & 1)
#define _setBoolKey(store,pos,val) ( ((val & 1) << pos) | (store & ~(1 << pos)) )


struct {
    uint16_t time;
    byte mode;
} display;

struct  Button {
    uint16_t time;
    bool state;
};

struct {
    byte drive;
    byte view;
    byte addon;
} Payload;

typedef struct EepromData {
    byte remoteId;
    byte chID;
    int16_t LVShift;
    int16_t LHShift;
    int16_t RVShift;
    int16_t RHShift;
    byte keys;
    bool swap; 
    byte sleep;
} ProfileData;

struct packet {
    int8_t cmd;
    int8_t leftVert;
    int8_t leftHoriz;
    int8_t rightVert;
    int8_t rightHoriz;
    int8_t Keys;
} sendData[1];

ProfileData profSettings;
ProfileData savedSettings;
byte profile=0;

Button U1Btns[8]; 
Button exitBtn;
Button enterBtn;
Button FKey1;
Button FKey2;
Button FKey3;
Button FKey4;

int8_t leftVert = 0;
int8_t leftHoriz = 0;
int8_t rightVert = 0;
int8_t rightHoriz =0;

EncButton<EB_TICK, VIRT_ENC> enc;
// ST7567_FB(uint8_t dc, uint8_t rst, uint8_t cs);
ST7567_FB_P lcd(dcPin, rstPin, csPin);
MenuTree  menu(&lcd);
MainScreen mainScreen(&lcd);

PCF8574 pcf1(0x20);  // 40h Read; 41h write;  (20h)
PCF8574 pcf2(0x21); // 48h Read; 49h Write;  (24h)

// RF24 radio(8,10); // CE, CSN
RF24 radio(8,10,RF24_SPI_SPEED); // CE, CSN

byte ext1Btn;
byte ext2Btn;
bool exitToMenu = false;
byte currentProffile = 0;
bool save_yes_no = false;
byte currentKeys = 0;
bool isNeedSend = false;
byte localPowerPercent = 0;


PGM_P errorMsg = NULL;

const uint64_t pipe[1] = {0xF0F0F0F0E1LL};
// int msg[1] = {1};
char ans[1] = {0};

//   Check if the button change state, 100ms ago
bool isAction( Button* btn, bool action) {
    if ((action != btn->state ) && (_checkT(btn->time) > BTN_TOUT)) {
        btn->state = action;
        btn->time = _getT();
        return true;
    }
    return false;
}

void resetBtn(Button* btn) {
    // Serial.println(F("Reset button."));
    btn->state = ! btn->state;
    btn->time = _getT();
}

void loadProfile(byte profileID) {
    EEPROM.get(1 + sizeof(EepromData)*profileID, profSettings);  
    EEPROM.get(1 + sizeof(EepromData)*profileID, savedSettings);  
    profile = currentProffile = profileID;
}

// void saveProfile(byte profileID) {
//     EEPROM.put(1 + sizeof(EepromData)*profileID, profSettings); 
// }

void saveProfile() {
    EEPROM.put(1 + sizeof(EepromData)*profile, profSettings); 
    EEPROM.put(0, currentProffile);  
    savedSettings.chID = profSettings.chID;  
    savedSettings.remoteId = profSettings.remoteId;
    savedSettings.LVShift = profSettings.LVShift;
    savedSettings.LHShift = profSettings.LHShift;
    savedSettings.RVShift = profSettings.RVShift;
    savedSettings.RHShift = profSettings.RHShift;
    savedSettings.keys = profSettings.keys;
    savedSettings.swap = profSettings.swap;
    savedSettings.sleep = profSettings.sleep;
    // Serial.println(F("Save profile."));
}
 
void saveProfileID() {
    EEPROM.put(0, profile);  
    currentProffile = profile;
}


byte checkEncoder() {
    enc.tick(_getVal(ext2Btn,EncAPin), _getVal(ext2Btn,EncBPin));
    if (enc.left()) {
        enc.resetState();
        ext2Btn |= (1 << EncAPin);
        ext2Btn |= (1 << EncBPin);
        pcf2.write8(ext2Btn);
        return ENC_LEFT;
    }
    else if (enc.right()) {
        enc.resetState();  
        ext2Btn |= (1 << EncAPin);
        ext2Btn |= (1 << EncBPin);
        pcf2.write8(ext2Btn);
        return ENC_RIGHT;
    }
    return ENC_NONE;
}


int getCurrentValue(byte index) {

    switch(index) {
        case MENU_PROF :
            return profile;
            break;
        case MENU_CHID :
            return profSettings.chID;
            break;    
        case MENU_RID :
            return profSettings.remoteId;
            break;
        case MENU_CALLB :
            return -1;
            break;
        case MENU_SLPTM :
            return profSettings.sleep;
            break;
        case MENU_LUPKEY :
            return _getKey(profSettings.keys,0);
            break;
        case MENU_LDWKEY :
            return _getKey(profSettings.keys,1);
            break;
        case MENU_RUPKEY :
            return _getKey(profSettings.keys,2);
            break;
        case MENU_RDWKEY :
            return _getKey(profSettings.keys,3);
            break;
        case MENU_SWPJS :
            return profSettings.swap;
            break;
        case MENU_SAVEPRF :
            return profile;
            break;
        default:
            return -1;
    }

}


void setup() {
    display.mode = DISP_MAIN;
    display.time = _getT();
    
    Serial.begin(115200);
    SPI.begin();
    printf_begin();
    //  Start logger
    // logger.add (Serial, LOG_LEVEL_VERBOSE); // This will log everything on Serial
    // inf << F("Logger started") << endl;

    //
    //   Initialize EEPROM and Load profiles
    //
    EEPROM.get(0, profile);  
    currentProffile = profile;

    Serial.print(F("Load profile: "));
    Serial.println(profile);

    if (profile > MAX_PROFILES ) {
        profile = 0;
        //  Clear all profiles
        profSettings.remoteId = 0;
        profSettings.chID = 5;
        profSettings.LVShift = 0 ;
        profSettings.LHShift = 0 ;
        profSettings.RVShift = 0 ;
        profSettings.RHShift = 0 ;
        // profSettings.keys = 0 ;
        _setBoolKey(profSettings.keys,0,0);
        _setBoolKey(profSettings.keys,1,1);
        _setBoolKey(profSettings.keys,2,2);
        _setBoolKey(profSettings.keys,3,3);
        profSettings.swap = true ;
        profSettings.sleep = 3;

        EEPROM.put(0, profile); 
        for (byte i; i < MAX_PROFILES; i++ ) {
            EEPROM.put(1 + sizeof(EepromData)*i, profSettings); 
        }
    }
    else {
        loadProfile(profile);

#ifdef DEBUG_2
        Serial.print(F("RemoteId: ")); Serial.print(profSettings.remoteId);
        Serial.print(F(", Keys: ")); Serial.print(profSettings.remoteId);
        Serial.print(F(", Swap: ")); Serial.print(profSettings.remoteId);
        Serial.print(F(", Sleep: ")); Serial.print(profSettings.remoteId);
        Serial.println();
#endif        
    } 

    //
    //  Initialize first PCF8574 chips
    //
    pcf1.begin(0xFF);
    // inf << F("pcf1.") << hex << pcf1.getAddress() << " ";
    Serial.print(F("pcf1. Addr "));
    Serial.print(pcf1.getAddress(),HEX);


    if (!pcf1.isConnected()) {
        Serial.println(err_not_connect);
        // inf << F("not connected, ") << F("Err=") << dec << pcf1.lastError();
        }
    else { 
        ext1Btn = pcf1.read8();
        Serial.print(F(", Val "));
        Serial.println(ext1Btn,BIN);
        }

    //
    //  Initialize second PCF8574 chips
    //
    pcf2.begin(0xFF);
    Serial.print(F("pcf2. Addr "));
    Serial.print(pcf2.getAddress(),HEX);    
    // inf << F("pcf2.") << hex << pcf2.getAddress() << " ";

    if (!pcf2.isConnected()) {
         Serial.println(err_not_connect);
        // inf << F("not connected, ") << F("Err=") << dec << pcf2.lastError();
        }
    else { 
        // inf << F("connected !!!, ");
        ext2Btn = pcf2.read8();
        Serial.print(F(", Val "));
        Serial.println(ext2Btn,BIN);
        // trace << F("pcf2.") << hex << pcf2.getAddress() << F(" bits: ")<< bin << ext2Btn;
        }
    // inf << endl;

    //
    //  Initialize  buttons
    //
    for (int i = 0; i  < 8; i++ ) {
        U1Btns[i].state = _getVal(ext1Btn,i);
        U1Btns[i].time = _getT();
    }

    //
    //  Initialize  ST7567 Display
    //
    lcd.init();
    lcd.setContrast(0);
    lcd.cls();

    // lcd.printStr(ALIGN_CENTER, 28, (char*) "Starting...");
    lcd.display();
    //  Turn on Display Light
    pcf2.write(0,0);

    //  Initialize menu
    delay(500);

    menu.begin();
    menu.registerCB(getCurrentValue);
    mainScreen.refreshMain(profile, profSettings.chID, profSettings.remoteId,36,20,40);

    #ifdef USE_RADIO
    radio.begin();  // Инициализация модуля NRF24L01
    // radio.setChannel(5); // Обмен данными будет вестись на пятом канале (2,405 ГГц)
    radio.setChannel(profSettings.chID);
    radio.setDataRate (RF24_1MBPS); // Скорость обмена данными 1 Мбит/сек
    radio.setPALevel(RF24_PA_HIGH); // Выбираем высокую мощность передатчика (-6dBm)
    radio.setRetries(2,2);
    radio.enableDynamicPayloads();
    radio.openWritingPipe(0x787878787800 + profSettings.remoteId); 
    // radio.openWritingPipe(0x7878787878LL); // Открываем трубу с уникальным ID
    #ifdef DEBUG_RADIO
    radio.printPrettyDetails();
    #endif
    // radio.setRetries(2,5);
    #endif
}

void loop() {

 

    //
    //   Read button statuses
    //
    ext1Btn = pcf1.read8();
    ext2Btn = pcf2.read8();
    isAction(&enterBtn,! _getVal(ext2Btn,EntBtnPin));
    isAction(&exitBtn,! _getVal(ext2Btn,ExitBtnPin));

    //
    //  Joystic position
    //

    leftVert = map(analogRead(A3) + profSettings.LVShift, 0, 1023, 0, MOVE_RANGE*2) - MOVE_RANGE;
    if ( sendData[0].leftVert != leftVert ) { isNeedSend = true; sendData[0].leftVert = leftVert; }
    leftHoriz  = map(analogRead(A2) + profSettings.LHShift, 0, 1023, 0, MOVE_RANGE*2) - MOVE_RANGE;
    if ( sendData[0].leftHoriz != leftHoriz ) { isNeedSend = true; sendData[0].leftHoriz = leftHoriz; }
    rightVert = map(analogRead(RIGHT_VERT_PIN) + profSettings.RVShift, 0, 1023, 0, MOVE_RANGE*2) - MOVE_RANGE;
    if ( sendData[0].rightVert != rightVert ) { isNeedSend = true ; sendData[0].rightVert = rightVert; }
    rightHoriz = map(analogRead(RIGHT_HORIZ_PIN) + profSettings.RHShift, 0, 1023,  0, MOVE_RANGE*2) - MOVE_RANGE;
    if ( sendData[0].rightHoriz != rightHoriz ) { isNeedSend = true; sendData[0].rightHoriz = rightHoriz; }


    //=======================================================
    //
    //  Check Function keys
    //

    //  Key status was changed from old value
  
    #ifdef USE_FKEYS
    if ( isAction(&FKey1,digitalRead(3))  !=  _Bool(_getBoolKey(sendData[0].Keys, _getKey(profSettings.keys,0))))  {  // SL2
        isNeedSend = true;
        // resetBtn(&FKey1); 
        //  Real key  position for value store is redefined by profile (profSettings.keys)
        _setBoolKey(sendData[0].Keys,_getKey(profSettings.keys,0),FKey1.state);
    }
    if ( isAction(&FKey2,digitalRead(4))  != _Bool(_getBoolKey(sendData[0].Keys, _getKey(profSettings.keys,0))))  { // SL1
        isNeedSend = true;
        // resetBtn(&FKey2);
        _setBoolKey(sendData[0].Keys,_getKey(profSettings.keys,1),FKey2.state);
    }
    if (isAction(&FKey3,digitalRead(5)) != _Bool(_getBoolKey(sendData[0].Keys, _getKey(profSettings.keys,0)))) { // SR2
        isNeedSend = true;
        // resetBtn(&FKey3);
        _setBoolKey(sendData[0].Keys,_getKey(profSettings.keys,2),FKey3.state);
    }
    if ( isAction(&FKey4,digitalRead(6)) != _Bool(_getBoolKey(sendData[0].Keys, _getKey(profSettings.keys,0)))) {// SR1
        isNeedSend = true;
        // resetBtn(&FKey4);
        _setBoolKey(sendData[0].Keys,_getKey(profSettings.keys,3),FKey4.state);
    }
    #endif

    //=======================================================
    //
    //  Send data to receiver.
    //

    if (isNeedSend) {

        #ifdef DEBUG_2
        Serial.print(F("LV: ")); Serial.print(sendData[0].leftVert); print_tab;
        Serial.print(F("LH: ")); Serial.print(sendData[0].leftHoriz); print_tab;
        Serial.print(F("RV: ")); Serial.print(sendData[0].rightVert); print_tab;
        Serial.print(F("RH: ")); Serial.print(sendData[0].rightHoriz); print_tab;
        Serial.println();

        #ifdef USE_FKEYS
        Serial.print(F("Key1: "));  Serial.print (_getKey(profSettings.keys, 0)); print_delim; Serial.print(_getBoolKey(sendData[0].Keys, _getKey(profSettings.keys,0))); print_tab;
        Serial.print(F("Key2: "));  Serial.print (_getKey(profSettings.keys, 1)); print_delim; Serial.print(_getBoolKey(sendData[0].Keys, _getKey(profSettings.keys,1))); print_tab;
        Serial.print(F("Key3: "));  Serial.print (_getKey(profSettings.keys, 2)); print_delim; Serial.print(_getBoolKey(sendData[0].Keys, _getKey(profSettings.keys,2))); print_tab;
        Serial.print(F("Key4: "));  Serial.print (_getKey(profSettings.keys, 3)); print_delim; Serial.print(_getBoolKey(sendData[0].Keys, _getKey(profSettings.keys,3))); print_tab;
        Serial.println();
        #endif
        #endif

        #ifdef USE_RADIO
        radio.stopListening();
        if (radio.write(sendData, sizeof(sendData[0])))  {
            // // Serial.print( msg[0] );
            // // Serial.println("  transmitted successfully !!");
            // if (radio.isAckPayloadAvailable()) {
            //     radio.read(ans,sizeof(ans));  

            //     //  Get feedback data from remote board
            //      #ifdef DEBUG_2
            //         Serial.print("Receive ACK. ");
            //         Serial.println(ans[1]);
            //      #endif
            // }
            // Serial.println(F("Pkt send."));
        }
        else {   //  Error writing
            print_P(0); Serial.println();
            errorMsg = err_not_connect;
            display.mode = DISP_ERROR;
            display.time = _getT();
            }

        #endif
        isNeedSend = false;
    }


    //
    //   Check calibration buttons 
    // 
    for (int i = 0; i  < 8; i++ ) {
        //  Btn switchd state  more then 100ms ago and new state true
        if ( isAction(&U1Btns[i], _getVal(ext1Btn,i)) &  (! U1Btns[i].state)) {

            #ifdef DEBUG_2
                Serial.print(F("Calib key"));
                Serial.print(i); print_tab;
                Serial.print(U1Btns[i].state); 
                Serial.println();
            #endif
            // trace << F("Status ") << dec << U1Btns[i].state << F(", I= ")<< i <<  endl;

            switch (i) {
                case RVUP_S2_Pin:              //   Right up  -
                    if ( profSettings.RVShift >= INPUT_RANGE * (-1) )
                        profSettings.RVShift -= CALB_STEP;
                    break;
                case RVDW_S1_Pin:   //  Right down +
                    if ( profSettings.RVShift <= INPUT_RANGE )
                        profSettings.RVShift += CALB_STEP;
                    break;
                case LVUP_S4_Pin:       //  Left UP  - 
                    if ( profSettings.LVShift >= INPUT_RANGE * (-1) )
                        profSettings.LVShift -= CALB_STEP;
                    break;
                case LVDW_S3_Pin:      //   Left DOWN +
                    if ( profSettings.LVShift <= INPUT_RANGE )
                        profSettings.LVShift += CALB_STEP;
                    break;
                case RHRI_S7_Pin:    //  Right horizontal  +
                    if ( profSettings.RHShift <=  INPUT_RANGE) {
                        profSettings.RHShift += CALB_STEP;
                    }
                    break;
                case RHLE_S8_Pin:    //  Right horizontal  -
                    if ( profSettings.RHShift >= INPUT_RANGE * (-1))
                        profSettings.RHShift -= CALB_STEP;
                    break;
                case LHLE_S5_Pin:      //    Lefh horizontal left - 
                    if ( profSettings.LHShift >= INPUT_RANGE * (-1))
                        profSettings.LHShift -= CALB_STEP;
                    break;
                case LHRI_S6_Pin:     //    Lefh horizontal rhght +
                    if ( profSettings.LHShift <=  INPUT_RANGE)
                        profSettings.LHShift += CALB_STEP;
                    break;
            }

            display.mode = DISP_CALIBR;
            display.time = _getT();
            exitToMenu = false;

            resetBtn(&U1Btns[i]);

            #ifdef DEBUG_CALIBR
            Serial.print(F("LV Shift: ")); Serial.print(profSettings.LVShift); print_tab;
            Serial.print(F("LH Shift: ")); Serial.print(profSettings.LHShift); print_tab; 
            Serial.print(F("RV Shift: ")); Serial.print(profSettings.RVShift); print_tab;
            Serial.print(F("RH Shift: ")); Serial.print(profSettings.RHShift); print_tab;
            Serial.println();
            #endif

        }
    }

    //=======================================================
    //
    //  Refresh data on main screen  
    //
    if (display.mode == DISP_MAIN) {

        //  мин 2.8 макс 4.2 питание 4.5
        if ( analogRead(A6) )  
        localPowerPercent = map(analogRead(A6) * (5.0 / 1023.0),2.8,4.5,0,122);

        // Serial.print(F("A6="));
        // Serial.print(localPowerPercent); print_delim;
        // Serial.println(analogRead(A6));

        mainScreen.refreshMain(profile, 
            profSettings.chID, 
            profSettings.remoteId,
            36,  // Temperature
            20,  // Remote Power
            localPowerPercent < 100?localPowerPercent:100); // Local Power

        //
        // Enter BTN pressed
        //
        if ( enterBtn.state) {
            // trace << F("Enter button pressed.") << endl;
            display.mode = DISP_MENU;
            display.time = _getT();
            resetBtn(&enterBtn);
        }
    }

    //=======================================================
    //
    //  Menu Error screen
    //

    if (display.mode == DISP_ERROR) {
        if ( errorMsg == NULL) {
            if ( exitToMenu ) display.mode = DISP_MENU;
            else  display.mode = DISP_MAIN;
            display.time = _getT();
        }
        else {
            mainScreen.refreshMessage(errorMsg,0,false);
            //
            // Enter BTN pressed
            //
            if ((_checkT(display.time) > DISPLAY_TOUT)  | (exitBtn.state)) {
                // trace << F("Cancel button pressed.") << endl;
                if ( exitToMenu ) display.mode = DISP_MENU;
                else  display.mode = DISP_MAIN;
                display.time = _getT();
                resetBtn(&exitBtn);
            }
        }
    }


    //=======================================================
    //
    //  Menu display screen mode
    //

    //else
    else if (display.mode == DISP_MENU) {

        menu.display();

        switch (checkEncoder()) {
            case ENC_LEFT:
                menu.scrollDown();
                break;
            case ENC_RIGHT:
                menu.scrollUp();
                break;
            default:
                break;
        }

        //  Enter BTN 
        if (enterBtn.state) {

            byte disp = menu.enter();  

            // trace << F("Enter to menu: ") << dec << disp << endl;
            switch (disp) {
                case 0:
                    // menu.enter();
                    // display.mode = DISP_PROFILE_CH;
                    break;
                case MENU_PROF :
                    display.mode = DISP_PROFILE_CH;
                    break;
                 case MENU_CHID :
                    display.mode = DISP_CHANNEL;
                    break;                   
                case MENU_RID :
                    display.mode = DISP_ID_CH;
                    break;
                case MENU_CALLB :
                    display.mode = DISP_CALIBR;
                    exitToMenu = true;
                    break;
                case MENU_SLPTM :
                    display.mode = DISP_SLPTM_CH;
                    break;
                case MENU_LUPKEY :
                    display.mode = DISP_KEY0_CH;
                    break;
                case MENU_LDWKEY :
                    display.mode = DISP_KEY1_CH;
                    break;
                case MENU_RUPKEY :
                    display.mode = DISP_KEY2_CH;
                    break;
                case MENU_RDWKEY :
                    display.mode = DISP_KEY3_CH;
                    break;
                case MENU_SWPJS :
                    display.mode = DISP_SWPJS_CH;
                    break;
                case MENU_SAVEPRF :
                    display.mode = DISP_SAVE;
                    break;
                default:
                    // menu.enter();
                    break;
                display.time = _getT();
            }
            resetBtn(&enterBtn);
        }

        //   Exit BTN pressed
        if ( exitBtn.state ) {
            // trace << F("Exit button pressed.") <<  dec << menu.getMenu()->currentMenuHasParent() << endl;
            if (menu.getMenu()->currentMenuHasParent() > 0) {
                menu.exit();
            }
            else {
                // trace << F("Switch to MAIN Display")<< endl;
                display.mode = DISP_MAIN;
                display.time = _getT();
                // (DISP_MAIN);
            }
            resetBtn(&exitBtn);
        }
    }

    //=======================================================
    //
    //  Position correction display mode 
    //
    else if (display.mode == DISP_CALIBR) {
        mainScreen.refreshCalibration(profSettings.LHShift,profSettings.LVShift,profSettings.RHShift,profSettings.RVShift);

        if ((_checkT(display.time) > DISPLAY_TOUT) |
            (exitBtn.state ))
         {
            if ( exitToMenu) {
                display.mode = DISP_MENU;
                display.time = _getT();
                // switchDisplay(DISP_MENU);
            }
            else {
                display.mode = DISP_MENU;
                display.time = _getT();
                // switchDisplay(DISP_MAIN);
            }
            resetBtn(&exitBtn);
        }
    }

    //=======================================================
    //
    //  Change and load current profile 
    //
    else if (display.mode == DISP_PROFILE_CH) {

        mainScreen.refreshMessage(PSTR("Cur profile"),profile);

        switch (checkEncoder()) {
            case ENC_LEFT:
                if (profile > 0 ) profile--;
                break;
            case ENC_RIGHT:
                if (profile < MAX_PROFILES) profile++;
                break;
        }

        if(enterBtn.state) {
            // trace << F("DISP_PROFILE_CH. Enter pressed.") << endl;
            display.mode = DISP_MENU;
            display.time = _getT();
            // switchDisplay(DISP_MENU);
            resetBtn(&enterBtn);
            currentProffile = profile;
            loadProfile(profile);     //  Load data for new profile ID
        }
        //  Exit BTN pressed
        else if ( exitBtn.state ) {
            // trace << F("DISP_PROFILE_CH. Exit pressed.") << endl;
            // switchDisplay(DISP_MENU);
            display.mode = DISP_MENU;
            display.time = _getT();
            resetBtn(&exitBtn);
            profile = currentProffile;  //  Reset cur profile it to saved
        }

    }
    //=======================================================
    //
    //  Radio channel ID change display mode
    //
    else if ( display.mode == DISP_CHANNEL ) {
        mainScreen.refreshMessage(PSTR("Channel ID"),profSettings.chID);

        switch (checkEncoder()) {
            case ENC_LEFT:
                if (profSettings.chID > 0)  profSettings.chID--;
                break;
            case ENC_RIGHT:
                if (profSettings.chID < 127) profSettings.chID++;
                break;
        }
               //  Exit BTN pressed
        if(enterBtn.state) {
            // trace << F("DISP_ID_CH. Enter pressed.") << endl;
            display.mode = DISP_MENU;
            display.time = _getT();
            // switchDisplay(DISP_MENU);
            resetBtn(&enterBtn);
            savedSettings.chID = profSettings.chID;
        }              
        else if ( exitBtn.state ) {
            display.mode = DISP_MENU;
            display.time = _getT();
            // switchDisplay(DISP_MENU);
            resetBtn(&exitBtn);
            profSettings.chID = savedSettings.chID;  //  Reset cur profile it to saved
        }

    }

    //=======================================================
    //
    //  Remote ID change display mode
    //
    else if ( display.mode == DISP_ID_CH ) {
        mainScreen.refreshMessage(PSTR("Remote ID"),profSettings.remoteId);

        switch (checkEncoder()) {
            case ENC_LEFT:
                if (profSettings.remoteId > 0)  profSettings.remoteId--;
                break;
            case ENC_RIGHT:
                if (profSettings.remoteId < 255) profSettings.remoteId++;
                break;
        }
               //  Exit BTN pressed
        if(enterBtn.state) {
            // trace << F("DISP_ID_CH. Enter pressed.") << endl;
            display.mode = DISP_MENU;
            display.time = _getT();
            // switchDisplay(DISP_MENU);
            resetBtn(&enterBtn);
            savedSettings.remoteId = profSettings.remoteId;
        }              
        else if ( exitBtn.state ) {
            display.mode = DISP_MENU;
            display.time = _getT();
            // switchDisplay(DISP_MENU);
            resetBtn(&exitBtn);
            profSettings.remoteId = savedSettings.remoteId;  //  Reset cur profile it to saved
        }

    }

    //=======================================================
    //
    //   Set sleep timer display mode
    //
    else if ( display.mode  == DISP_SLPTM_CH) {
        mainScreen.refreshMessage(PSTR("Sleep timer"),profSettings.sleep);

        if(enterBtn.state) {
            // trace << F("DISP_SLPTM_CH. Enter pressed.") << endl;
            display.mode = DISP_MENU;
            display.time = _getT();
            // switchDisplay(DISP_MENU);
            resetBtn(&enterBtn);
            savedSettings.sleep = profSettings.sleep;
        }              
        else if ( exitBtn.state ) {
            display.mode = DISP_MENU;
            display.time = _getT();
            // switchDisplay(DISP_MENU);
            resetBtn(&exitBtn);
            profSettings.sleep = savedSettings.sleep;  //  Reset cur profile it to saved
        }
    }

    //=======================================================
    //
    //   Swap Left/right joystick  display mode
    //
    else if ( display.mode  == DISP_SWPJS_CH) {
        mainScreen.refreshMessage(PSTR("Swap Joystics"),profSettings.swap);
        switch (checkEncoder()) {
            case ENC_LEFT:
            case ENC_RIGHT:
                save_yes_no = ! save_yes_no;
                break;
            default:
                break;
        }

        if(enterBtn.state) {
            // trace << F("DISP_SWPJS_CH. Enter pressed.") << endl;
            display.mode = DISP_MENU;
            display.time = _getT();
            // switchDisplay(DISP_MENU);
            resetBtn(&enterBtn);
            savedSettings.swap = profSettings.swap;
        }
        else if (exitBtn.state ) {
            display.mode = DISP_MENU;
            display.time = _getT();
            resetBtn(&exitBtn);
            profSettings.swap = savedSettings.swap; 
        }

    }

    //=======================================================
    //
    //   Set Key X display mode
    //
    else if (( display.mode  == DISP_KEY0_CH) || 
            ( display.mode  == DISP_KEY1_CH) ||
            ( display.mode  == DISP_KEY2_CH) ||
            ( display.mode  == DISP_KEY3_CH))
    
     {
        
        byte key = 0;
        switch (display.mode) {
            case DISP_KEY0_CH:
                key = 0;
                mainScreen.refreshMessage(PSTR("Left top btn code"),_getKey(profSettings.keys,key));           
                break;
            case DISP_KEY1_CH:
                key = 1;
                mainScreen.refreshMessage(PSTR("Left bot btn code"),_getKey(profSettings.keys,key));             
                break;
            case DISP_KEY2_CH:
                mainScreen.refreshMessage(PSTR("Right top btn code"),_getKey(profSettings.keys,key));            
                key = 2;
                break;           
            case DISP_KEY3_CH: 
                mainScreen.refreshMessage(PSTR("Right bot btn code"),_getKey(profSettings.keys,key));                   
                key = 3;
                break;                                                          
        }

        switch (checkEncoder()) {
            case ENC_LEFT:
                if (_getKey(profSettings.keys,key) > 0 ) 
                    _setKey(profSettings.keys,key,_getKey(profSettings.keys,key)-1);
            case ENC_RIGHT:
                if (_getKey(profSettings.keys,key) < 3 ) 
                    _setKey(profSettings.keys,key,_getKey(profSettings.keys,key)+1);
                break;
            default:
                break;
        }        

        if (enterBtn.state) {
            // trace << F("DISP_KEYx_CH. Enter pressed.") << endl;
            display.mode = DISP_MENU;
            display.time = _getT();
            // switchDisplay(DISP_MENU);
            resetBtn(&enterBtn);
            savedSettings.keys = profSettings.keys;
        }
        else if (exitBtn.state ) {
            display.mode = DISP_MENU;
            display.time = _getT();
            resetBtn(&exitBtn);
            profSettings.keys = savedSettings.keys;  //  Reset cur profile it to saved
        }
    }
    //=======================================================
    //
    //   Save profile display mode
    
    else if (display.mode == DISP_SAVE) {
        mainScreen.refreshYesNo(PSTR("Save profile"),save_yes_no);
        switch (checkEncoder()) {
            case ENC_LEFT:
            case ENC_RIGHT:
                save_yes_no = ! save_yes_no;
                break;
            default:
                break;
        }

        if(enterBtn.state) {
            // trace << F("DISP_SAVE. Enter pressed.") << endl;
            display.mode = DISP_MENU;
            display.time = _getT();
            // switchDisplay(DISP_MENU);
            resetBtn(&enterBtn);
            if ( save_yes_no ) {
                //  Save current ProfSetting as new profile& 
                saveProfile();
            }
            else {
                loadProfile(currentProffile);
            }
        }
        else if (exitBtn.state ) {
            display.mode = DISP_MENU;
            display.time = _getT();
            resetBtn(&exitBtn);
        }
    }
}


