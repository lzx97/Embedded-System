#ifndef TASKS_H
#define TASKS_H
#include <math.h>
#include <stdio.h>
#include "DataStructs.h"

void measurefun(void *measureStruct);
void measureTemp(unsigned int *temperature, Bool *tempIncrease, unsigned int *numOfMeasureCalls);
void measureSysPres(unsigned int *sysPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measureDiaPres(unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measurePulseRate(unsigned int *pulseRate, Bool *bpIncrease, unsigned int *numOfMeasureCalls);
void computefun(void *computeStruct);
void displayfun(void *displayStruct);
void annuciatefun(void *warningAlarmStruct);
void statusfun(void *statusStruct);
void schedulefun(void *taskQueue);
void delay_ms(unsigned int time_in_ms);

#endif
