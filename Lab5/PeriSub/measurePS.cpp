#include "DataStructsPS.h"
#include "Bool.h"
#include <math.h>
#include "measurePS.h"
#include <Arduino.h>



void measurePS(void *measureStruct) {
    MeasureDataPS *mData = (MeasureDataPS*) measureStruct;
    
    // measure temperature
    if (*(mData->tempSelection)){ 
        measureTemp(mData->temperatureRaw);
    }

    // measure blood pressures
    if (*(mData->bpSelection)){
        measureBloodPres(mData->systolicPressRaw, mData->diastolicPressRaw, mData->sysMeasureComplete, mData->diaMeasureComplete,
                mData->bloodPressure, mData->patient);
        (*(mData->bpSelection)) = FALSE;
    }

    // measure pulse rate
    if (*(mData->pulseSelection)){
        measurePulseRate(mData->pulseRateRaw);
    }

    if (*(mData->respSelection)) {
        measureRespiration(mData->respirationRaw);
    }

    // increment simulation counter
    *(mData->numOfMeasureCalls) += 1;
}

void measureTemp(unsigned int *temperature) {
    int val = analogRead(TEMP_IN);
    int temp = map(val, 0, 1023, 15, 50);
    
    *temperature = temp;

    
    
/*
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
    */
}

void measureBloodPres(unsigned int *sysPres, unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete,
                        unsigned int *bloodPressure, int *patient) {
    /*
    Bool IncRead;
    Bool DecRead;
    while (!(*(sysMeasureComplete)) || !(*(diaMeasureComplete))) {
        do {
            IncRead = digitalRead(BP_INC);
            DecRead = digitalRead(BP_DEC);
        }
        while (IncRead == DecRead);

        if (IncRead) {
            *(bloodPressure) *= 1.1;
        }
        else if (DecRead) {
            *(bloodPressure) *= 0.9;
        }

        if (!(*(sysMeasureComplete))) {
            if (*(bloodPressure) >= 110 && *(bloodPressure) <= 150) {
                *sysPres = *bloodPressure;
                *sysMeasureComplete = TRUE;

                digitalWrite(LED_BUILTIN, HIGH);
                delay(100);
                digitalWrite(LED_BUILTIN, LOW);
                delay(100);
            }
        }
        else if (!(*(diaMeasureComplete))) {
            if (*(bloodPressure) <= 80 && *(bloodPressure) >=50 ) {
                *diaPres  = *bloodPressure;
                *diaMeasureComplete = TRUE;

                digitalWrite(LED_BUILTIN, HIGH);
                delay(100);
                digitalWrite(LED_BUILTIN, LOW);
                delay(100);
            } 
        }
        delay(300);
        

    }
    *sysMeasureComplete = FALSE;
    *diaMeasureComplete = FALSE;
    */
    
    if (*patient == -1) {
        *patient = random(0, 3);
    }

    
    if (!(*(sysMeasureComplete))) {
        if (*patient == 0) {
            if (*(bloodPressure) >= 110 && *(bloodPressure) <= 130) {
                *sysPres = *bloodPressure;
                *sysMeasureComplete = TRUE;

                digitalWrite(LED_BUILTIN, HIGH);
                delay(100);
                digitalWrite(LED_BUILTIN, LOW);
                delay(100);
            }
        }
        else if (*patient == 1) {
            if (*(bloodPressure) >= 120 && *(bloodPressure) <= 140) {
                *sysPres = *bloodPressure;
                *sysMeasureComplete = TRUE;

                digitalWrite(LED_BUILTIN, HIGH);
                delay(100);
                digitalWrite(LED_BUILTIN, LOW);
                delay(100);
            }
        }
        else if (*patient == 2) {
            if (*(bloodPressure) >= 130 && *(bloodPressure) <= 150) {
                *sysPres = *bloodPressure;
                *sysMeasureComplete = TRUE;

                digitalWrite(LED_BUILTIN, HIGH);
                delay(100);
                digitalWrite(LED_BUILTIN, LOW);
                delay(100);
            }
        }
    }
    else if (!(*(diaMeasureComplete))) {
        if (*patient == 0) {
            if (*(bloodPressure) <= 60 && *(bloodPressure) >= 50 ) {
                *diaPres  = *bloodPressure;
                *diaMeasureComplete = TRUE;

                digitalWrite(LED_BUILTIN, HIGH);
                delay(100);
                digitalWrite(LED_BUILTIN, LOW);
                delay(100);
            }
        }
        else if (*patient == 1) {
            if (*(bloodPressure) <= 70 && *(bloodPressure) >= 60) {
                *diaPres  = *bloodPressure;
                *diaMeasureComplete = TRUE;

                digitalWrite(LED_BUILTIN, HIGH);
                delay(100);
                digitalWrite(LED_BUILTIN, LOW);
                delay(100);
            }
        }
        else if (*patient == 2) {
            if (*(bloodPressure) <= 80 && *(bloodPressure) >= 70) {
                *diaPres  = *bloodPressure;
                *diaMeasureComplete = TRUE;

                digitalWrite(LED_BUILTIN, HIGH);
                delay(100);
                digitalWrite(LED_BUILTIN, LOW);
                delay(100);
            }
        }
    }

    if (*sysMeasureComplete && *diaMeasureComplete) {
        sysMeasureComplete = FALSE;
        diaMeasureComplete = FALSE;
        *patient = -1;
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
    unsigned long halfPeriod = pulseIn(PULSE_IN, LOW, 2000000UL);
    double halfPeriodInS = (1.0 * halfPeriod) / 1000000;
    int pulse = (int) 1 / (2 * halfPeriodInS);

    *pulseRate = pulse;
    
}

void measureRespiration(unsigned int *respirationRaw) {
    unsigned long halfPeriod = pulseIn(PULSE_IN, LOW, 2000000UL);
    double halfPeriodInS = (1.0 * halfPeriod) / 1000000;
    int freq = (int) 1 / (2 * halfPeriodInS);

    // map freq (range [10, 200]) to resp (range [1, 14])
    int resp = (int)(((freq - 10.0)/(200 - 10.0)) * (14.33 - 1.0) + 1.0);

    *respirationRaw = resp;
}
