#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <stdio.h>
#include "Bool.h"


// implemented as linked list

typedef struct {
    // Raw
    unsigned int *temperatureRawBuf; 
    unsigned int *bloodPressRawBuf;
    unsigned int *pulseRateRawBuf;
    /*
    unsigned int *diastolicPressRaw;
    unsigned int *systolicPressRaw;
    unsigned int *pulseRateRaw;
    unsigned int *temperatureRaw;
    */
    // Measurement seleciton
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;

    // Variables to update values
    Bool *sysMeasureComplete;
    Bool *diaMeasureComplete;
    Bool *tempIncrease;
    Bool *bpIncrease;
    unsigned int *numOfMeasureCalls;
    unsigned int *globalTime;
    unsigned int *measureInterval;
   // TCB *MeasureTCB;
   // TCB* ComputeTCB;
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
    
    // Measurement selection
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
    unsigned int *sysNumeric;
    unsigned int *diasNumeric;
    unsigned int *pulseNumeric;
    float *tempNumeric;
    unsigned int *globalTime;
} ComputeData;

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
    float *tempNumeric;
    unsigned int *sysNumeric;
    unsigned int *diasNumeric;
    unsigned int *pulseNumeric;
    unsigned int *globalTime;
    Bool *sysAlarm;
    Bool *alarmAcknowledge; // type TBD
    unsigned int *warningInterval;
    unsigned int *alarmTimer;
} WarningAlarmData;

typedef struct {
      // Warning flags
    Bool *bpHigh;
    Bool *bpLow;
    Bool *tempOff;
    Bool *pulseOff;
    Bool *batteryLow;
    /*
    unsigned char *bpOutOfRange;
    unsigned char *tempOutOfRange;
    unsigned char *pulseOutOfRange;
    */
    // Data to be displayed
    
    float *tempCorrectedBuf;
    unsigned int bloodPressCorrectedBuf;
    unsigned int *pulseRateCorrectedBuf;
    unsigned short *batteryState;
    // Test data
    unsigned int *pulseNumeric;
    unsigned int *diasNumeric;
    unsigned int *sysNumeric;
    float *tempNumeric;
    
    unsigned int *temperatureRawBuf;
    unsigned int *bloodPressRawBuf;
    unsigned int *pulseRateRawBuf;
    // Specified by lab spec, more fields to be added
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
    Bool *sysAlarm;
    Bool *justPressed;
    unsigned int *alarmTimer;
    Bool *alarmAcknowledge; // type TBD
    unsigned int *globalTime;
    unsigned int *displayInterval;
    unsigned long *timeNow;
    Bool *justPressed
} TFTData;

typedef struct {
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
    float *tempCorrectedBuf;
    unsigned int *bloodPressCorrectedBuf;
    unsigned int *pulseRateCorrectedBuf;
    unsigned int *globalTime;
} ComData;

typedef struct {
    char (*batteryState)[3]; // pointer to char array of size 5
    unsigned int *globalTime;
    unsigned int *statusInterval;
} StatusData;


typedef struct TCB TCB; // This line is to be able to use TCB as a field inside TCB
struct TCB{
    void *taskDataPtr;
    void (*taskPtr)(void*);
    struct TCB* next; // TCB* next
    struct TCB* prev; // TCB* prev
};


#endif
