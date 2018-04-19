#include <stdio.h>
#include "DataStructs.h"
#include "tasks.h"
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
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
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//unsigned int measureInterval = 5;
unsigned int globalCounter = 0;


// Problems: 'Bool's are expected to be 'enum Bool *'
// numOfMeasureCalls
void measureData(void *measureStruct) {
    MeasureData *mData = (MeasureData*) measureStruct;
    if ((globalCounter % (*(mData->measureInterval))) != 0){
        return;
    }
    measureTemp(mData->temperatureRaw, mData->tempIncrease, mData->numOfMeasureCalls);
    //Serial.println(*(mData->temperatureRaw));
    measureSysPres(mData->systolicPressRaw,mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
    measureDiaPres(mData->diastolicPressRaw,mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
    measurePulseRate(mData->pulseRateRaw, mData->bpIncrease, mData->numOfMeasureCalls);
    *(mData->numOfMeasureCalls) += 1;
}

void computeData(void *computeStruct) {
    ComputeData *cData = (ComputeData*) computeStruct;
    if ((globalCounter % *(cData->computeInterval)) != 0){
        return;
    }
    double temp = 5 + 0.75 * (*(cData->temperatureRaw));
    unsigned int systolicPres = (unsigned int) 9 + 2 * (*(cData->systolicPressRaw));
    unsigned int diastolicPres = (unsigned int) floor(6 + 1.5 * (*(cData->diastolicPressRaw)));
    unsigned int pr = (unsigned int) 8 + 3 * (*(cData->pulseRateRaw));

    *(cData->tempNumeric) = temp;
    *(cData->sysNumeric) = systolicPres;
    *(cData->diasNumeric) = diastolicPres;
    *(cData->pulseNumeric) = pr;
/*
    sprintf(**(cData->tempCorrected), "%f", temp);
    Serial.println(F("Updated tempCorrected in computefun"));
    delay(200);
    sprintf(**(cData->sysPressCorrected), "%d", systolicPres);
    sprintf(**(cData->diasCorrected), "%d", diastolicPres);
    sprintf(**(cData->prCorrected), "%d", pr);
    Serial.println(F("Done with computefun"));
    delay(200);
*/
}

void displayData(void *displayStruct) {
    DisplayData *dData = (DisplayData*) displayStruct;
    if ((globalCounter % *(dData->displayInterval)) != 0){
        return;
    };
    tft.fillScreen(BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    // print low and high presure
    tft.setTextColor(*(dData->bpHigh) ? RED : GREEN);
    //tft.print(*(dData->sysNumeric));
    tft.print(*(dData->systolicPressRaw));
    tft.setTextColor(WHITE);
    tft.print("/");
    tft.setTextColor(*(dData->bpLow) ? RED : GREEN);
    //tft.print(*(dData->diasNumeric));
    tft.print(*(dData->diastolicPressRaw));
    tft.setTextColor(WHITE);
    //tft.write(80);
    tft.println(" mm Hg");

    // print temp
    tft.setTextColor(*(dData->tempOff) ? RED : GREEN);
    //tft.print(*(dData->tempNumeric));
    tft.print((float)*(dData->temperatureRaw), 1);
    tft.setTextColor(WHITE);
    tft.print("C "); 
    
    // print pulserate
    tft.setTextColor(*(dData->pulseOff) ? RED : GREEN);
    //tft.print(*(dData->pulseNumeric));
    tft.print(*(dData->pulseRateRaw));
    tft.setTextColor(WHITE);
    tft.print(" BPM "); 
    
    // print battery
    tft.setTextColor(*(dData->batteryLow) ? RED : GREEN);
    tft.print(*(dData->batteryState));
    tft.setTextColor(WHITE);
    tft.print("%"); 
}

void annuciate(void *warningAlarmStruct) {
    WarningAlarmData *wData = (WarningAlarmData*) warningAlarmStruct;
    if ((globalCounter % *(wData->warningInterval)) != 0){
    return;
    }
    // Battery
    *(wData->batteryLow) = (((*(wData->batteryState)) < 40) ?  TRUE : FALSE);
    // syst
    *(wData->bpHigh) = (((*(wData->sysNumeric)) > 120) ? TRUE : FALSE);
    // dias
    *(wData->bpLow) = (((*(wData->diasNumeric)) < 80) ? TRUE : FALSE);
    // pulserate
    *(wData->pulseOff) = ((((*(wData->pulseNumeric)) < 60) || ((*(wData->pulseNumeric)) > 100)) ? TRUE : FALSE);
    // Temperature
}


void batteryStatus(void *statusStruct) {
    StatusData *sData = (StatusData*) statusStruct;
    if ((globalCounter % *(sData->statusInterval)) != 0){
        return;
    }
    *(sData->batteryState) -= 1;
}

void schedulefun(TCB **tasks) {
    Serial.print(F("GlobalCounter = "));
    Serial.println(globalCounter);
    (*(tasks[0]->taskPtr))(tasks[0]->taskDataPtr);
    (*(tasks[1]->taskPtr))(tasks[1]->taskDataPtr);
    (*(tasks[2]->taskPtr))(tasks[2]->taskDataPtr);
    (*(tasks[3]->taskPtr))(tasks[3]->taskDataPtr);
    (*(tasks[4]->taskPtr))(tasks[4]->taskDataPtr);
    delay(50);
    //delay_ms(10000);
    globalCounter++;
}

//////////////////
// MEASURE TEMP //
//////////////////
void measureTemp(unsigned int *temperature, Bool *tempIncrease, unsigned int *numOfMeasureCalls) {
    if (*tempIncrease) {
        if (*numOfMeasureCalls % 2 == 0) {
            *temperature += 2;
        } else {
            *temperature -= 1;
        }
    } else {
        if (*numOfMeasureCalls % 2 == 0) {
            *temperature -= 2;
        } else {
            *temperature += 1;
        }
    }
    if (*tempIncrease && *temperature > 50){
        *tempIncrease = FALSE;
    }
    if (!(*tempIncrease) && *temperature < 15){
        *tempIncrease = TRUE;
    }
}

void measureSysPres(unsigned int *sysPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls) {
    if (*diaMeasureComplete && *sysMeasureComplete){
            *sysMeasureComplete = FALSE;
            *sysPres = 80;
    }
    if (!*sysMeasureComplete) {
        if (*numOfMeasureCalls % 2 == 0) {
                *sysPres += 3;
        }
        else {
            *sysPres -= 1;
        }
        if (*sysPres > 100) {
            *sysMeasureComplete = TRUE;
        }
    }
}

void measureDiaPres(unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls) {
    if (*sysMeasureComplete && *diaMeasureComplete){
            *diaMeasureComplete = FALSE;
            *diaPres = 80;
    }
    if (!*diaMeasureComplete) {
        if (*numOfMeasureCalls % 2 == 0) {
                *diaPres -= 2;
        }
        else {
            *diaPres += 1;
        }
        if (*diaPres < 40) {
            *diaMeasureComplete = TRUE;
        }
    }
}

void measurePulseRate(unsigned int *pulseRate, Bool *bpIncrease, unsigned int *numOfMeasureCalls){
     if (*bpIncrease) {
        if (*numOfMeasureCalls % 2 == 0) {
            *pulseRate -= 1;
        }
        else {
            *pulseRate += 3;
        }
    }
    else {
        if (*numOfMeasureCalls % 2 == 0) {
            *pulseRate += 1;
        }
        else {
            *pulseRate -= 2;
        }
    }
    if (*bpIncrease && (*pulseRate > 40)){
        *bpIncrease = FALSE;
    }
    if (!(*bpIncrease) && (*pulseRate < 15)){
        *bpIncrease = TRUE;
    }
}

///////////////////
//     DELAY     //
///////////////////
void delay_ms(unsigned long time) {
    volatile int i, j;
    for (i = 0; i <= 3000; i++) { // 32767
        for (j = time; j > 0; j--) {
            // empty
        }
    }
}



///////////////////
// SETUP DISPLAY //
///////////////////
void setupDisplay(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));


#ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
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
  }
  else if(identifier==0x1111)
  {     
      identifier=0x9328;
       Serial.println(F("Found 0x9328 LCD driver"));
  }
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9328;
  
  }
  tft.begin(identifier);
}

