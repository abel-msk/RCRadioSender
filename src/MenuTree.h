#ifndef __MENU_TREE__
#define __MENU_TREE__
#ifdef ARDUINO
#include <Arduino.h>
#endif
#include "MenuData.h"
#include "ST7567_FB.h"
#include "config.h"
#include "proppl5x7_font.h"
// #include <ArduinoArray.h>
#include "ArduinoArray.h"



#define MENU_DEPTH 3
#define MENU_SCRIN_LINES 5
#ifndef  NAME_BUFF_LEN
    #define MENU_MAX_NAME_LENGHT 21 //   Moved to global configuration  config.h
#else
    #define MENU_MAX_NAME_LENGHT NAME_BUFF_LEN   // defined in config.h
#endif // ! 

#define SCREEN_SIZE_W 128 //  Y Coord
#define SCREEN_SIZE_H 64  //  X Coord
#define CURSOR_VERT_PADDING 2
#define CURSOR_LEFT_PADDING 5
#define TEXT_LEFT_PADDING 10
#define SUBMENU_PTR_POS  110

// typedef char* (*cbFunc)(byte param, char* buf);

// class MenuPos
// {
//     public:
//     byte curPageStart = 0;
//     byte selPosOnScreen = 0;
// };

typedef struct onScreenPos {
  unsigned char curPageStart;
  unsigned char selPosOnScreen;
} onScreenPos;



class MenuTree {
    private:
    // ArduinoArray<LevelMenu*>* menuStack;
    ST7567_FB* lcd;
    MenuManager* curMenu;
    onScreenPos menuPosStack[MENU_DEPTH];
    byte stackPtr = 0;
    int (*itemDataCB)(byte idx) = NULL;

    byte getItemID(byte item);

    // const uint8_t* theFont = PropPL5x7;

    public:
    // MenuTree(ST7567_FB* l):lcd(l){}
    MenuTree(ST7567_FB* l);
    void begin();
    void display();
    byte enter();
    void exit();
    void scrollUp();
    void scrollDown();
    void scrollTop();
    MenuManager* getMenu();
    void registerCB(int (*callback)(byte idx)) {
        itemDataCB = callback;
    };
};

#endif