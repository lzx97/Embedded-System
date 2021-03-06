#include "DataStructs.h"
#include <stdio.h>
#include "TFTKeypad.h"
#include "Bool.h"


// IMPORTANT: Elegoo_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com
//void drawDefaultMode();
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

//void drawAnnunciate(); // Should be covered by using headerfile
//void drawMenu();

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pinheader at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xFF00

// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x0440      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

/******************* UI details */
int mode = 0; // 0 = Default, 1 = Menu, 2=Annunciate
#define MODE_BUTTON_X 60
#define MODE_BUTTON_Y 40
#define MODE_BUTTON_W 90
#define MODE_BUTTON_H 38
#define MODE_BUTTON_SPACING_X 30
#define MODE_BUTTON_SPACING_Y 20
#define MODE_BUTTON_TEXTSIZE 2

#define MENU_BUTTON_X 58
#define MENU_BUTTON_Y 165
#define MENU_BUTTON_W 115
#define MENU_BUTTON_H 50
#define MENU_BUTTON_SPACING_X 8
#define MENU_BUTTON_SPACING_Y 12
#define MENU_BUTTON_TEXTSIZE 2.8

#define ACKN_BUTTON_X 120
#define ACKN_BUTTON_Y 260
#define ACKN_BUTTON_W 220
#define ACKN_BUTTON_H 50
#define ACKN_BUTTON_SPACING_X 30
#define ACKN_BUTTON_SPACING_Y 8
#define ACKN_BUTTON_TEXTSIZE 3

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

//Touch For New ILI9341 TP
#define TS_MINX 70
#define TS_MAXX 920

#define TS_MINY 120
#define TS_MAXY 900
// We have a status line for like, is FONA working
#define STATUS_X 65
#define STATUS_Y 10


Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Elegoo_GFX_Button buttons[4];
Elegoo_GFX_Button menubuttons[10];
Elegoo_GFX_Button acknbuttons[1];
/* create the buttons */
// buttonlabels[num_buttons][length of array]
char buttonlabels[4][20] = {"Menu", "Annunc.", "Display", "Exp1"};
uint16_t buttoncolors[4] = {ILI9341_NAVY, ILI9341_NAVY, ILI9341_NAVY, ILI9341_NAVY};

char menubuttonlabels[10][20] = {"BP: ON", "Temp: ON", "Pulse: ON", "Resp: ON", "EKG: ON", "BP: OFF", "Temp: OFF", "Pulse:OFF", "Resp: OFF", "EKG: OFF"};
uint16_t menubuttoncolors[10] = {ILI9341_LIGHTGREY, ILI9341_LIGHTGREY, ILI9341_LIGHTGREY, ILI9341_LIGHTGREY,ILI9341_LIGHTGREY,
                             ILI9341_DARKGREY, ILI9341_DARKGREY,ILI9341_DARKGREY, ILI9341_DARKGREY,ILI9341_DARKGREY};

char acknbuttonlabels[1][20] = {"Acknowl."};
uint16_t acknbuttoncolors[1] = {ILI9341_GREEN};

uint16_t identifier; // global variable to be reached from all functions

