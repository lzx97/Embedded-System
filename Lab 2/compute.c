#include <math.h>
#include "DataStructs.h"

// Set cData values to chars
void compute(void *computeStruct) {
    ComputeData *cData = (ComputeData*) computeStruct;
    *(cData->tempCorrected) = (int) floor(5 + 0.75 * (*(cData->temperatureRaw)));
    *(cData->sysPressCorrected) = (int) floor(9 + 2 * (*cData->systolicPressRaw));
    *(cData->diasCorrected) = (int) floor(6 + 1.5 * (*cData->diastolicPressRaw));
    *(cData->prCorrected) = (int) floor(8 + 3 * (*cData->pulseRateRaw));
}
