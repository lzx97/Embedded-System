#include "DataStructsPs.h"

void computePS(void *computeStruct) {
    ComputeDataPS *cData = (ComputeDataPS*) computeStruct;

    float temp = 5 + 0.75 * (*(cData->temperatureRaw));
    unsigned int systolicPres = (unsigned int) 9 + 2 * (*(cData->systolicPressRaw));
    unsigned int diastolicPres = (unsigned int) floor(6 + 1.5 * (*(cData->diastolicPressRaw)));
    unsigned int pr = (unsigned int) 8 + 3 * (*(cData->pulseRateRaw));

    *(cData->tempCorrected) = temp;
    *(cData->systolicPressCorrected) = systolicPres;
    *(cData->diastolicPressCorrected) = diastolicPres;
    *(cData->pulseRateCorrected) = pr;
}