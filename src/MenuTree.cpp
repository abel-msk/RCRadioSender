#include "MenuTree.h"

// #include "seg72_12x21dig_font.h"
// #include "digi2_19x15_font.h"
// #include "testfont.h"

// https://www.cohesivecomputing.co.uk/hackatronics/arduino-lcd-menu-library/
// MenuManager theMenu(sampleMenu_Root, menuCount(sampleMenu_Root));

//#define LEVEL_MENU_DEBUG

MenuTree::MenuTree(ST7567_FB* l) {
    lcd = l;
    curMenu = new MenuManager(sampleMenu_Root, menuCount(sampleMenu_Root));
    stackPtr = 0;
    menuPosStack[stackPtr].curPageStart = 0;
    menuPosStack[stackPtr].selPosOnScreen = 0;
}

void MenuTree::begin() {

    // menuCount = curMenu->getMenuItemCount();

 #ifdef LEVEL_MENU_DEBUG  
    Serial.print(F("BEGIN:  "));
    Serial.print(F("selPosOnScreen "));
    Serial.print(menuPosStack[stackPtr].curPageStart);
    Serial.print(F(", curPageStart "));
    Serial.print(menuPosStack[stackPtr].curPageStart);
    Serial.print(F(", screenLines "));
    Serial.println(MENU_SCRIN_LINES);    
#endif
}

MenuManager* MenuTree::getMenu()  {
    return curMenu;
}


byte MenuTree::getItemID(byte item) {
    return pgm_read_byte(&(curMenu->getMenuItem()[item].id));
}

