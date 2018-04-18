#include <stdio.h>
#include "DataStructs.h"
#include "tasks.h"

// unsigned int measureInterval = 5;
// unsigned int globalCounter = 0;

// Problems: 'Bool's are expected to be 'enum Bool *'
// numOfMeasureCalls

void measure(void *measureStruct){
    MeasureData *mData = (MeasureData*) measureStruct;
    if ((*mData->globalTime % measureInterval) != 0){
        return;
    }
    measureTemp(mData->temperatureRaw, mData->tempIncrease, mData->numOfMeasureCalls);
    measureSysPres(mData->systolicPressRaw, mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
    measureDiaPres(mData->diastolicPressRaw, mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
    measurePulseRate(mData->pulseRateRaw, mData->bpIncrease, mData->numOfMeasureCalls);
    (*(mData->numOfMeasureCalls))++;
}

void compute(void *computeStruct) {
    ComputeData *cData = (ComputeData*) computeStruct;
    if ((*cData->globalTime % measureInterval) != 0){
        return;
    }
    double temp = 5 + 0.75 * (*(cData->temperatureRaw));
    unsigned int systolicPres = (unsigned int) 9 + 2 * (*cData->systolicPressRaw);
    unsigned int diastolicPres = (unsigned int) 6 + 1.5 * (*cData->diastolicPressRaw);
    unsigned int pr = (unsigned int) 8 + 3 * (*cData->pulseRateRaw);

    *(cData->tempNumeric) = temp;
    *(cData->sysNumeric) = systolicPres;
    *(cData->diasNumeric) = diastolicPres;
    *(cData->pulseNumeric) = pr;

    sprintf(*(cData->tempCorrected), "%f", temp);
    sprintf(*(cData->sysPressCorrected), "%d", systolicPres);
    sprintf(*(cData->diasCorrected), "%d", diastolicPres);
    sprintf(*(cData->prCorrected), "%d", pr);
}

void display(void *displayStruct) {
    DisplayData *dData = (DisplayData*) displayStruct;
    if ((*dData->globalTime % measureInterval) != 0){
        return;
    }

    tft.fillScreen(BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    // print low and high presure
    tft.setTextColor(*(dData->bpLow) ? RED : GREEN);
    tft.printf("%s ", dData->diasCorrected);
    tft.setTextColor(*(dData->bpHigh) ? RED : GREEN);
    tft.printf("%s\n", dData->sysPressCorrected);

    // print temp
    tft.setTextColor(*(dData->tempOff) ? RED : GREEN);
    tft.printf("%s ", dData->tempCorrected);
    // print pr
    tft.setTextColor(*(dData->pulseOff) ? RED : GREEN);
    tft.printf("%s ", dData->prCorrected);
    // print battery
    tft.setTextColor(*(dData->batteryLow) ? RED : GREEN);
    tft.printf("%d ", dData->batteryState);
    //
}

void annuciate(void *warningAlarmStruct) {
        WarningAlarmData *wData = (WarningAlarmData*) warningAlarmStruct;
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

    delay_ms(10000);
    (*globalTime)++;
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
void delay_ms(unsigned int time_in_ms) {
    volatile int i, j;
    for (i = 0; i <= 31; i++) { // 32767
        for (j = 0; j <= time_in_ms; j++) {

        }
    }
}


