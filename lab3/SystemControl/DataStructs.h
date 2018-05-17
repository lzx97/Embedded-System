#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <stdio.h>
#include "Bool.h"


// implemented as linked list

typedef struct {
  // Raw
  char (*temperatureRawBuf)[16];
  char (*bloodPressRawBuf)[40];
  char (*pulseRateRawBuf)[24];

  // Measurement seleciton
  Bool *tempSelection;
  Bool *bpSelection;
  Bool *pulseSelection;

  // Variables to update values
  unsigned int *globalTime;
  unsigned int *measureInterval;
  // TCB *MeasureTCB;
  // TCB* ComputeTCB;
} MeasureData;

typedef struct {
  // Corrected
  char (*tempCorrectedBuf)[32];
  char (*bloodPressCorrectedBuf)[48];
  char (*pulseRateCorrectedBuf)[24];
  Bool *tempSelection;
  Bool *bpSelection;
  Bool *pulseSelection;
  unsigned int *globalTime;
  unsigned int *computeInterval;
} ComputeData;

typedef struct {
  // Measured Raw data
  char (*temperatureRawBuf)[16];
  char (*bloodPressRawBuf)[40];
  char (*pulseRateRawBuf)[24];
  char (*batteryState)[3];
  char (*tempCorrectedBuf)[32];
  char (*bloodPressCorrectedBuf)[48];
  char (*pulseRateCorrectedBuf)[24];
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
  char (*tempCorrectedBuf)[32];
  char (*bloodPressCorrectedBuf)[48];
  char (*pulseRateCorrectedBuf)[24];
  char (*batteryState)[3];


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
struct TCB {
  void *taskDataPtr;
  void (*taskPtr)(void*);
  struct TCB* next; // TCB* next
  struct TCB* prev; // TCB* prev
};


#endif
