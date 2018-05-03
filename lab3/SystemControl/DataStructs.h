#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <stdio.h>
#include "Bool.h"

typedef struct {
    unsigned int *temperatureRawBuf;
    unsigned int *bloodPressRawBuf;
    unsigned int *pulseRateRawBuf;
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
    Bool *sysMeasureComplete;
    Bool *diaMeasureComplete;
    Bool *tempIncrease;
    Bool *bpIncrease;
    unsigned int *numOfMeasureCalls;
} MeasureData;

typedef struct {
    // Raw
    unsigned int *temperatureRawBuf;
    unsigned int *bloodPressRawBuf;
    unsigned int *pulseRateRawBuf;
    // Corrected
    float *tempCorrectedBuf;
    unsigned int *bloodPressCorrectedBuf;
    unsigned int *prCorrectedBuf;
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
} ComputeData;

typedef struct {
    // Warning flags
    Bool *bpHigh;
    Bool *bpLow;
    Bool *tempOff;
    Bool *pulseOff;
    Bool *batteryLow;
    unsigned char *bpOutOfRange;
    unsigned char *tempOutOfRange;
    unsigned char *pulseOutOfRange;
    // Data to be displayed
    float *tempCorrectedBuf;
    unsigned int *bloodPressCorrectedBuf;
    unsigned int *prCorrectedBuf;
    unsigned short *batteryState;
    // Test data
    unsigned int *temperatureRawBuf;
    unsigned int *bloodPressRawBuf;
    unsigned int *pulseRateRawBuf;
} DisplayData;

typedef struct {
    unsigned int *temperatureRawBuf;
    unsigned int *bloodPressRawBuf;
    unsigned int *pulseRateRawBuf;
    unsigned short *batteryState;
    // Warning flags
    unsigned char *bpOutOfRange;
    unsigned char *tempOutOfRange;
    unsigned char *pulseOutOfRange;
    Bool *bpHigh;
    Bool *bpLow;
    Bool *tempOff;
    Bool *pulseOff;
    Bool *batteryLow;
    // may be used for testing
    double *tempNumeric;
    unsigned int *sysNumeric;
    unsigned int *diasNumeric;
    unsigned int *pulseNumeric;
} WarningAlarmData;

typedef struct {
    // Specified by lab spec, more fields to be added
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
    unsigned int *alarmAcknowledge; // type TBD
} TFTData;

typedef struct {
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
    float *tempCorrectedBuf;
    unsigned int *bloodPressCorrectedBuf;
    unsigned int *prCorrectedBuf;
} ComData;

typedef struct {
    unsigned short *batteryState;

} StatusData;

// implemented as linked list
typedef struct {
    void *taskDataPtr;
    void (*taskPtr)(void*);
    struct TCB *prev;
    struct TCB *next;
} TCB;

#endif
