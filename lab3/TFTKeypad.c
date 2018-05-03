#include "DataStructs.h"
#include <stdio.h>
#include "DataStructs.h"
//#include "tasks.h"
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h> // Maybe remove this??

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).
// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

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
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F


/******************* UI details */
#define MODE_BUTTON_X 50
#define MODE_BUTTON_Y 90
#define MODE_BUTTON_W 80
#define MODE_BUTTON_H 25
#define MODE_BUTTON_SPACING_X 30
#define MODE_BUTTON_SPACING_Y 8
#define MODE_BUTTON_TEXTSIZE 2

#define MENU_BUTTON_X 50
#define MENU_BUTTON_Y 90
#define MENU_BUTTON_W 80
#define MENU_BUTTON_H 25
#define MENU_BUTTON_SPACING_X 30
#define MENU_BUTTON_SPACING_Y 8
#define MENU_BUTTON_TEXTSIZE 2

#define ANNUNCIATE_BUTTON_X 50
#define ANNUNCIATE_BUTTON_Y 90
#define ANNUNCIATE_BUTTON_W 80
#define ANNUNCIATE_BUTTON_H 25
#define ANNUNCIATE_BUTTON_SPACING_X 30
#define ANNUNCIATE_BUTTON_SPACING_Y 8
#define ANNUNCIATE_BUTTON_TEXTSIZE 2

// text box where numbers go
#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 300
#define TEXT_H 50
#define TEXT_TSIZE 3
#define TEXT_TCOLOR ILI9341_MAGENTA
// the data (phone #) we store in the textfield

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
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;

Elegoo_GFX_Button buttons[11];
/* create 11 buttons
0: Menu,  1: Annunciate
2: Exp1,  3: Exp2,
4: Bloodpressure ON, 5: Temperature ON
6: Pulserate ON,  7: Bloodpressure OFF
8: Temperature OFF,  9: Pulserate OFF
10: Annunciate
*/

char buttonlabels[11][5] = {"Menu", "Annunciate", "Exp1", "Exp2", "Blood Pressure: ON", "Temperature: ON",
                            "Pulserate: ON", "Blood Pressure: OFF", "Temperature: OFF", "Pulserate: OFF", "Annunciate"};
uint16_t buttoncolors[11] = {ILI9341_DARKGREY, ILI9341_DARKGREY, ILI9341_DARKGREY, ILI9341_DARKGREY,
                             ILI9341_LIGHTGREY, ILI9341_LIGHTGREY, ILI9341_LIGHTGREY, ILI9341_DARKGREY,
                             ILI9341_DARKGREY, ILI9341_DARKGREY, ILI9341_GREEN};


void TFTKeypad(void *keypadStruct) {
    // CHECK HOW TO USE DIFFERENT SETS OF BUTTONS FOR DIFFERENT INTERFACES

        //DisplayData *dData = (DisplayData*) displayStruct;
        //if ((globalCounter % *(dData->displayInterval)) != 0){
        //return;
    //};
    // TODO: implement
    // Run this in the never ending while loop and check for inputs
    // If event happened: Check if it was a change of mode //
    // Yes: update mode,    No: Check the currently activated buttons (menu, annunciate)
    // set screen to all black while loading the new view
    // If not

    // Activate current mode {Menu, Annunciation, Exp1, Exp2}
    if (statusChanged){}
    void drawDefaultMode();
    if (mode == "Menu"){
        displayMenu();
    } else if (mode == "Annunciate"){
        displayAnnunciate();
    }

}

void displayMenu(void *keyPadStruct){
    // draw bp
    int bpButton, tempButton, pulseButton;
    int printbuttons[3] = {bpButton, tempButton, pulseButton};
    if (BpActive){
        bpButton = 4;
    } else {
        bpButton = 7;
    }
    if (tempActive){
        tempButton = 5;
    } else {
        tempButton = 8;
    }
    if (pulseActive){
        pulseButton = 6;
    } else {
        pulseButton = 9;
    }
    for (int i = 0; i < 3; i++){
    buttons[printbuttons[i]].initButton(&tft, MENU_BUTTON_X, MENU_BUTTON_Y,    // x, y, w, h, outline, fill, text
                 MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, buttoncolors[printbuttons[i]],
                 ILI9341_WHITE, buttonlabels[printbuttons[i]], MENU_BUTTON_TEXTSIZE);
    buttons[printbuttons[i]].drawButton();
    }


}

