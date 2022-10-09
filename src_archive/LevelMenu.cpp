#include "LevelMenu.h"
#include "MenuData.h"
#include "config.h"

// #define LEVEL_MENU_DEBUG

const char EmptyStr[] = "";


//byte menuMode = Menu1.handleNavigation(getNavAction, refreshMenuDisplay);
// https://stackoverflow.com/questions/400257/how-can-i-pass-a-class-member-function-as-a-callback
//------------------------------------------------------------------------------------------------------------

LevelMenu::LevelMenu(ST7567_FB* ST7567_FB_class, MenuManager* levelMenu) {
    // lcd = ST7567_FB_class;
    // screenLines = lines;
    // screenCols = cols;
    lcd = ST7567_FB_class;
    menu = levelMenu;
    curPageStart = 0;
    selPosOnScreen = 0;
    menuCount = levelMenu->getMenuItemCount();
}

void LevelMenu::scrollUp() {
    
 #ifdef LEVEL_MENU_DEBUG   
    Serial.print(F("Scroll UP:  "));
    Serial.print(F("selPosOnScreen "));
    Serial.print(selPosOnScreen);
    Serial.print(F(", screenLines "));
    Serial.print(screenLines);
    Serial.print(F(", curPageStart "));
    Serial.println(curPageStart);
#endif

    if (selPosOnScreen < 1) {
        if ((curPageStart > 0)) {
            curPageStart --;
            menu->moveToPreviousItem();
        }
    }
    else {
        selPosOnScreen --;
        menu->moveToPreviousItem();
    }

    #ifdef LEVEL_MENU_DEBUG
        Serial.print(F("Cur Item (getCurrentItemCmdId) =  "));
        Serial.println(menu->getCurrentItemCmdId());
    #endif

    printMenu();
}

void LevelMenu::scrollDown() {

 #ifdef LEVEL_MENU_DEBUG      
    Serial.print(F("Scroll DOWN:  "));
    Serial.print(F("selPosOnScreen "));
    Serial.print(selPosOnScreen);
    Serial.print(F(", screenLines "));
    Serial.print(screenLines);
    Serial.print(F(", curPageStart "));
    Serial.print(curPageStart);
    Serial.print(F(", Item Count "));
    Serial.println(menuCount);
#endif

    if (selPosOnScreen >= MENU_SCRIN_LINES - 1 ) {   //  We are on buttom of the screen
        if ((curPageStart + selPosOnScreen) >= menuCount-1) return;

        // Shift down mwnu page by 1 line
        curPageStart++;
        // selPosOnScreen++;
    }
    else {
        if (selPosOnScreen == (MENU_SCRIN_LINES - 1)) return;
        // Move Cur selection down by 1
        selPosOnScreen++;
    }
 
    menu->moveToNextItem();
    Serial.print(F("Cur Item =  "));
    Serial.println(menu->getCurrentItemCmdId());
    // Print menu from position
    printMenu();

}

//
//  Scroll menu to top of list. Set Current to first position
//
void LevelMenu::scrollTop() {
    curPageStart = 0;
    selPosOnScreen = 0;
    printMenu();
}

//
//   Printing menu items start from curPageStart untill screen lines
//
void LevelMenu::printMenu() {

    char memBuff[NAME_BUFF_LEN];

 #ifdef LEVEL_MENU_DEBUG  
    Serial.print(F("PRINT :  "));
    Serial.print(F("selPosOnScreen "));
    Serial.print(selPosOnScreen);
    Serial.print(F(", screenLines "));
    Serial.print(MENU_SCRIN_LINES);
    Serial.print(F(", curPageStart "));
    Serial.println(curPageStart);
#endif


    lcd->cls();
    if ( theFont != NULL) { 
        lcd->setFont(theFont);
    }
    byte vertPos = 4;
    if ( vertPos < CURSOR_VERT_PADDING) vertPos = CURSOR_VERT_PADDING;
    byte fontH = lcd->fontHeight();

    // byte onScrPos =0;

    for ( byte i = curPageStart; i < curPageStart+MENU_SCRIN_LINES; i++ ) {
        menu->getItemName(memBuff, i);

        if ( vertPos  + fontH + CURSOR_VERT_PADDING <= SCREEN_SIZE_H ) {
            if ( (selPosOnScreen + curPageStart) == i) {
                 //  Print Selected item
                lcd->printStr(TEXT_LEFT_PADDING, vertPos, memBuff);
                lcd->drawRect(CURSOR_LEFT_PADDING, vertPos-CURSOR_VERT_PADDING, SCREEN_SIZE_W - (CURSOR_LEFT_PADDING*2), fontH+CURSOR_VERT_PADDING*2, 1);
            }
            // Plain menu item
            else {
                lcd->printStr(TEXT_LEFT_PADDING, vertPos, memBuff);
            }

            if (menu->itemHasChildren(i) ) {
                lcd->drawTriangle(
                    SUBMENU_PTR_POS, vertPos,
                    SUBMENU_PTR_POS + (fontH / 2)+2, vertPos + (fontH/2),
                    SUBMENU_PTR_POS, vertPos + fontH,
                    1
                );
            }

            vertPos += fontH + CURSOR_VERT_PADDING*2;
        }
    }
    lcd->display();
}


MenuManager* LevelMenu::getMenu() {
    return menu;
}

//----------------------------------------------------------------------
// Callback to convert button press to navigation action.
// byte LevelMenu::getNavAction()
// {
//     byte navAction = 0;
//     // byte currentItemHasChildren = Menu1.currentItemHasChildren();
  
// //   if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED) navAction = MENU_ITEM_PREV;
// //   else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED) navAction = MENU_ITEM_NEXT;
// //   else if (btn == BUTTON_SELECT_PRESSED || (btn == BUTTON_RIGHT_PRESSED && currentItemHasChildren)) navAction = MENU_ITEM_SELECT;
// //   //else if (btn == BUTTON_LEFT_PRESSED) navAction = MENU_BACK;
//     return navAction;
// }

