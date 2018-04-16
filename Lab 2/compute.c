#include <math.h>
#include "DataStructs.h"

void compute(void *computeStruct) {
    ComputeData *cData = (ComputeData*) computeStruct;
    *(cData->tempCorrected) = (int) floor(5 + 0.75 * (*(cData->temperatureRaw)));
    *(cData->sysPressCorrected)  = (int) floor(9 + 2 * (*cData->systolicPressRaw));
    *(cData->)
}