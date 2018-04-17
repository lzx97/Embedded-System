#include "DataStructs.h"

void display(void *displayStruct) {
    DisplayData *dData = (DisplayData*) displayStruct;

    // print low and high presure
    tft.printf("%s ", dData->diasCorrected);
    tft.printf("%s\n", dData->sysPressCorrected);
    
    // print temp
    tft.printf("%s ", dData->tempCorrected);
    // print pr
    tft.printf("%s ", dData->prCorrected);
    // print battery
    tft.printf("%d ", dData->batteryState);
    // 
}