<<<<<<< HEAD
#ifdef __cplusplus
extern "C" {
#endif
#include "Bool.h"
#include <stdio.h>
#include "DataStructs.h"
#include "batteryStatusSC.h"
#include "measureSC.h"
#include "warningSC.h"
//#include "peripheralCom.h"
//#include "schedulerSC.h"
#include "computeSC.h"
//#include <Arduino.h>
#ifdef __cplusplus
}
#endif
#include "TFTKeypad.h"

void communicationSC(char *data, void *dataStruct);

TCB* head;
TCB* tail;

TCB MeasureTCB;
TCB ComputeTCB;
TCB tftTCB;
TCB WarningAlarmTCB;
TCB StatusTCB;

unsigned int globalTime = 0; // Change this to millis
Bool sysMeasureComplete = FALSE;
Bool diaMeasureComplete = FALSE;
Bool tempIncrease = TRUE;
Bool bpIncrease = TRUE;
unsigned int numOfMeasureCalls = 0;

unsigned int measureInterval = 5;
unsigned int computeInterval = 5;
unsigned int displayInterval = 5;
unsigned int warningInterval = 1;
unsigned int statusInterval = 5;

unsigned int temperatureRaw = 75;
unsigned int systolicPressRaw = 80;
unsigned int diastolicPressRaw = 80;
unsigned int pulseRateRaw = 50;

float tempNumeric = 0;
unsigned int sysNumeric = 0;
unsigned int diasNumeric = 0;
unsigned int pulseNumeric = 0;

