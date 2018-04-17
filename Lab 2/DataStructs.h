#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include "Bool.h"

typedef struct {
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
} MeasureData;

typedef struct {
    // Raw
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    // Corrected
    unsigned char *tempCorrected;
    unsigned char *sysPressCorrected;
    unsigned char *diasCorrected;
    unsigned char *prCorrected;
} ComputeData;

typedef struct {
    unsigned int *tempCorrected;
    unsigned int *sysPressCorrected;
    unsigned int *diasCorrected;
    unsigned int *prCorrected;
    unsigned short *batteryState;
    Bool *bpHigh;
    Bool *bpLow;
    Bool *tempHigh;
    Bool *pulseLow;
    unsigned char *bpOutOfRange;
    unsigned char *tempOutOfRange;
    unsigned char *pulseOutOfRange;
} DisplayData;

typedef struct {
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    unsigned short *batteryState;
    unsigned char bpOutOfRange;
    unsigned char tempOutOfRange;
    unsigned char pulseOutOfRange;
    Bool *bpHigh;
    Bool *bpLow;
    Bool *tempHigh;
    Bool *pulseLow;
    unsigned char *bpOutOfRange;
    unsigned char *tempOutOfRange;
    unsigned char *pulseOutOfRange; 
} WarningAlarmData;

typedef struct {
    unsigned short *batteryState;
} StatusData;

/* typedef struct SchedulerStruct {
    // None for this lab
    // may be used for future labs
} SchedulerData;*/

typedef struct {
    void *taskDataPtr;
    void (*taskPtr)(void*);
} TCB;

#endif
