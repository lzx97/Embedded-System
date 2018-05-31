#ifndef MEASURE
#define MEASURE

#include "Bool.h"

#define PULSE_IN 7
#define TEMP_IN 0
#define BP_INC 2
#define BP_DEC 3

void measurePS(void *measureStruct);
void measureTemp(unsigned int *temperature);
void measureBloodPres(unsigned int *sysPres, unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *bloodPressure, int *patient);
void measureSysPres(unsigned int *sysPres, Bool *sysMeasureComplete, 
    Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measureDiaPres(unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, 
    unsigned int *numOfMeasureCalls);
void measurePulseRate(unsigned int *pulseRate);
void measureRespiration(unsigned int *respirationRaw);

#endif
