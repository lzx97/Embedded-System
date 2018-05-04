#include "DataStructs.h"
#include <stdio.h>
#include "TFTKeypad.h"


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
#define ORANGE  0xFD20

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

#define MENU_BUTTON_X 120
#define MENU_BUTTON_Y 160
#define MENU_BUTTON_W 200
#define MENU_BUTTON_H 38
#define MENU_BUTTON_SPACING_X 30
#define MENU_BUTTON_SPACING_Y 28
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
Elegoo_GFX_Button menubuttons[6];
Elegoo_GFX_Button acknbuttons[1];
/* create the buttons */
// buttonlabels[num_buttons][length of array]
char buttonlabels[4][20] = {"Menu", "Annunc.", "Exp1", "Exp2"};
uint16_t buttoncolors[4] = {ILI9341_NAVY, ILI9341_NAVY, ILI9341_NAVY, ILI9341_NAVY};

char menubuttonlabels[6][20] = {"BP: ON", "Temp: ON", "Pulse: ON", "BP: OFF", "Temp: OFF", "Pulse:OFF"};
uint16_t menubuttoncolors[6] = {ILI9341_LIGHTGREY, ILI9341_LIGHTGREY, ILI9341_LIGHTGREY, ILI9341_DARKGREY,
                                ILI9341_DARKGREY, ILI9341_DARKGREY
                               };

char acknbuttonlabels[1][20] = {"Acknowl."};
uint16_t acknbuttoncolors[1] = {ILI9341_GREEN};

uint16_t identifier; // global variable to be reached from all functions

void setupDisplay(void *keyPadStruct) {
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
  drawDefaultMode(keyPadStruct);
}


