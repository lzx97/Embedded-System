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
void computeSC() {

}