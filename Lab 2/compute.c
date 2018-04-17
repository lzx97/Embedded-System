#include <math.h>
#include "DataStructs.h"

// Set cData values to chars
void compute(void *computeStruct) {
    ComputeData *cData = (ComputeData*) computeStruct;
    int temp = (int) floor(5 + 0.75 * (*(cData->temperatureRaw)));
    int systolicPres = (int) floor(9 + 2 * (*cData->systolicPressRaw));
    int diastolicPres = (int) floor(6 + 1.5 * (*cData->diastolicPressRaw));
    int pr = (int) floor(8 + 3 * (*cData->pulseRateRaw));

    sprintf(*(cData->tempCorrected), "%d", temp);
    sprintf(*(cData->sysPressCorrected), "%d", systolicPres);
    sprintf(*(cData->diasCorrected), "%d", diastolicPres);
    sprintf(*(cData->prCorrected), "%d", pr);
}
