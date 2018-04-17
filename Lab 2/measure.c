#include "Bool.h"
#include "DataStructs.h"
// Move this to the TCB struct
// int numOfCall = 0; use globalTime instead
// Bool sysMeasureComplete = FALSE; // Put these variables inside the TCB structs, initialize in main
// Bool diaMeasureComplete = FALSE;
// Bool tempIncrease = TRUE;
// Bool bpIncrease = TRUE;
// WHERE DO WE GET THE VARIABLES FROM? What's the point of having a datastruct??
unsigned int *measureInterval = 5;
void measureTemp(unsigned int *temperature, Bool *tempIncrease, unsigned int *numOfMeasureCalls);
void measureSysPres(unsigned int *sysPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measureDiaPres(unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measurePulseRate(unsigned int *pulseRate, Bool *bpIncrease, unsigned int *numOfMeasureCalls);


// Problems: 'Bool's are expected to be 'enum Bool *'
// numOfMeasureCalls
void measure(void *measureStruct) {
    MeasureData *mData = (MeasureData*) measureStruct;
    if ((*mData->globalTime % *measureInterval) == 0){
        measureTemp(mData->temperatureRaw, mData->tempIncrease, mData->numOfMeasureCalls);
        measureSysPres(mData->systolicPressRaw,mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
        measureDiaPres(mData->diastolicPressRaw,mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
        measurePulseRate(mData->pulseRateRaw, mData->bpIncrease, mData->numOfMeasureCalls);
        mData->numOfMeasureCalls++;
    }
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