void displayAnnunciate(void *keyPadStruct) {
    // Adds the menu up top
    // Everything below should be the same as before
    // ADD ANNUNCIATE!!
    tft.setTextSize(2);
    tft.setCursor(0, 80); // Change this to be halfway down, leaving enough space for the menus in the top
    // print low and high presure
    tft.setTextColor(*(dData->bpHigh) ? RED : GREEN);
    //tft.print(*(dData->sysNumeric));
    tft.print(*(dData->sysNumeric));
    tft.setTextColor(WHITE);
    tft.print("/");
    tft.setTextColor(*(dData->bpLow) ? RED : GREEN);
    //tft.print(*(dData->diasNumeric));
    tft.print(*(dData->diasNumeric));
    tft.setTextColor(WHITE);
    //tft.write(80);
    tft.println(" mm Hg");

    // print temp
    tft.setTextColor(*(dData->tempOff) ? RED : GREEN);
    //tft.print(*(dData->tempNumeric));
    tft.print((float)*(dData->tempNumeric), 1);
    tft.setTextColor(WHITE);
    tft.print("C ");

    // print pulserate
    tft.setTextColor(*(dData->pulseOff) ? RED : GREEN);
    //tft.print(*(dData->pulseNumeric));
    tft.print(*(dData->pulseNumeric));
    tft.setTextColor(WHITE);
    tft.println(" BPM ");

    // print battery
    tft.setTextColor(*(dData->batteryLow) ? RED : GREEN);
    tft.print(*(dData->batteryState));
    tft.setTextColor(WHITE);
    tft.print(" Charges");

    // Add annunciate button
    buttons[10].initButton(&tft, ANNUNCIATE_BUTTON_X, ANNUNCIATE_BUTTON_Y,    // x, y, w, h, outline, fill, text
                 ANNUNCIATE_BUTTON_W, ANNUNCIATE_BUTTON_H, ILI9341_WHITE, buttoncolors[10],
                 ILI9341_WHITE, buttonlabels[10], ANNUNCIATE_BUTTON_TEXTSIZE);
    buttons[10].drawButton();
}




// Print something in the mini status bar with either flashstring
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
#define MINPRESSURE 10
#define MAXPRESSURE 1000
void loop(void) {
  /*TSPoint p;
  p = ts.getPoint();
  */
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

 // p = ts.getPoint();
  /*
  if (ts.bufferSize()) {

  } else {
    // this is our way of tracking touch 'release'!
    p.x = p.y = p.z = -1;
  }*/

  // Scale from ~0->4000 to tft.width using the calibration #'s
  /*
  if (p.z != -1) {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    Serial.print("("); Serial.print(p.x); Serial.print(", ");
    Serial.print(p.y); Serial.print(", ");
    Serial.print(p.z); Serial.println(") ");
  }*/
   if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // scale from 0->1023 to tft.width
    p.x = (tft.width() - map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
    p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));//
   }

  // go thru all the buttons, checking if they were pressed
  for (uint8_t b=0; b<15; b++) {
    if (buttons[b].contains(p.x, p.y)) {
      //Serial.print("Pressing: "); Serial.println(b);
      buttons[b].press(true);  // tell the button it is pressed
      //Serial.print(p.x);
      //Serial.print(", ");
      //Serial.println(p.y);
    } else {
      buttons[b].press(false);  // tell the button it is NOT pressed
    }
  }

  // now we can ask the buttons if their state has changed
  for (uint8_t b=0; b<15; b++) {
    if (buttons[b].justReleased()) {
      // Serial.print("Released: "); Serial.println(b);
      buttons[b].drawButton();  // draw normal
    }

    if (buttons[b].justPressed()) {
        buttons[b].drawButton(true);  // draw invert!

        // if a numberpad button, append the relevant # to the textfield
        if (b >= 3) {
          if (textfield_i < TEXT_LEN) {
            textfield[textfield_i] = buttonlabels[b][0];
            textfield_i++;
	    textfield[textfield_i] = 0; // zero terminate

           // fona.playDTMF(buttonlabels[b][0]);
          }
        }

        // clr button! delete char
        if (b == 1) {

          textfield[textfield_i] = 0;
          if (textfield_i > 0) {
            textfield_i--;
            if(textfield_i < 0){
                textfield_i = 0;
            }
            textfield[textfield_i] = ' ';
          }
        }

        // update the current text field
        Serial.println(textfield);
        tft.setCursor(TEXT_X + 2, TEXT_Y+10);
        tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(textfield);

        // its always OK to just hang up
        if (b == 0) {
          status(F("Hanging up"));
          //fona.hangUp();
        }
        // we dont really check that the text field makes sense
        // just try to call
        if (b == 2) {
          status(F("Calling"));
          Serial.print("Calling "); Serial.print(textfield);

          //fona.callPhone(textfield);
        }

      delay(100); // UI debouncing
    }
  }

}
void setupDisplay(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9341;
    drawDefaultMode();
  }
  // create 'text field'
  tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9341_WHITE);
}

void drawDefaultMode(){
  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  // create default mode buttons
  for (uint8_t row=0; row<2; row++) {
    for (uint8_t col=0; col<2; col++) {
      buttons[col + row*2].initButton(&tft, MODE_BUTTON_X+col*(MODE_BUTTON_W+MODE_BUTTON_SPACING_X),
                 MODE_BUTTON_Y+row*(MODE_BUTTON_H+MODE_BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  MODE_BUTTON_W, MODE_BUTTON_H, ILI9341_WHITE, buttoncolors[col+row*2], ILI9341_WHITE,
                  buttonlabels[col + row*2], MODE_BUTTON_TEXTSIZE);
      buttons[col + row*2].drawButton();
    }
  }
}
