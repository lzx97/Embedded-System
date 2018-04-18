#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include "Bool.h"

typedef struct {
    unsigned int *globalTime;
    unsigned int *measureInterval;
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    Bool sysMeasureComplete;
    Bool diaMeasureComplete;
    Bool tempIncrease;
    Bool bpIncrease;
    unsigned int numOfMeasureCalls;
} MeasureData;

typedef struct {
    unsigned int *globalTime;
    unsigned int *computeInterval;
    // Raw
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    // Corrected
    unsigned char **tempCorrected;
    unsigned char **sysPressCorrected;
    unsigned char **diasCorrected;
    unsigned char **prCorrected;
    double *tempNumeric;
    unsigned int *sysNumeric;
    unsigned int *diasNumeric;
    unsigned int *pulseNumeric;
} ComputeData;

typedef struct {
    unsigned int *globalTime;
    unsigned int *displayInterval;
    unsigned char **tempCorrected;
    unsigned char **sysPressCorrected;
    unsigned char **diasCorrected;
    unsigned char **prCorrected;
    unsigned short *batteryState;
    Bool *bpHigh;
    Bool *bpLow;
    Bool *tempOff;
    Bool *pulseOff;
    Bool *batteryLow;
    unsigned char *bpOutOfRange;
    unsigned char *tempOutOfRange;
    unsigned char *pulseOutOfRange;
} DisplayData;

typedef struct {
    unsigned int *globalTime;
    unsigned int *statusInterval;
    unsigned int *warningInterval;
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    unsigned short *batteryState;
    unsigned char *bpOutOfRange;
    unsigned char *tempOutOfRange;
    unsigned char *pulseOutOfRange;
    Bool *bpHigh;
    Bool *bpLow;
    Bool *tempOff;
    Bool *pulseOff;
    Bool *batteryLow;
    double *tempNumeric;
    unsigned int *sysNumeric;
    unsigned int *diasNumeric;
    unsigned int *pulseNumeric;
} WarningAlarmData;

typedef struct {
    unsigned int *globalTime;
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
