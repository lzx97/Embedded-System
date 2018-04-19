#include <math.h>
#include <stdio.h>
#include "DataStructs.h"

void measureData(void *measureStruct);
void measureTemp(unsigned int *temperature, Bool *tempIncrease, unsigned int *numOfMeasureCalls);
void measureSysPres(unsigned int *sysPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measureDiaPres(unsigned int *diaPres, Bool *sysMeasureComplete, Bool *diaMeasureComplete, unsigned int *numOfMeasureCalls);
void measurePulseRate(unsigned int *pulseRate, Bool *bpIncrease, unsigned int *numOfMeasureCalls);
void computeData(void *computeStruct);
void displayData(void *displayStruct);
void annuciate(void *warningAlarmStruct);
void batteryStatus(void *statusStruct);
void schedulefun(TCB **tasks);
void delay_ms(unsigned long time_in_ms);
void setupDisplay(void);