void setupDisplay(void *tftStruct) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  identifier = tft.readID();
  if (identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if (identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if (identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  } else if (identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if (identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if (identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if (identifier == 0x0101)
  {
    identifier = 0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier = 0x9341;
  }
  tft.begin(identifier);
  tft.setRotation(0);
  drawDefaultMode(tftStruct);
}


void drawDefaultMode(void *tftStruct) {
  TFTData *dData = (TFTData*) tftStruct;
  *(dData->justPressed) = FALSE;
  tft.fillScreen(BLACK);
  // create default mode buttons
  for (uint8_t row = 0; row < 2; row++) {
    for (uint8_t col = 0; col < 2; col++) {
      buttons[col + row * 2].initButton(&tft, MODE_BUTTON_X + col * (MODE_BUTTON_W + MODE_BUTTON_SPACING_X),
                                        MODE_BUTTON_Y + row * (MODE_BUTTON_H + MODE_BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                        MODE_BUTTON_W, MODE_BUTTON_H, ILI9341_WHITE, buttoncolors[col + row * 2], ILI9341_WHITE,
                                        buttonlabels[col + row * 2], MODE_BUTTON_TEXTSIZE);
      buttons[col + row * 2].drawButton();
    }
  }
}
int bpon;
int tempon;
int pulseon;
int respon;
int ekgon;

int bpvar;
int tempvar;
int pulsevar;
int respvar;
int ekgvar;

void drawMenu(void *tftStruct) {
  TFTData *dData = (TFTData*) tftStruct;
  *(dData->justPressed) = FALSE;
  bpon = *(dData->bpSelection);
  tempon = *(dData->tempSelection);
  pulseon = *(dData->pulseSelection);
  respon = *(dData->respSelection);
  ekgon = *(dData->EKGSelection);

  // create default mode buttons
  bpvar = ((bpon == 1) ? 0 : 5);
  tempvar = ((tempon == 1) ? 1 : 6);
  pulsevar = ((pulseon == 1) ? 2 : 7);
  respvar = ((respon == 1) ? 3 : 8);
  ekgvar = ((ekgon == 1) ? 4 : 9);
 
  menubuttons[bpvar].initButton(&tft,  MENU_BUTTON_X,
                 MENU_BUTTON_Y,    // x, y, w, h, outline, fill, text
                  MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[bpvar], ILI9341_WHITE,
                  menubuttonlabels[bpvar], MENU_BUTTON_TEXTSIZE);
  menubuttons[bpvar].drawButton();

  menubuttons[tempvar].initButton(&tft,  MENU_BUTTON_X,
                 MENU_BUTTON_Y+2*(MENU_BUTTON_H+MENU_BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[tempvar], ILI9341_WHITE,
                  menubuttonlabels[tempvar], MENU_BUTTON_TEXTSIZE);
  menubuttons[tempvar].drawButton();

  menubuttons[pulsevar].initButton(&tft,  MENU_BUTTON_X+(MENU_BUTTON_W+MENU_BUTTON_SPACING_X),
                 MENU_BUTTON_Y,    // x, y, w, h, outline, fill, text
                  MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[pulsevar], ILI9341_WHITE,
                  menubuttonlabels[pulsevar], MENU_BUTTON_TEXTSIZE);
  menubuttons[pulsevar].drawButton();

  menubuttons[respvar].initButton(&tft,  MENU_BUTTON_X+(MENU_BUTTON_W+MENU_BUTTON_SPACING_X),
                 MENU_BUTTON_Y+2*(MENU_BUTTON_H+MENU_BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[respvar], ILI9341_WHITE,
                  menubuttonlabels[respvar], MENU_BUTTON_TEXTSIZE);
  menubuttons[respvar].drawButton();

  menubuttons[ekgvar].initButton(&tft,  MENU_BUTTON_X+(MENU_BUTTON_W+MENU_BUTTON_SPACING_X)/2,
                 MENU_BUTTON_Y+(MENU_BUTTON_H+MENU_BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  2*MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[ekgvar], ILI9341_WHITE,
                  menubuttonlabels[ekgvar], MENU_BUTTON_TEXTSIZE);
  menubuttons[ekgvar].drawButton();
}
#define MINPRESSURE 10
#define MAXPRESSURE 1000

unsigned long startTime;

void displayLoop(void *tftStruct) {
  TFTData *dData = (TFTData*) tftStruct;
  if(*(dData->globalTime) % *(dData->displayInterval) == 0){ 
      *(dData->justPressed) = TRUE;
  }
  while (millis() < (*(dData->timeNow))  + 1000) {
    TFTData *dData = (TFTData*) tftStruct;
    if (*(dData->displayOff)){
        tft.fillScreen(BLACK);
    } else {
    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);

    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if (*(dData->justPressed) == TRUE) {
      drawDefaultMode(tftStruct);
      if (mode == 1) {
        drawMenu(tftStruct);
      } else if (mode == 2) {
        drawAnnunciate(tftStruct);
      } else if (mode == 3) {
        drawDisplay(tftStruct);
      }
      *(dData->justPressed) = FALSE;
    }

    int dx;
    int dy;
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      // scale from 0->1023 to tft.width
      p.y = (map(p.y, TS_MINX, TS_MAXX, tft.width(), 0));
      p.x = (tft.height() - map(p.x, TS_MINY, TS_MAXY, tft.height(), 0)); //
      // Mapping to match actual screen
      dx = (unsigned int16_t) p.y;
      dy = (unsigned int32_t) p.x;
      dx = (unsigned int32_t) (dx - 6) * 232 / 210;
      dy = (unsigned int32_t) (dy + 5) * 320 / 345;
      //Serial.print(dx);    Serial.print(", ");    Serial.println(dy);
    } else {
      dx = -100;
      dy = -200;
      p.z = -1;
    }


    // go thru all the buttons, checking if they were pressed
    for (uint8_t b = 0; b < 4; b++) {
      if (buttons[b].contains(dx, dy)) {
        //Serial.print("Pressing: "); Serial.println(buttonlabels[b]);
        buttons[b].press(true);  // tell the button it is pressed
        //Serial.print(dx);   Serial.print(", ");  Serial.println(dy);
        *(dData->justPressed) = TRUE;
      } else {
        buttons[b].press(false);  // tell the button it is NOT pressed
      }
    }
    if (mode == 1) {
      for (uint8_t b = 0; b < 5; b++) {
        if (menubuttons[b].contains(dx, dy)) {
          //Serial.print("Pressing: "); Serial.println(menubuttonlabels[b]);
          menubuttons[b].press(true);  // tell the button it is pressed
          //Serial.print(dx);     Serial.print(", ");     Serial.println(dy);
          *(dData->justPressed) = TRUE;
        } else {
          menubuttons[b].press(false);  // tell the button it is NOT pressed
        }
      }
    } else if (mode == 2) {
      if (acknbuttons[0].contains(dx, dy)) {
        //Serial.print("Pressing: "); Serial.println(acknbuttonlabels[0]);
        acknbuttons[0].press(true);  // tell the button it is pressed
        //Serial.print(dx);    Serial.print(", ");    Serial.println(dy);
        *(dData->justPressed) = TRUE;
      } else {
        acknbuttons[0].press(false);  // tell the button it is NOT pressed
      }
    }

    // now we can ask the buttons if their state has changed
    for (uint8_t b = 0; b < 4; b++) {
      if (buttons[b].justReleased()) {
        // Serial.print("Released: "); Serial.println(b);
        buttons[b].drawButton();  // draw normal
      }

      if (buttons[b].justPressed()) {
        buttons[b].drawButton(true);  // draw invert!
        buttons[b].press(false);
        if (b < 4) {
          mode = b + 1; // Set mode to default 0 = Default, 1 = Menu, 2=Annunciate
        }
        delay(100);
      }
    }
    if (mode == 1) {
      for (uint8_t b = 0; b < 10; b++) {
        if (menubuttons[b].justReleased()) {
          // Serial.print("Released: "); Serial.println(b);
          menubuttons[b].drawButton();  // draw normal
        }

        if (menubuttons[b].justPressed()) {
          menubuttons[b].press(false);
          menubuttons[b].drawButton(true);  // draw invert!
          //Serial.print("This is the value of b: "); Serial.println(b);
          if (b == 0 || b == 5) {
            bpon = ((bpon == 0) ? 1 : 0);
          } else if (b == 1 || b == 6) {
            tempon = ((tempon == 0) ? 1 : 0);
          } else if (b == 2 || b == 7) {
            pulseon = ((pulseon == 0) ? 1 : 0);
          } else if (b == 3 ||b == 8) {
            respon = ((respon == 0) ? 1 : 0);
          } else if (b ==4 || b == 9) {
            ekgon = ((ekgon == 0) ? 1 : 0);
          }
          *(dData->bpSelection) = bpon;
          *(dData->tempSelection) = tempon;
          *(dData->pulseSelection) = pulseon;
          *(dData->respSelection) = respon;
          *(dData->EKGSelection) = ekgon;

          mode = 1; // 0 = Default, 1 = Menu, 2=Annunciate
          delay(100);
        }
      }
    }
    if (mode == 2) {
      if (acknbuttons[0].justReleased()) {
        // Serial.print("Released: "); Serial.println(b);
        acknbuttons[0].drawButton();  // draw normal
      }

      if (acknbuttons[0].justPressed()) {
        acknbuttons[0].press(false);
        acknbuttons[0].drawButton(true);  // draw invert!
        // Check if alarm is ringing
        // If so, acknowledge
        // Else, do nothing
        if (*(dData->sysAlarm)) {
          *(dData->sysAlarmAcknowledge) = TRUE;
          *(dData->sysAlarmTimer) = 0;
          *(dData->sysAlarm) = FALSE;
          *(dData->sysWarning) = TRUE;
        }
        if (*(dData->tempAlarm)) {
          *(dData->tempAlarmAcknowledge) = TRUE;
          *(dData->tempAlarmTimer) = 0;
          *(dData->tempAlarm) = FALSE;
          *(dData->tempWarning) = TRUE;
        }
        if (*(dData->pulseAlarm)) {
          *(dData->pulseAlarmAcknowledge) = TRUE;
          *(dData->pulseAlarmTimer) = 0;
          *(dData->pulseAlarm) = FALSE;
          *(dData->pulseWarning) = TRUE;
        }
        if (*(dData->respAlarm)) {
          *(dData->respAlarmAcknowledge) = TRUE;
          *(dData->respAlarmTimer) = 0;
          *(dData->respAlarm) = FALSE;
        }
        delay(100);
      }
    }
   if (mode == 2){
    flashAlarms(tftStruct);

   }
  }
  }
}

void drawAnnunciate(void *tftStruct) {
  TFTData *dData = (TFTData*) tftStruct;
  *(dData->justPressed) = FALSE;
  // create default mode buttonstft.setCursor(0, 0);
  // print low and high presure
  if (*(dData->bpSelection)) {
    tft.setCursor(0, 150);
    if (*(dData->sysAlarm)) {
      tft.setTextColor(RED);
    } else if (*(dData->sysWarning)) {
      tft.setTextColor(ORANGE);
    } else {
      tft.setTextColor(GREEN);
    }
    tft.print((*(dData->bloodPressCorrectedBuf))[0]);
    tft.print((*(dData->bloodPressCorrectedBuf))[1]);
    tft.print((*(dData->bloodPressCorrectedBuf))[2]); 
    tft.setTextColor(WHITE);     tft.print("/");
    if (*(dData->diasWarning)) {
      tft.setTextColor(ORANGE);
    } else {
      tft.setTextColor(GREEN);
    }
    tft.print((*(dData->bloodPressCorrectedBuf))[24]);
    tft.print((*(dData->bloodPressCorrectedBuf))[25]);
    tft.print((*(dData->bloodPressCorrectedBuf))[26]); 
    tft.setTextColor(WHITE);  tft.println(" mm Hg");

  } else {
    
    tft.setCursor(0, 150);
    tft.setTextColor(WHITE);    tft.print("--");
    tft.setTextColor(WHITE);    tft.print("/");
    tft.setTextColor(WHITE);    tft.print("--");
    tft.setTextColor(WHITE);    tft.println(" mm Hg");
  }

  // print temp
  if (*(dData->tempSelection)) {
    if (*(dData->tempAlarm)) {
      tft.setTextColor(RED);
    } else if (*(dData->tempWarning)){
      tft.setTextColor(ORANGE);
    } else {
      tft.setTextColor(GREEN);
    }
    tft.print((*(dData->tempCorrectedBuf))[0]);
    tft.print((*(dData->tempCorrectedBuf))[1]);
    tft.print((*(dData->tempCorrectedBuf))[2]);
    tft.print((*(dData->tempCorrectedBuf))[3]);
    tft.setTextColor(WHITE);
    tft.print("C ");

  } else {
    tft.setTextColor(WHITE);
    tft.print("--.-");
    tft.setTextColor(WHITE);
    tft.print("C ");
  }

  // print pulserate
  if (*(dData->pulseSelection)) {
    if (*(dData->pulseAlarm)) {
      tft.setTextColor(RED);
    } else if (*(dData->pulseWarning)){
      tft.setTextColor(ORANGE);
    } else {
      tft.setTextColor(GREEN);
    }
    tft.print((*(dData->pulseRateCorrectedBuf))[0]);
    tft.print((*(dData->pulseRateCorrectedBuf))[1]);
    tft.print((*(dData->pulseRateCorrectedBuf))[2]);
    tft.setTextColor(WHITE);
    tft.println(" BPM ");
  } else {
    tft.setTextColor(WHITE);
    tft.print("---");
    tft.setTextColor(WHITE);
    tft.println(" BPM ");
  }

  // print respiratory rate
  if (*(dData->respSelection)) {
    if (*(dData->respAlarm)) {
      tft.setTextColor(RED);
    } else {
      tft.setTextColor(GREEN);
    }
    tft.print((*(dData->respirationRateCorrectedBuf))[0]);
    tft.print((*(dData->respirationRateCorrectedBuf))[1]);
    tft.setTextColor(WHITE);
    tft.println(" RR ");
  } else {
    tft.setTextColor(WHITE);
    tft.print("--");
    tft.setTextColor(WHITE);
    tft.println(" RR ");
  }

  
  // print battery
  if (*(dData->batteryLow)) {
    tft.setTextColor(RED);
  } else {
    tft.setTextColor(GREEN);
  }
  tft.print((*(dData->batteryState))[0]);
  tft.print((*(dData->batteryState))[1]);
  tft.print((*(dData->batteryState))[2]);
  tft.setTextColor(WHITE);
  tft.print(" Charges");

  acknbuttons[0].initButton(&tft,  ACKN_BUTTON_X,
                            ACKN_BUTTON_Y,    // x, y, w, h, outline, fill, text
                            ACKN_BUTTON_W, ACKN_BUTTON_H, ILI9341_WHITE, acknbuttoncolors[0], ILI9341_WHITE,
                            acknbuttonlabels[0], ACKN_BUTTON_TEXTSIZE);
  acknbuttons[0].drawButton();
}

void flashAlarms(void *tftStruct){
    TFTData *dData = (TFTData*) tftStruct;
    tft.setCursor(0, 150);
    //Serial.println("We are in Flash");
    // Flash systolic
    /*if(*(dData->sysWarning) && *(dData->bpSelection)){
        if(millis() - *(dData->lastSysFlash) > 250){
          *(dData->lastSysFlash) = millis();
          if (*(dData->sysFlash)){
              *(dData->sysFlash) = FALSE;
              tft.setTextColor(BLACK); // Black text on black background = good camouflage
          } else {
              *(dData->sysFlash) = TRUE;
              tft.setTextColor(ORANGE);
          }
        }
        tft.print((*(dData->bloodPressCorrectedBuf))[0]);
        tft.print((*(dData->bloodPressCorrectedBuf))[1]);
        tft.print((*(dData->bloodPressCorrectedBuf))[2]); 
        tft.setTextColor(WHITE);    tft.print("/");
}
*/
    // Flash diastolic
    /*if(*(dData->diasWarning) && *(dData->bpSelection)){
        if(millis() - *(dData->lastDiasFlash) > 250){
          *(dData->lastDiasFlash) = millis();
          if (*(dData->diasFlash)){
              *(dData->diasFlash) = FALSE;
              tft.setTextColor(BLACK);
          } else {
              *(dData->diasFlash) = TRUE;
               tft.setTextColor(ORANGE);
          }
        } else {
          tft.setTextColor(ORANGE);
        }
        tft.print((*(dData->bloodPressCorrectedBuf))[24]);
        tft.print((*(dData->bloodPressCorrectedBuf))[25]);
        tft.print((*(dData->bloodPressCorrectedBuf))[26]); 
        tft.setTextColor(WHITE);    tft.print("/");
        tft.setTextColor(WHITE);    tft.println(" mm Hg");
    } else {
      tft.print("\n");
    }*/
    /************************************************************
     * Flashing shit
     ***********************************************************/
        if(*(dData->sysWarning) && *(dData->bpSelection)||
           *(dData->diasWarning) && *(dData->bpSelection)||
           *(dData->tempWarning) && *(dData->tempSelection)||
           *(dData->pulseWarning) && *(dData->pulseSelection)){
          float timeNow = millis();
          
         //Flash systolic 
         if(*(dData->sysWarning) && *(dData->bpSelection)){
         if(timeNow - *(dData->lastSysFlash) > 250){
          *(dData->lastSysFlash) = millis();
          if (*(dData->sysFlash)){
              *(dData->sysFlash) = FALSE;
              tft.setTextColor(BLACK); // Black text on black background = good camouflage
          } else {
              *(dData->sysFlash) = TRUE;
              tft.setTextColor(ORANGE);
          }
        }
        tft.setTextSize(2);
        tft.setCursor(0, 150);
        tft.print((*(dData->bloodPressCorrectedBuf))[0]);
        tft.print((*(dData->bloodPressCorrectedBuf))[1]);
        tft.print((*(dData->bloodPressCorrectedBuf))[2]); 
        //tft.setTextColor(WHITE);    tft.print("/");
         }
        //flash diastolic
         if(*(dData->diasWarning) && *(dData->bpSelection)){ 
        if(timeNow - *(dData->lastDiasFlash) > 250){
          *(dData->lastDiasFlash) = millis();
          if (*(dData->diasFlash)){
              *(dData->diasFlash) = FALSE;
              tft.setTextColor(BLACK);
          } else {
              *(dData->diasFlash) = TRUE;
               tft.setTextColor(ORANGE);
          }
        }
        tft.setTextSize(2);
        tft.setCursor(48, 150);
        tft.print((*(dData->bloodPressCorrectedBuf))[24]);
        tft.print((*(dData->bloodPressCorrectedBuf))[25]);
        tft.print((*(dData->bloodPressCorrectedBuf))[26]); 
        //tft.setTextColor(WHITE);    tft.println(" mm Hg");

         }
        //Flash Temp 
        if(*(dData->tempWarning) && *(dData->tempSelection)){
        if((timeNow - *(dData->lastTempFlash) > 500)  ){
          *(dData->lastTempFlash) = millis();
          if (*(dData->tempFlash)){
              *(dData->tempFlash) = FALSE;
              tft.setTextColor(BLACK);
          } else {
              *(dData->tempFlash) = TRUE;
               tft.setTextColor(ORANGE);
          }

          if(*dData->tempAlarm){
              (*dData->tempWarning)=FALSE;
              }
        tft.setTextSize(2);
        tft.setCursor(0, 166);
        tft.print((*(dData->tempCorrectedBuf))[0]);
        tft.print((*(dData->tempCorrectedBuf))[1]);
        tft.print((*(dData->tempCorrectedBuf))[2]);
        tft.print((*(dData->tempCorrectedBuf))[3]);
    }
        }
        //Flash Pulse
        if(*(dData->pulseWarning) && *(dData->pulseSelection)){
          
        if(timeNow - *(dData->lastPulseFlash) > 1000){
            *(dData->lastPulseFlash) = millis();
            if (*(dData->pulseFlash)){
                *(dData->pulseFlash) = FALSE;
                //tft.setTextColor(BLACK);
                tft.setTextColor(BLACK);
            } else {
                *(dData->pulseFlash) = TRUE;
                 tft.setTextColor(ORANGE); 
            } 

            if(*dData->pulseAlarm){
              (*dData->pulseWarning)=FALSE;
              }
        
        }
        tft.setTextSize(2);
        tft.setCursor(72, 166);
        tft.print((*(dData->pulseRateCorrectedBuf))[0]);
        tft.print((*(dData->pulseRateCorrectedBuf))[1]);
        tft.print((*(dData->pulseRateCorrectedBuf))[2]);
        }

    }
    
}
void drawDisplay(void *tftStruct) {
  TFTData *dData = (TFTData*) tftStruct;
  *(dData->justPressed) = FALSE;
    tft.setTextColor(WHITE);
  // create default mode buttonstft.setCursor(0, 0);
  // print low and high presure
  if (*(dData->bpSelection)) {
    tft.setCursor(0, 150);
  //Diastolic pressure

  tft.print("Sys. Press.:");
    tft.print((*(dData->bloodPressCorrectedBuf))[0]);
    tft.print((*(dData->bloodPressCorrectedBuf))[1]);
    tft.print((*(dData->bloodPressCorrectedBuf))[2]); 
  tft.println("mmHg");
    //Systolic pressure
  tft.print("Dias. Press.:");
    tft.print((*(dData->bloodPressCorrectedBuf))[24]);
    tft.print((*(dData->bloodPressCorrectedBuf))[25]);
    tft.print((*(dData->bloodPressCorrectedBuf))[26]); 
  tft.println("mmHg");

  } else {
    
    tft.setCursor(0, 150);    tft.print("Sys. Press.:");

  tft.print("--");  tft.println("mmHg");
    tft.print("Dia. Press.: ");
  tft.print("--");  tft.println("mmHg");
   
  }

  // print temp
  if (*(dData->tempSelection)) {
  tft.print("Body Temp:   ");
    tft.print((*(dData->tempCorrectedBuf))[0]);
    tft.print((*(dData->tempCorrectedBuf))[1]);
    tft.print((*(dData->tempCorrectedBuf))[2]);
    tft.print((*(dData->tempCorrectedBuf))[3]);
    tft.println(" C");

  } else {
    tft.print("--.-");
    tft.print("C ");
  }

  // print pulserate
  if (*(dData->pulseSelection)) {
  tft.print("Pulse Rate: ");
    tft.print((*(dData->pulseRateCorrectedBuf))[0]);
    tft.print((*(dData->pulseRateCorrectedBuf))[1]);
    tft.print((*(dData->pulseRateCorrectedBuf))[2]);
    tft.println(" BPM");
  } else {
    tft.print("---");
    tft.println(" BPM");
  }

  // print respiratory rate
  if (*(dData->respSelection)) {
  tft.print("Resp. Rate:   ");
    tft.print((*(dData->respirationRateCorrectedBuf))[0]);
    tft.print((*(dData->respirationRateCorrectedBuf))[1]);
    tft.println(" RR");
  } else {
    tft.print("--");
    tft.println(" RR");
  }

  if (*(dData->EKGSelection)) {
    tft.print("EKG:  ");
    tft.print((*(dData->freqBuf))[0]);
    tft.println(" Hz ");
  }
  else {
    tft.print("--");
    tft.print(" Hz ");
  }
}

