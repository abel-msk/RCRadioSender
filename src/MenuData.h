#ifndef _sampleMenu_
#define _sampleMenu_
#include "MenuManager.h"
#include <avr/pgmspace.h>

/*

Generated using LCD Menu Builder at https://lcd-menu-bulder.cohesivecomputing.co.uk/
For more information, visit https://www.cohesivecomputing.co.uk/hackatronics/arduino-lcd-menu-library/

All our hackatronics projects are free for personal use. If you find them helpful or useful, please consider
making a small donation to our hackatronics fund using the donate buttons on our web pages. Thank you.
		
*/

enum sampleMenuCommandId
{
  MENU_Back = 0,
  MENU_PROF,
  MENU_CHID,
  MENU_RID,
  MENU_CALLB,
  MENU_SLPTM,
  MENU_KCODE,
  MENU_LUPKEY,
  MENU_LDWKEY,
  MENU_RUPKEY,
  MENU_RDWKEY,
  MENU_SWPJS,
  MENU_SAVEPRF
};

PROGMEM const char sampleMenu_back[] = "Back";
PROGMEM const char sampleMenu_exit[] = "Exit";

PROGMEM const char sampleMenu_6_1[] = "Left top Key";
PROGMEM const char sampleMenu_6_2[] = "Left bot Key";
PROGMEM const char sampleMenu_6_3[] = "Right top Key";
PROGMEM const char sampleMenu_6_4[] = "Right bot Key";
PROGMEM const MenuItem sampleMenu_List_6[] = {{MENU_LUPKEY, sampleMenu_6_1}, {MENU_LDWKEY, sampleMenu_6_2}, {MENU_RUPKEY, sampleMenu_6_3}, {MENU_RDWKEY, sampleMenu_6_4}, {MENU_Back, sampleMenu_back}};

PROGMEM const char sampleMenu_1[] = "Load Profile";
PROGMEM const char sampleMenu_2[] = "Set channel";
PROGMEM const char sampleMenu_3[] = "Set remote ID";
PROGMEM const char sampleMenu_4[] = "Callibration";
PROGMEM const char sampleMenu_5[] = "Sleep time";
PROGMEM const char sampleMenu_6[] = "Key Codes";
PROGMEM const char sampleMenu_7[] = "Swap Joystic";
PROGMEM const char sampleMenu_8[] = "Save cur profile";
PROGMEM const MenuItem sampleMenu_Root[] = {{MENU_PROF, sampleMenu_1}, {MENU_CHID, sampleMenu_2}, {MENU_RID, sampleMenu_3}, {MENU_CALLB, sampleMenu_4}, {MENU_SLPTM, sampleMenu_5}, {MENU_KCODE, sampleMenu_6, sampleMenu_List_6, menuCount(sampleMenu_List_6)}, {MENU_SWPJS, sampleMenu_7}, {MENU_SAVEPRF, sampleMenu_8}, {MENU_Back, sampleMenu_exit}};

/*
case MENU_PROF :
	break;
case MENU_CHID :
	break;
case MENU_RID :
	break;
case MENU_CALLB :
	break;
case MENU_SLPTM :
	break;
case MENU_LUPKEY :
	break;
case MENU_LDWKEY :
	break;
case MENU_RUPKEY :
	break;
case MENU_RDWKEY :
	break;
case MENU_SWPJS :
	break;
case MENU_SAVEPRF :
	break;
*/

/*
<?xml version="1.0"?>
<RootMenu xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">
  <Config IdPrefix="MENU_" VarPrefix="sampleMenu" UseNumbering="false" IncludeNumberHierarchy="false"
          MaxNameLen="21" MenuBackFirstItem="false" BackText="Back" ExitText="Exit" AvrProgMem="true" />
<MenuItems>
	<Item Id="PROF" Name="Load Profile"/>
    <Item Id="CHID" Name="Set channel"/>
    <Item Id="RID" Name="Set remote ID"/>
    <Item Id="CALLB" Name="Callibration"/>
	<Item Id="SLPTM" Name="Sleep time"/>
	<Item Id="KCODE" Name="Key Codes">	
    	<MenuItems>
      	  	<Item Id="LUPKEY" Name="Left top Key"/>
      		<Item Id="LDWKEY" Name="Left bot Key"/>
      		<Item Id="RUPKEY" Name="Right top Key"/>
			<Item Id="RDWKEY" Name="Right bot Key"/>
    	</MenuItems>
	</Item>
	<Item Id="SWPJS" Name="Swap Joystic"/>
	<Item Id="SAVEPRF" Name="Save cur profile"/>
</MenuItems>
</RootMenu>
*/
#endif