#include <stdio.h>
#include "DataStructs.h"

int globalCounter;

void computePS(void *computeStruct) {
    // TODO: modify lab 2 codes according to the new spec
    ComputeData *cData = (ComputeData*) computeStruct;
    if (globalCounter % 5 != 0){
        return;
    }

    float temp = 5 + 0.75 * (*(cData->temperatureRaw));
    unsigned int systolicPres = (unsigned int) 9 + 2 * (*(cData->systolicPressRaw));
    unsigned int diastolicPres = (unsigned int) floor(6 + 1.5 * (*(cData->diastolicPressRaw)));
    unsigned int pr = (unsigned int) 8 + 3 * (*(cData->pulseRateRaw));

    *(cData->tempNumeric) = temp;
    *(cData->sysNumeric) = systolicPres;
    *(cData->diasNumeric) = diastolicPres;
    *(cData->pulseNumeric) = pr;
}

// SC part of the compute. Send data packet to call compute. 
void computeSC(void *computeStruct) {
    // create string to be sent to the PS
    char start = 2;
    char stop = 3;
    char str[30];
    str[0] = 'C';
    str[1] = 'B'; // To be changed after implemented TFTKeypad
    str[2] = 'T'; // To be changed after implemented TFTKeypad
    str[3] = 'P'; // To be changed after implemented TFTKeypad
    strcat(str, &start);
    strcat(str, "Starting compute");
    strcat(str, &stop);

    // transfer and receive 
    com(char *data, void *dataStruct);
}