unsigned int bloodPressCorrectedBuf[16] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
float tempCorrectedBuf[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
unsigned int pulseRateCorrectedBuf[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

unsigned int bloodPressRawBuf[16] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};;
unsigned int temperatureRawBuf[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
unsigned int pulseRateRawBuf[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};


unsigned short batteryState = 200;
/*
unsigned char bpOutOfRange = 0;
unsigned char tempOutOfRange = 0;
unsigned char pulseOutOfRange = 0;
*/
Bool bpHigh = FALSE;
Bool bpLow = FALSE;
Bool tempOff = FALSE;
Bool pulseOff = FALSE;
Bool batteryLow = FALSE;
Bool sysAlarm = FALSE;

Bool tempSelection = TRUE;
Bool bpSelection = TRUE;
Bool pulseSelection = TRUE;
Bool alarmAcknowledge = TRUE; // type TBD
unsigned int alarmTimer = 0;
unsigned long timeNow = 0;
Bool justPressed = FALSE;

MeasureData mData;
ComputeData cData;
TFTData dData;
WarningAlarmData wData;
StatusData stData;

void setup(void) {
    // Add variables to measure struct
    mData.globalTime = &globalTime;
    mData.measureInterval = &measureInterval;
    
    // Raw data
    mData.bloodPressRawBuf = bloodPressRawBuf;
    mData.pulseRateRawBuf = pulseRateRawBuf;
    mData.temperatureRawBuf = temperatureRawBuf;
    
    mData.sysMeasureComplete = &sysMeasureComplete;
    mData.diaMeasureComplete = &diaMeasureComplete;
    mData.tempIncrease = &tempIncrease;
    mData.bpIncrease = &bpIncrease;
    mData.numOfMeasureCalls = &numOfMeasureCalls;
//    mData.MeasureTCB = &MeasureTCB;
//    mData.ComputeTCB = &ComputeTCB;


    // Add variables to compute struct
    cData.globalTime = &globalTime;
    cData.bloodPressRawBuf = bloodPressRawBuf;
    cData.pulseRateRawBuf = pulseRateRawBuf;
    cData.temperatureRawBuf = temperatureRawBuf;

/*
    cData.tempNumeric = &tempNumeric;
    cData.sysNumeric = &sysNumeric;
    cData.diasNumeric = &diasNumeric;
    cData.pulseNumeric = &pulseNumeric;
*/
    // Add variables to display struct
    dData.globalTime = &globalTime;
    dData.displayInterval = &displayInterval;
    dData.bloodPressCorrectedBuf = bloodPressCorrectedBuf;
    dData.pulseRateCorrectedBuf = pulseRateCorrectedBuf;
    dData.tempCorrectedBuf = tempCorrectedBuf;
    dData.bloodPressRawBuf = bloodPressRawBuf;
    dData.pulseRateRawBuf = pulseRateRawBuf;
    dData.bpHigh = &bpHigh;
    dData.bpLow = &bpLow;
    dData.tempOff = &tempOff;
    dData.pulseOff = &pulseOff;
    /*
    dData.bpOutOfRange = &bpOutOfRange;
    dData.pulseOutOfRange = &pulseOutOfRange;
    dData.tempOutOfRange = &tempOutOfRange;
    */
    dData.batteryLow = &batteryLow;
    dData.tempNumeric = &tempNumeric;
    dData.sysNumeric = &sysNumeric;
    dData.diasNumeric = &diasNumeric;
    dData.pulseNumeric = &pulseNumeric;
    dData.batteryState = &batteryState;
    dData.displayInterval = &displayInterval;
    dData.tempSelection = &tempSelection;
    dData.bpSelection = &bpSelection;
    dData.pulseSelection = &pulseSelection;
    dData.alarmAcknowledge = &alarmAcknowledge;
    dData.alarmTimer = &alarmTimer;
    dData.sysAlarm = &sysAlarm;
    dData.timeNow = &timeNow;
    dData.justPressed = &justPressed;


    // Add values to warning/alarm struct
    wData.globalTime = &globalTime;
    wData.warningInterval = &warningInterval;
    /*
    wData.bpOutOfRange = &bpOutOfRange;
    wData.pulseOutOfRange = &pulseOutOfRange;
    wData.tempOutOfRange = &tempOutOfRange;
    */
    wData.batteryState = &batteryState;
    wData.bpHigh = &bpHigh;
    wData.bpLow = &bpLow;
    wData.tempOff = &tempOff;
    wData.pulseOff = &pulseOff;
    wData.batteryLow = &batteryLow;
    wData.tempNumeric = &tempNumeric;
    wData.sysNumeric = &sysNumeric;
    wData.diasNumeric = &diasNumeric;
    wData.pulseNumeric = &pulseNumeric;
    wData.sysAlarm = &sysAlarm;
    wData.alarmAcknowledge = &alarmAcknowledge;
    wData.alarmTimer = &alarmTimer;

    // Add data to status struct
    stData.globalTime = &globalTime;
    stData.statusInterval = &statusInterval;
    stData.batteryState = &batteryState;

    // Initialize the TCBs
    MeasureTCB.taskPtr = &measurerSC;
    MeasureTCB.taskDataPtr = (void*)&mData;
    MeasureTCB.prev = NULL;
    MeasureTCB.next = &StatusTCB;

    ComputeTCB.taskPtr = &computeSC;
    ComputeTCB.taskDataPtr = (void*)&cData;
    ComputeTCB.prev = NULL;  // Compute is by default not part of the queue
    ComputeTCB.next = NULL;

    StatusTCB.taskPtr = &batteryStatusSC;
    StatusTCB.taskDataPtr = (void*)&stData;
    StatusTCB.prev = &MeasureTCB;
    StatusTCB.next = &WarningAlarmTCB;

    WarningAlarmTCB.taskPtr = &annunciate;
    WarningAlarmTCB.taskDataPtr = (void*)&wData;
    WarningAlarmTCB.prev = &StatusTCB;
    WarningAlarmTCB.next = &tftTCB;

    tftTCB.taskPtr = &displayLoop;
    tftTCB.taskDataPtr = (void*)&dData;
    tftTCB.prev = &WarningAlarmTCB;
    tftTCB.next = NULL;

=======
// IMPORTANT: Elegoo_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com
//void drawDefaultMode();
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
void drawAnnunciate();
void drawMenu();

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
                             ILI9341_DARKGREY, ILI9341_DARKGREY};

char acknbuttonlabels[1][20] = {"Acknowl."};
uint16_t acknbuttoncolors[1] = {ILI9341_GREEN};

uint16_t identifier; // global variable to be reached from all functions

void setup(void) {
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
  }
   tft.begin(identifier);
   tft.setRotation(0);
   drawDefaultMode();
   
   Serial.print(F("THIS IS THE WIDTH"));
   Serial.print(tft.width());
   Serial.print(F("THIS IS THE HEIGHT"));
   Serial.print(tft.height());
}
>>>>>>> a7058520c4afaee70300228f7dbc45115674a50e


<<<<<<< HEAD
    Serial.println("0. are we here?");
}

