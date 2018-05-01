#include "DataStructs.h"

void measurement(void *measureStruct) {
    // TODO: modify lab 2 codes according to the new spec
    MeasureData *mData = (MeasureData*) measureStruct;
    if ((globalCounter % (*(mData->measureInterval))) != 0){
        return;
    }
    if (*(mData->tempSelection)){
    measureTemp(mData->temperatureRaw, mData->tempIncrease, mData->numOfMeasureCalls);
    }
    if (*(mData->bpSelection)){
    measureSysPres(mData->systolicPressRaw,mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
    measureDiaPres(mData->diastolicPressRaw,mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
    }
    if (*(mData->pulseSelection)){
    measurePulseRate(mData->pulseRateRaw, mData->bpIncrease, mData->numOfMeasureCalls);
    }
    *(mData->numOfMeasureCalls) += 1; // Change this to numOfTempCalls, numOfBpCalls, numOfPulseCalls??

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
     if (*bpIncrease && (*pulseRate > 40)){
        *bpIncrease = FALSE;
    }
    if (!(*bpIncrease) && (*pulseRate < 15)){
        *bpIncrease = TRUE;
    }

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
            *pulseRate -= 3;
        }
    }
}
