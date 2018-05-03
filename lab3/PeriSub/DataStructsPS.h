#ifndef DATASTRUCTSPS_H
#define DATASTRUCTSPS_H
#include <stdio.h>
#include "Bool.h"

typedef struct {
	// Raw
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
	// Flags for simulating
    Bool *sysMeasureComplete;
    Bool *diaMeasureComplete;
    Bool *tempIncrease;
    Bool *bpIncrease;
	// Flags for selection
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
	// For simulation
    unsigned int *numOfMeasureCalls;
} MeasureDataPS;

typedef struct {
    // Raw
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    // Corrected
    float *tempCorrected;
    unsigned int *systolicPressCorrected;
    unsigned int *diastolicPressCorrected;
    unsigned int *pulseRateCorrected;
	// Flags
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
	// Raw data
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    unsigned short *batteryState;
	// warning & alarm flags
    Bool *bpOutOfRange;
    Bool *tempOutOfRange;
    Bool *pulseOutOfRange;
    Bool *bpHigh;
    Bool *bpAlarmHigh;
    unsigned int *bpAlarmCount;
    Bool *bpOff;
    Bool *tempOff;
    Bool *pulseOff;
    Bool *batteryLow;
	
    Bool *bpSelection;
    Bool *tempSelection;
    Bool *pulseSelection;
} WarningAlarmDataPS;

typedef struct {
    unsigned short *batteryState;

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
