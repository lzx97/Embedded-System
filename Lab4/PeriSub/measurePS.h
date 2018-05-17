#ifndef MEASURE
#define MEASURE

#include "Bool.h"

#define PULSE_IN 7
#define SYS_IN 2
#define DIA_IN 4

void measurePS(void *measureStruct);
void measureTemp(unsigned int *temperature, Bool *tempIncrease, unsigned int *numOfMeasureCalls);
void measureSysPres(unsigned int *sysPres, Bool *sysMeasureComplete, 
    Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measureDiaPres(unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, 
    unsigned int *numOfMeasureCalls);
void measurePulseRate(unsigned int *pulseRate);

#endif
