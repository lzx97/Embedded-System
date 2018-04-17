#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include "bool.h"

typedef struct MeasureStruct {
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
} MeasureData;

typedef struct ComputeStruct {
    // Raw
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    // Corrected
    unsigned int *tempCorrected;
    unsigned int *sysPressCorrected;
    unsigned int *diasCorrected;
    unsigned int *prCorrected;
} ComputeData;

typedef struct DisplayStruct {
    unsigned int *tempCorrected;
    unsigned int *sysPressCorrected;
    unsigned int *diasCorrected;
    unsigned int *prCorrected;
    unsigned short *batteryState;
    Bool *bpHigh;
    Bool *tempHigh;
    Bool *pulseLow;
} DisplayData;

typedef struct WarningAlarmStruct {
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    unsigned short *batteryState;
    Bool *bpHigh;
    Bool *tempHigh;
    Bool *pulseLow;
} WarningAlarmData;

typedef struct StatusStruct {
    unsigned short *batteryState;
} StatusData;

/* typedef struct SchedulerStruct {
    // None for this lab
    // may be used for future labs
} SchedulerData;*/ 

#endif