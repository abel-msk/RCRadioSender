#ifndef __LEVEL_MENU__
#define __LEVEL_MENU__

#ifdef ARDUINO
#include <Arduino.h>
#endif

#include "ST7567_FB.h"
#include "MenuData.h"
// #include "vga2_8x15_font.h"
#include "proppl5x7_font.h"
#include "config.h"

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


class LevelMenu {
    private:
    ST7567_FB* lcd;
    // MenuManager* menu;
    byte curPageStart = 0;
    byte selPosOnScreen = 0;
    byte menuCount = 0;
    // byte screenLines = 4;
    // byte screenCols = 16;
    const uint8_t* theFont = PropPL5x7;
    //char nameBuf[MENU_MAX_NAME_LENGHT];  //   Moved to global configuration  config.h

    public:
    MenuManager* menu;

    LevelMenu(ST7567_FB* ST7567_FB_class, MenuManager* levelMenu);
    void setFont(const uint8_t *font) {theFont = font;};
    const uint8_t* getFont() {return theFont;};
    void scrollUp();
    void scrollDown();
    void scrollTop();
    void printMenu();
    MenuManager* getMenu();

    // byte getNavAction();
    // void processKey(byte keyPressed);
    // unsigned char handleNavigation(unsigned char action);
};

#endif