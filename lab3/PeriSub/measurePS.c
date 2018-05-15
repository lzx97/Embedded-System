#include "DataStructsPS.h"
#include "Bool.h"
#include <math.h>
#include "measurePS.h"
#include <Arduino.h>



void measurePS(void *measureStruct) {
    MeasureDataPS *mData = (MeasureDataPS*) measureStruct;
    
    // measure temperature
    if (*(mData->tempSelection)){ 
        measureTemp(mData->temperatureRaw, mData->tempIncrease, mData->numOfMeasureCalls);
    }

    // measure blood pressures
    if (*(mData->bpSelection)){
        measureSysPres(mData->systolicPressRaw, mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
        measureDiaPres(mData->diastolicPressRaw, mData->sysMeasureComplete, mData->diaMeasureComplete, mData->numOfMeasureCalls);
    }

    // measure pulse rate
    if (*(mData->pulseSelection)){
        measurePulseRate(mData->pulseRateRaw);
    }

    // increment simulation counter
    *(mData->numOfMeasureCalls) += 1;
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
    /*while (digitalRead(PIN_IN) != HIGH) {
        
    }
    while (digitalRead(PIN_IN) != LOW) {
        // idle until PIN_IN == LOW
    }
    unsigned long startTime = micros();
    while (digitalRead(PIN_IN) != HIGH) {
        // idle till HIGH
        //Serial.println(digitalRead(PIN_IN));
    }
    while (digitalRead(PIN_IN) != LOW) {
        // idle till another low
        //Serial.println(digitalRead(PIN_IN));
    }
    unsigned long stopTime = micros();
    unsigned long period = stopTime - startTime;
    double periodInS = (1.0 * period) / 1000000;
    int pulse = (int) 1 / periodInS;

    *pulseRate = pulse + 1;*/
    
    
    unsigned long halfPeriod = pulseIn(PIN_IN, LOW, 2000000UL);
    double halfPeriodInS = (1.0 * halfPeriod) / 1000000;
    int pulse = (int) 1 / (2 * halfPeriodInS);

    *pulseRate = pulse;
    
}
