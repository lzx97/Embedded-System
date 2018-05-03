#include "DataStructsPS.h"
#include "Bool.h"

int pin = 7; // pin to receive pulse rate input;


void measurePS(void *measureStruct) {
    // TODO: modify lab 2 codes according to the new spec
    MeasureDataPS *mData = (MeasureDataPS*) measureStruct;
    
    // measure temperature
    if (*(mData->tempSelection)){ 
        measureTemp(mData->temperatureRaw, mData->tempIncrease, mData->numOfMeasureCalls);
    }

    // measure blood pressures
    if (*(mData->bpSelection)){
        measureSysPres(mData->systolicPressRaw,mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
        measureDiaPres(mData->diastolicPressRaw,mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
    }

    // measure pulse rate
    if (*(mData->pulseSelection)){
        measurePulseRate(mData->pulseRateRaw);
    }

    // increment simulation counter
    *(mData->numOfMeasureCalls) += 1; // Change this to numOfTempCalls, numOfBpCalls, numOfPulseCalls??
}

void measureTemp(unsigned int *temperature, Bool *tempIncrease, unsigned int *numOfMeasureCalls) {
    if (*tempIncrease && *temperature > 50){
        *tempIncrease = FALSE;
    }
    if (!(*tempIncrease) && *temperature < 15){
        *tempIncrease = TRUE;
    }

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

void measurePulseRate(unsigned int *pulseRate){
    int halfPeriod = pulseIn(pin, LOW);
    float halfPeriodInS = (1.0 * halfPeriod) / 1000000;
    int pulse = (int) 1 / (2 * halfPeriodInS);

    *pulseRate = pulse;
    



    /* if (*bpIncrease && (*pulseRate > 40)){
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
    }*/ 
}