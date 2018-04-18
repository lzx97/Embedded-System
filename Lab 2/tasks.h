#include <math.h>
#include <stdio.h>
#include "DataStructs.h"

void measure(void *measureStruct);
void measureTemp(unsigned int *temperature, Bool *tempIncrease, unsigned int *numOfMeasureCalls);
void measureSysPres(unsigned int *sysPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measureDiaPres(unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measurePulseRate(unsigned int *pulseRate, Bool *bpIncrease, unsigned int *numOfMeasureCalls);
void compute(void *computeStruct);
void display(void *displayStruct);
void annuciate(void *warningAlarmStruct);
void status(void *statusStruct);