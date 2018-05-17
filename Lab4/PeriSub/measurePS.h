#ifndef MEASURE
#define MEASURE

#include "Bool.h"

#define PULSE_IN 7
#define TEMP_IN 0;
#define INC 2
#define DEC 4

void measurePS(void *measureStruct);
void measureTemp(unsigned int *temperature);
void measureSysPres(unsigned int *sysPres, Bool *sysMeasureComplete, 
    Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measureDiaPres(unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, 
    unsigned int *numOfMeasureCalls);
void measurePulseRate(unsigned int *pulseRate);
void measureRespiration(unsigned int *respirationRaw);

#endif