void drawDefaultMode(void *keyPadStruct) {
  TFTData *dData = (TFTData*) keyPadStruct;

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

int bpvar = 0;
int tempvar = 1;
int pulsevar = 2;

void drawMenu(void *keyPadStruct) {
  TFTData *dData = (TFTData*) keyPadStruct;
  bpon = *(dData->bpSelection);
  tempon = *(dData->tempSelection);
  pulseon = *(dData->pulseSelection);

  // create default mode buttons
  bpvar = ((bpon == 1) ? 0 : 3);
  tempvar = ((tempon == 1) ? 1 : 4);
  pulsevar = ((pulseon == 1) ? 2 : 5);

  menubuttons[bpvar].initButton(&tft,  MENU_BUTTON_X,
                                MENU_BUTTON_Y,    // x, y, w, h, outline, fill, text
                                MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[bpvar], ILI9341_WHITE,
                                menubuttonlabels[bpvar], MENU_BUTTON_TEXTSIZE);
  menubuttons[bpvar].drawButton();

  menubuttons[tempvar].initButton(&tft,  MENU_BUTTON_X,
                                  MENU_BUTTON_Y + MENU_BUTTON_H + MENU_BUTTON_SPACING_Y, // x, y, w, h, outline, fill, text
                                  MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[tempvar], ILI9341_WHITE,
                                  menubuttonlabels[tempvar], MENU_BUTTON_TEXTSIZE);
  menubuttons[tempvar].drawButton();

  menubuttons[pulsevar].initButton(&tft,  MENU_BUTTON_X,
                                   MENU_BUTTON_Y + 2 * (MENU_BUTTON_H + MENU_BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                   MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[pulsevar], ILI9341_WHITE,
                                   menubuttonlabels[pulsevar], MENU_BUTTON_TEXTSIZE);
  menubuttons[pulsevar].drawButton();
}
#define MINPRESSURE 10
#define MAXPRESSURE 1000
int pressed = 1;

unsigned long startTime;

void displayLoop(void *keyPadStruct) {
  
  startTime = millis();
  while(millis() < startTime + 10000){
  //Serial.print("Start time is ");
  //Serial.println(startTime);
  //Serial.print(F("Current time is "));
  //Serial.println(millis());
  TFTData *dData = (TFTData*) keyPadStruct;
  TSPoint p = ts.getPoint();
  digitalWrite(13, HIGH);
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (pressed == 1) {
    drawDefaultMode(keyPadStruct);
    if (mode == 1) {
      drawMenu(keyPadStruct);
    } else if (mode == 2) {
      drawAnnunciate(keyPadStruct);
    }
    pressed = 0;
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
    Serial.print(dx);    Serial.print(", ");    Serial.println(dy);
  }


  // go thru all the buttons, checking if they were pressed
  for (uint8_t b = 0; b < 4; b++) {
    if (buttons[b].contains(dx, dy)) {
      Serial.print("Pressing: "); Serial.println(buttonlabels[b]);
      buttons[b].press(true);  // tell the button it is pressed
      Serial.print(dx);   Serial.print(", ");  Serial.println(dy);
      pressed = 1;
    } else {
      buttons[b].press(false);  // tell the button it is NOT pressed
    }
  }
  if (mode == 1) {
    for (uint8_t b = 0; b < 3; b++) {
      if (menubuttons[b].contains(dx, dy)) {
        Serial.print("Pressing: "); Serial.println(menubuttonlabels[b]);
        menubuttons[b].press(true);  // tell the button it is pressed
        Serial.print(dx);     Serial.print(", ");     Serial.println(dy);
        pressed = 1;
      } else {
        menubuttons[b].press(false);  // tell the button it is NOT pressed
      }
    }
  } else if (mode == 2) {
    if (acknbuttons[0].contains(dx, dy)) {
      Serial.print("Pressing: "); Serial.println(acknbuttonlabels[0]);
      acknbuttons[0].press(true);  // tell the button it is pressed
      Serial.print(dx);    Serial.print(", ");    Serial.println(dy);
      pressed = 1;
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
    for (uint8_t b = 0; b < 6; b++) {
      if (menubuttons[b].justReleased()) {
        // Serial.print("Released: "); Serial.println(b);
        menubuttons[b].drawButton();  // draw normal
      }

      if (menubuttons[b].justPressed()) {
        menubuttons[b].press(false);
        menubuttons[b].drawButton(true);  // draw invert!
        if (b == 0 || b == 3) {
          bpon = ((bpon == 0) ? 1 : 0);
        } else if (b == 1 || b == 4) {
          tempon = ((tempon == 0) ? 1 : 0);
        } else if (b == 2 || b == 5) {
          pulseon = ((pulseon == 0) ? 1 : 0);
        }
        *(dData->bpSelection) = bpon;
        *(dData->tempSelection) = tempon;
        *(dData->pulseSelection) = pulseon;
        delay(100);
        mode = 1; // 0 = Default, 1 = Menu, 2=Annunciate
        //drawMenu();
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
        *(dData->alarmAcknowledge) = TRUE;
        *(dData->alarmTimer) = 0;
        *(dData->sysAlarm) = FALSE;

      }
      delay(100);
    }
  }
}
}

void drawAnnunciate(void *keyPadStruct) {
  TFTData *dData = (TFTData*) keyPadStruct;
  // create default mode buttonstft.setCursor(0, 0);
  // print low and high presure
  if (*(dData->bpSelection)) {
    tft.setCursor(0, 150);
    if (*(dData->sysAlarm)) {
      tft.setTextColor(RED);
    } else if (*(dData->bpHigh)) {
      tft.setTextColor(ORANGE);
    } else {
      tft.setTextColor(GREEN);
    }
    tft.print(*(dData->sysNumeric)); // Not sure how to access correct index (0)
    tft.setTextColor(WHITE);     tft.print("/");
    if (*(dData->bpLow)) {
      tft.setTextColor(ORANGE);
    } else {
      tft.setTextColor(GREEN);
    }
    tft.print(*(dData->diasNumeric)); // Not sure how to access correct index (8)
    tft.setTextColor(WHITE);  tft.println(" mm Hg");

  } else {
    tft.setCursor(0, 150);
    tft.setTextColor(GREEN);    tft.print("--");
    tft.setTextColor(WHITE);    tft.print("/");
    tft.setTextColor(GREEN);    tft.print("--");
    tft.setTextColor(WHITE);    tft.println(" mm Hg");
  }

  // print temp
  if (*(dData->tempSelection)) {
    if (*(dData->tempOff)) {
      tft.setTextColor(ORANGE);
    } else {
      tft.setTextColor(GREEN);
    }
    tft.print(((float) * (dData->tempNumeric), 1));
    tft.setTextColor(WHITE);
    tft.print("C ");

  } else {
    tft.print("--.-");
    tft.setTextColor(WHITE);
    tft.print("C ");
  }

  // print pulserate
  if (*(dData->pulseSelection)) {
    if (*(dData->pulseOff)) {
      tft.setTextColor(ORANGE);
    } else {
      tft.setTextColor(GREEN);
    }
    tft.print(*(dData->pulseNumeric)); // Not sure how to access correct index, removed *
    tft.setTextColor(WHITE);
    tft.println(" BPM ");
  } else {
    tft.setTextColor(GREEN);
    tft.print("---");
    tft.setTextColor(WHITE);
    tft.println(" BPM ");
  }

  // print battery
  if (*(dData->batteryLow)) {
    tft.setTextColor(RED);
  } else {
    tft.setTextColor(GREEN);
  }
  tft.print(*(dData->batteryState));
  tft.setTextColor(WHITE);
  tft.print(" Charges");

  acknbuttons[0].initButton(&tft,  ACKN_BUTTON_X,
                            ACKN_BUTTON_Y,    // x, y, w, h, outline, fill, text
                            ACKN_BUTTON_W, ACKN_BUTTON_H, ILI9341_WHITE, acknbuttoncolors[0], ILI9341_WHITE,
                            acknbuttonlabels[0], ACKN_BUTTON_TEXTSIZE);
  acknbuttons[0].drawButton();
}




// Print something in the mini status bar with either flashstring
/*
  void status(const __FlashStringHelper *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(msg);
  }
  // or charstring
  void status(char *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(msg);
  }
*/
