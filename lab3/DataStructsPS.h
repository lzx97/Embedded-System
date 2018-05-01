#ifndef DATASTRUCTSPS_H
#define DATASTRUCTSPS_H
#include <stdio.h>
#include "Bool.h"

typedef struct {
    unsigned int *globalTime;
    unsigned int *measureInterval;
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    Bool *sysMeasureComplete;
    Bool *diaMeasureComplete;
    Bool *tempIncrease;
    Bool *bpIncrease;
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
    unsigned int *numOfMeasureCalls;
} MeasureDataPS;

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
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
} ComputeDataPS;
/*
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
    double *tempNumeric;
    unsigned int *sysNumeric;
    unsigned int *diasNumeric;
    unsigned int *pulseNumeric;
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
} DisplayData;
*/
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
    Bool *bpAlarmHigh;
    unsigned int *bpAlarmCount;
    Bool *bpLow;
    Bool *tempOff;
    Bool *pulseOff;
    Bool *batteryLow;
    double *tempNumeric;
    unsigned int *sysNumeric;
    unsigned int *diasNumeric;
    unsigned int *pulseNumeric;
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
} WarningAlarmDataPS;

typedef struct {
    unsigned int *globalTime;
    unsigned short *batteryState;
    unsigned int *statusInterval;

} StatusDataPS;

typedef struct {
    unsigned int *globalTime;
} PeripheralComPS;


/*
typedef struct SchedulerStruct {
    // None for this lab
    // may be used for future labs
} SchedulerData;
*/
/*
typedef struct {
    void *taskDataPtr;
    void (*taskPtr)(void*);
} TCB;
*/
#endif