void loop(void) {
    Serial.println("Start of loop: are we here?");
    timeNow = millis();
    TCB* curr = head;
    TCB* oldcurr;
    while (curr != tail){
        if (curr == &MeasureTCB){
            insertNode(&ComputeTCB, &MeasureTCB, head, tail);
        }
        (*(curr->taskPtr))(curr->taskDataPtr);
        oldcurr = curr;
        curr = curr->next;
        if (oldcurr == &ComputeTCB){
          deleteNode(&ComputeTCB,head,tail);
        }
    }       
    // While loop ends before tail is executed
    // So we call it one last time to run through everything
    (*(curr->taskPtr))(curr->taskDataPtr);
    // Delay one second
    globalTime++;
=======
void drawDefaultMode(){
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
int bpon = 1;
int tempon = 1;
int pulseon = 1;

int bpvar = 0;
int tempvar = 1;
int pulsevar = 2;

void drawMenu(){
  // create default mode buttons
  bpvar = ((bpon == 1) ? 0 : 3);
  tempvar = ((tempon == 1) ? 1 : 4);
  pulsevar = ((pulseon ==1) ? 2 : 5);
  
  menubuttons[bpvar].initButton(&tft,  MENU_BUTTON_X,
                 MENU_BUTTON_Y,    // x, y, w, h, outline, fill, text
                  MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[bpvar], ILI9341_WHITE,
                  menubuttonlabels[bpvar], MENU_BUTTON_TEXTSIZE);
  menubuttons[bpvar].drawButton();

  menubuttons[tempvar].initButton(&tft,  MENU_BUTTON_X,
                 MENU_BUTTON_Y+MENU_BUTTON_H+MENU_BUTTON_SPACING_Y,    // x, y, w, h, outline, fill, text
                  MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[tempvar], ILI9341_WHITE,
                  menubuttonlabels[tempvar], MENU_BUTTON_TEXTSIZE);
  menubuttons[tempvar].drawButton();

  menubuttons[pulsevar].initButton(&tft,  MENU_BUTTON_X,
                 MENU_BUTTON_Y+2*(MENU_BUTTON_H+MENU_BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  MENU_BUTTON_W, MENU_BUTTON_H, ILI9341_WHITE, menubuttoncolors[pulsevar], ILI9341_WHITE,
                  menubuttonlabels[pulsevar], MENU_BUTTON_TEXTSIZE);
  menubuttons[pulsevar].drawButton();
>>>>>>> a7058520c4afaee70300228f7dbc45115674a50e
}
#define MINPRESSURE 10
#define MAXPRESSURE 1000
int pressed = 1;

<<<<<<< HEAD
void communicationSC(char *data, void *dataStruct) {
    // send process
    
        char dataType = data[0];
        Serial.write(data); // send
        
        if (dataType == 'M'){
        } else if (dataType == 'C'){
        while (Serial.available() == 0){
        }
=======
void loop(void) {
  //mode = 1;
  TSPoint p = ts.getPoint();
  digitalWrite(13, HIGH);
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (pressed == 1){
      drawDefaultMode(); // MAYBE THIS IS WHY IT RESETS ON / OFF??
      if (mode == 1){
          drawMenu();
      } else if (mode ==2){
          drawAnnunciate();
      } 
      pressed = 0; 
  } 
  
   int dx;
   int dy;
   if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // scale from 0->1023 to tft.width
    p.y = (map(p.y, TS_MINX, TS_MAXX, tft.width(), 0));
    p.x = (tft.height()-map(p.x, TS_MINY, TS_MAXY, tft.height(), 0));//
    // Mapping to match actual screen
    dx = (unsigned int16_t) p.y;
    dy = (unsigned int32_t) p.x;
    dx = (unsigned int32_t) (dx-6)*232/210;
    dy = (unsigned int32_t) (dy+5)*320/345;
    Serial.print(dx);    Serial.print(", ");    Serial.println(dy);
   }

   
  // go thru all the buttons, checking if they were pressed
  for (uint8_t b=0; b<4; b++) {
      if (buttons[b].contains(dx, dy)) {
          Serial.print("Pressing: "); Serial.println(buttonlabels[b]);
          buttons[b].press(true);  // tell the button it is pressed
          Serial.print(dx);   Serial.print(", ");  Serial.println(dy);
          pressed = 1;
      } else {
          buttons[b].press(false);  // tell the button it is NOT pressed
      }
  }
  if (mode == 1){
      for (uint8_t b=0; b<3; b++) {
          if (menubuttons[b].contains(dx, dy)) {
              Serial.print("Pressing: "); Serial.println(menubuttonlabels[b]);
              menubuttons[b].press(true);  // tell the button it is pressed
              Serial.print(dx);     Serial.print(", ");     Serial.println(dy);
              pressed = 1;
          } else {
              menubuttons[b].press(false);  // tell the button it is NOT pressed
          }
      }
  } else if (mode == 2){
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
  for (uint8_t b=0; b<4; b++) {
    if (buttons[b].justReleased()) {
      // Serial.print("Released: "); Serial.println(b);
      buttons[b].drawButton();  // draw normal
    }
    
    if (buttons[b].justPressed()) {
        buttons[b].drawButton(true);  // draw invert!
        buttons[b].press(false);        
        if (b < 4) {
          mode = b+1; // Set mode to default 0 = Default, 1 = Menu, 2=Annunciate
        }  
       delay(100);
    }
  }
  if (mode ==1){
      for (uint8_t b=0; b<6; b++) {
          if (menubuttons[b].justReleased()) {
             // Serial.print("Released: "); Serial.println(b);
             menubuttons[b].drawButton();  // draw normal
          }
>>>>>>> a7058520c4afaee70300228f7dbc45115674a50e
        
          if (menubuttons[b].justPressed()) {
              menubuttons[b].press(false);
              menubuttons[b].drawButton(true);  // draw invert!
              if (b == 0 || b == 3){
                  bpon = ((bpon == 0) ? 1 : 0);
              } else if (b == 1 || b == 4){
                  tempon = ((tempon == 0) ? 1 : 0);
              } else if (b == 2 || b == 5){
                  pulseon = ((pulseon == 0) ? 1 : 0);
              }
              delay(100);
              mode = 1; // 0 = Default, 1 = Menu, 2=Annunciate
              //drawMenu();
        }
      }
  }
  if (mode == 2){
      if (acknbuttons[0].justReleased()) {
          // Serial.print("Released: "); Serial.println(b);
          acknbuttons[0].drawButton();  // draw normal
      }
  
<<<<<<< HEAD
        } else if (dataType == 'B'){
          while (Serial.available() == 0){
        }
          StatusData *stData = (StatusData*) dataStruct;
          (*(stData->batteryState)) = Serial.parseInt();
          
        }
}

void deleteNode(struct TCB* node, struct TCB* head, struct TCB* tail) {
    TCB* curr;
    TCB* prevNode;
    TCB* nextNode;
    if (node == head){
        // Node is head
        // 1. Set head->next to head
        curr = head;
        head = head->next;
        // 2. Set internal pointers to NULL
        curr->next = NULL;
    } else if (node == tail){
        // Node is tail
        // 1. Set tail->prev to tail
        curr = tail;
        tail = tail->prev;
        // 2. Set internal pointer to NULL
        curr->prev = NULL;
    } else {
        // Node is somewhere in between
        // 1. Find node
        curr = head->next;
        while(node != curr){
            curr = curr->next;
        }
        // 2. Node found, update neighbor pointers, set internal pointers to NULL
        prevNode = curr->prev;
        nextNode = curr->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        curr->next = NULL;
        curr->prev = NULL;
    }
    return;
}

// Do insert(TCBToInsert, TCBtoadd it to after)
// So calling insert(compute, measure) adds compute after measure

void insertNode(struct TCB* node, struct TCB* precNode, struct TCB* head, struct TCB* tail) {
    // Since C lacks default parameters,
    // The user has to input NULL as 2nd arg if not specified
    if (NULL == precNode){
        precNode = tail;
    }
    if(NULL == head){               //  If the head pointer is pointing to nothing
      head = node;                  //  set the head and tail pointers to point to this node
      tail = node;
    } else if (tail == precNode) {                        //  otherwise, head is not NULL, add the node to the end of the list
        tail->next = node;
        node->prev = tail;          //  note that the tail pointer is still pointing
                                    //  to the prior last node at this point
        tail = node;                //  update the tail pointer
    } else {
        TCB* curr = precNode->next;
        precNode->next = node;
        curr->prev = node;
        node->next=curr;
        node->prev = precNode;
    }
    return;
}
=======
      if (acknbuttons[0].justPressed()) {
          acknbuttons[0].press(false);
          acknbuttons[0].drawButton(true);  // draw invert!
          delay(100);
      } 
  }
}

void drawAnnunciate(){
  // create default mode buttonstft.setCursor(0, 0);
    // print low and high presure
    tft.setCursor(0, 150);
    tft.setTextColor(GREEN);
    tft.print("--");
    tft.setTextColor(WHITE);
    tft.print("/");
    tft.setTextColor(GREEN);
    tft.print("--");
    tft.setTextColor(WHITE);
    tft.println(" mm Hg");

    // print temp
    tft.setTextColor(GREEN);
    tft.print("37.2");
    tft.setTextColor(WHITE);
    tft.print("C "); 
    
    // print pulserate
    tft.setTextColor(RED);
    tft.print("200");
    tft.setTextColor(WHITE);
    tft.println(" BPM "); 
    
    // print battery
    tft.setTextColor(GREEN);
    tft.print("95");
    tft.setTextColor(WHITE);
    tft.print(" %"); 

  acknbuttons[0].initButton(&tft,  ACKN_BUTTON_X,
                 ACKN_BUTTON_Y,    // x, y, w, h, outline, fill, text
                  ACKN_BUTTON_W, ACKN_BUTTON_H, ILI9341_WHITE, acknbuttoncolors[0], ILI9341_WHITE,
                  acknbuttonlabels[0], ACKN_BUTTON_TEXTSIZE);
  acknbuttons[0].drawButton();
}


/*
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
*/
>>>>>>> a7058520c4afaee70300228f7dbc45115674a50e
