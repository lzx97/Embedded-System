#ifndef MEASURE
#define MEASURE

#include "Bool.h"

#define PIN_IN 7

void measurePS(void *measureStruct);
void measureTemp(unsigned int *temperature, Bool *tempIncrease, unsigned int *numOfMeasureCalls);
void measureSysPres(unsigned int *sysPres, Bool *sysMeasureComplete, 
    Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measureDiaPres(unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, 
    unsigned int *numOfMeasureCalls);
void measurePulseRate(unsigned int *pulseRate);

#endif