void MenuTree::display() {

    char memBuff[NAME_BUFF_LEN];
    lcd->cls();
    lcd->setFont(PropPL5x7); 

//  #ifdef LEVEL_MENU_DEBUG  
//     Serial.print(F("PRINT :  "));
//     Serial.print(F("selPosOnScreen "));
//     Serial.print(menuPosStack[stackPtr].selPosOnScreen);
//     Serial.print(F(", curPageStart "));
//     Serial.println(menuPosStack[stackPtr].curPageStart);
// #endif

    byte vertPos = 4;
    if ( vertPos < CURSOR_VERT_PADDING) vertPos = CURSOR_VERT_PADDING;
    byte fontH = lcd->fontHeight();

    for ( byte i = menuPosStack[stackPtr].curPageStart; i < menuPosStack[stackPtr].curPageStart+MENU_SCRIN_LINES; i++ ) {
        curMenu->getItemName(memBuff, i);

        if ( vertPos  + fontH + CURSOR_VERT_PADDING <= SCREEN_SIZE_H ) {
            //  Print menu item
            lcd->printStr(TEXT_LEFT_PADDING, vertPos, memBuff); 
            // Add menu Item data
            if ( itemDataCB != NULL ) {
                int vl = itemDataCB(getItemID(i));
                // Serial.print(F("CB return = "));
                // // Serial.println(value);
                // sprintf_P(memBuff,PSTR("%2d"),vl);
                if ( vl != -1 ) {
                    sprintf_P(memBuff,PSTR("%2d"),vl);
                    // Serial.println(memBuff);
                    lcd->printStr(90, vertPos, memBuff); 
                }
                
            }

            //   If current item is current
            if ( (menuPosStack[stackPtr].selPosOnScreen + menuPosStack[stackPtr].curPageStart) == i) {
                lcd->drawRect(CURSOR_LEFT_PADDING, vertPos-CURSOR_VERT_PADDING, SCREEN_SIZE_W - (CURSOR_LEFT_PADDING*2), fontH+CURSOR_VERT_PADDING*2, 1);
            }

            if (curMenu->itemHasChildren(i) ) {
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


byte MenuTree::enter() {

    if (curMenu->currentItemHasChildren() == 1) {

        //  ERROR: Cur menu depth exeed MENU_DEPTH
        if ( stackPtr >= MENU_DEPTH ) return 0;

        stackPtr++;
        menuPosStack[stackPtr].curPageStart=0;
        menuPosStack[stackPtr].selPosOnScreen=0;

#ifdef LEVEL_MENU_DEBUG  

        Serial.print(F("selPosOnScreen "));
        Serial.print(menuPosStack[stackPtr].selPosOnScreen);
        Serial.print(F(", curPageStart "));
        Serial.print(menuPosStack[stackPtr].curPageStart);
        Serial.print(F(", stackPtr "));
        Serial.println(stackPtr);  
#endif

        curMenu->descendToChildMenu();

        display();
        return 0;
    }
     
    return curMenu->getCurrentItemCmdId();
}

void MenuTree::exit() {

    if (stackPtr > 0) {
        // delete menuPos;
        stackPtr--;
        // menuPos = stack[stackPtr];
        curMenu->ascendToParentMenu();

#ifdef LEVEL_MENU_DEBUG  
        Serial.print(F("Exit submenu : "));
        Serial.print(F("selPosOnScreen "));
        Serial.print(menuPosStack[stackPtr].selPosOnScreen);
        Serial.print(F(", curPageStart "));
        Serial.print(menuPosStack[stackPtr].curPageStart);
        Serial.print(F(", stackPtr "));
        Serial.println(stackPtr);   

        Serial.print(F(", Has Parent "));
        Serial.println(curMenu->currentMenuHasParent());     
#endif

    }
    display();
}

void MenuTree::scrollUp() {
    
 #ifdef LEVEL_MENU_DEBUG   
    Serial.print(F("Scroll UP:  "));
    Serial.print(F("selPosOnScreen "));
    Serial.print(menuPosStack[stackPtr].selPosOnScreen);
    Serial.print(F(", curPageStart "));
    Serial.println(menuPosStack[stackPtr].curPageStart);
#endif

    if (menuPosStack[stackPtr].selPosOnScreen < 1) {
        if ((menuPosStack[stackPtr].curPageStart > 0)) {
            menuPosStack[stackPtr].curPageStart --;
            curMenu->moveToPreviousItem();
        }
    }
    else {
        menuPosStack[stackPtr].selPosOnScreen --;
        curMenu->moveToPreviousItem();
    }

    #ifdef LEVEL_MENU_DEBUG
        Serial.print(F("Cur Item (getCurrentItemCmdId) =  "));
        Serial.println(curMenu->getCurrentItemCmdId());
    #endif

    display();
}

void MenuTree::scrollDown() {
#ifdef LEVEL_MENU_DEBUG      
    Serial.print(F("Scroll DOWN:  "));
    Serial.print(F("selPosOnScreen "));
    Serial.print(menuPosStack[stackPtr].selPosOnScreen);
    Serial.print(F(", curPageStart "));
    Serial.println(menuPosStack[stackPtr].curPageStart);
#endif

    if (menuPosStack[stackPtr].selPosOnScreen >= MENU_SCRIN_LINES - 1 ) {   //  We are on buttom of the screen
        if ((menuPosStack[stackPtr].curPageStart + menuPosStack[stackPtr].selPosOnScreen) >= curMenu->getMenuItemCount()-1) return;

        // Shift down mwnu page by 1 line
        menuPosStack[stackPtr].curPageStart++;
        // selPosOnScreen++;
    }
    else {
        if (menuPosStack[stackPtr].selPosOnScreen == (MENU_SCRIN_LINES - 1)) return;
        // Move Cur selection down by 1
        menuPosStack[stackPtr].selPosOnScreen++;
    }
 
    curMenu->moveToNextItem();
#ifdef LEVEL_MENU_DEBUG       
    Serial.print(F("Cur Item =  "));
    Serial.println(curMenu->getCurrentItemCmdId());
#endif
    // Print menu from position
    display();
}

void MenuTree::scrollTop() {
    menuPosStack[stackPtr].curPageStart = 0;
    menuPosStack[stackPtr].selPosOnScreen = 0;
    display();
}

