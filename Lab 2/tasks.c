#include <math.h>
#include <stdio.h>
#include "DataStructs.h"




// Move this to the TCB struct
// int numOfCall = 0; use globalTime instead
// Bool sysMeasureComplete = FALSE; // Put these variables inside the TCB structs, initialize in main
// Bool diaMeasureComplete = FALSE;
// Bool tempIncrease = TRUE;
// Bool bpIncrease = TRUE;
// WHERE DO WE GET THE VARIABLES FROM? What's the point of having a datastruct??
unsigned int measureInterval = 5;
unsigned int globalCounter = 0;


// Problems: 'Bool's are expected to be 'enum Bool *'
// numOfMeasureCalls
void measure(void *measureStruct) {
    MeasureData *mData = (MeasureData*) measureStruct;
    if ((*mData->globalTime % measureInterval) != 0){
        return;
    }
    measureTemp(mData->temperatureRaw, mData->tempIncrease, mData->numOfMeasureCalls);
    measureSysPres(mData->systolicPressRaw,mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
    measureDiaPres(mData->diastolicPressRaw,mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
    measurePulseRate(mData->pulseRateRaw, mData->bpIncrease, mData->numOfMeasureCalls);
    mData->numOfMeasureCalls++;
}

void compute(void *computeStruct) {
    ComputeData *cData = (ComputeData*) computeStruct;
    if ((*cData->globalTime % measureInterval) != 0){
        return;
    }
    int temp = (int) floor(5 + 0.75 * (*(cData->temperatureRaw)));
    int systolicPres = (int) floor(9 + 2 * (*cData->systolicPressRaw));
    int diastolicPres = (int) floor(6 + 1.5 * (*cData->diastolicPressRaw));
    int pr = (int) floor(8 + 3 * (*cData->pulseRateRaw));

    sprintf(*(cData->tempCorrected), "%d", temp);
    sprintf(*(cData->sysPressCorrected), "%d", systolicPres);
    sprintf(*(cData->diasCorrected), "%d", diastolicPres);
    sprintf(*(cData->prCorrected), "%d", pr);
}

void display(void *displayStruct) {
    DisplayData *dData = (DisplayData*) displayStruct;
    if ((*dData->globalTime % measureInterval) != 0){
        return;
    }
    // print low and high presure
    tft.setTextColor(*(dData->bpLow) ? RED : GREEN);
    tft.printf("%s ", dData->diasCorrected);
    tft.setTextColor(*(dData->bpHigh) ? RED : GREEN);
    tft.printf("%s\n", dData->sysPressCorrected);
    
    // print temp
    tft.setTextColor(*(dData->tempHigh) ? RED : GREEN);
    tft.printf("%s ", dData->tempCorrected);
    // print pr
    tft.setTextColor(*(dData->pulseLow) ? RED : GREEN);
    tft.printf("%s ", dData->prCorrected);
    // print battery
    tft.setTextColor(*(dData->batteryLow) ? RED : GREEN);
    tft.printf("%d ", dData->batteryState);
    // 
}

void annuciate(void *warningAlarmStruct) {
    WarningAlarmData *wData = (WarningAlarmData*) warningAlarmStruct;
    if (*(wData->temperatureRaw)) 
}

void status(void *statusStruct) {
    StatusData *sData = (StatusData*) statusStruct;
    if ((*sData->globalTime % measureInterval) != 0){
        return;
    }
    *(sData->batteryState) -= 1;
}

void schedule(void *taskQueue) {
    TCB *tasks[5] = (TCB*) taskQueue;

    (*(tasks[0]->taskPtr))(tasks[0]->taskDataPtr);
    (*(tasks[1]->taskPtr))(tasks[1]->taskDataPtr);
    (*(tasks[2]->taskPtr))(tasks[2]->taskDataPtr);
    (*(tasks[3]->taskPtr))(tasks[3]->taskDataPtr);
    (*(tasks[4]->taskPtr))(tasks[4]->taskDataPtr);

    delay(10000);
    globalCounter++;


    /*if (counter == 0) {
        // measure
        (*(tasks[0]->taskPtr))(tasks[0]->taskDataPtr);
        (*(tasks[0]->taskPtr))(tasks[0]->taskDataPtr);
    }
    else if (count == 1) {
        // execute compute
    }
    // >= 5 case
    else {
        count = 0;
    }

    counter++;*/
}


// Do we really need to use all variables like this?
void measureTemp(unsigned int *temperature, Bool *tempIncrease, unsigned int *numOfMeasureCalls) {
    // cases:   0-15
    //          15-50
    //          50+
    if (*tempIncrease) {
        if (*numOfMeasureCalls % 2 == 0) {
            *temperature += 2;
        }
        else {
            *temperature -= 1;
        }
    }
    else {
        if (*numOfMeasureCalls % 2 == 0) {
            *temperature -= 2;
        }
        else {
            *temperature += 1;
        }
    }
    if (*tempIncrease && *temperature > 50){
        *tempIncrease = FALSE;
    }
    if (!*tempIncrease && *temperature < 15){
        *tempIncrease = TRUE;
    }
}

void measureSysPres(unsigned int *sysPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls) {
    if (*diaMeasureComplete && !*sysMeasureComplete){
            *sysMeasureComplete = FALSE;
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
    if (*sysMeasureComplete && !*diaMeasureComplete){
            *diaMeasureComplete = FALSE;
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
    if (*bpIncrease && *pulseRate > 40){
        *bpIncrease = FALSE;
    }
    if (!*bpIncrease && *pulseRate < 15){
        *bpIncrease = TRUE;
    }
}

/* Delay for X milliseconds */
void delay(unsigned long time) {
    volatile int i, j;
    for (i = 0; i <= time; i++) {
        for (j = 0; j <= time; j++) {
            // empty
        }
    }
}


