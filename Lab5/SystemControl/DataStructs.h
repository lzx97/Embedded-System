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
  char (*respirationRateRawBuf)[16];

  // Measurement seleciton
  Bool *tempSelection;
  Bool *bpSelection;
  Bool *pulseSelection;
  Bool *respSelection;

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
  char (*respirationRateCorrectedBuf)[16];
  Bool *tempSelection;
  Bool *bpSelection;
  Bool *pulseSelection;
  Bool *respSelection;
  unsigned int *globalTime;
  unsigned int *computeInterval;
} ComputeData;

typedef struct {
  // Measured Raw data
  char (*temperatureRawBuf)[16];
  char (*bloodPressRawBuf)[40];
  char (*pulseRateRawBuf)[24];
  char (*respirationRateRawBuf)[16];
  char (*batteryState)[3];
  char (*tempCorrectedBuf)[32];
  char (*bloodPressCorrectedBuf)[48];
  char (*pulseRateCorrectedBuf)[24];
  char (*respirationRateCorrectedBuf)[16];
  // Warning flags
  Bool *pulseWarning;
  Bool *pulseAlarm;
  Bool *tempWarning;
  Bool *tempAlarm;
  Bool *sysWarning;
  Bool *diasWarning;
  Bool *sysAlarm;
  Bool *respAlarm;
  Bool *batteryLow;
  unsigned int *globalTime;
  unsigned int *warningInterval;

  Bool *sysAlarmAcknowledge;
  unsigned int *sysAlarmTimer;
  Bool *tempAlarmAcknowledge;
  unsigned int *tempAlarmTimer;
  Bool *pulseAlarmAcknowledge;
  unsigned int *pulseAlarmTimer;
  Bool *respAlarmAcknowledge;
  unsigned int *respAlarmTimer;

} WarningAlarmData;

typedef struct {
  // Warning flags
  Bool *pulseWarning;
  Bool *pulseAlarm;
  Bool *tempWarning;
  Bool *tempAlarm;
  Bool *sysWarning;
  Bool *diasWarning;
  Bool *sysAlarm;
  Bool *respAlarm;
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
  char (*respirationRateCorrectedBuf)[16];
  char (*batteryState)[3];


  // Specified by lab spec, more fields to be added
  Bool *tempSelection;
  Bool *bpSelection;
  Bool *pulseSelection;
  Bool *respSelection;
  Bool *EKGSelection;
  Bool *justPressed;

  unsigned int *globalTime;
  unsigned int *displayInterval;
  unsigned long *timeNow;
  Bool *sysAlarmAcknowledge;
  unsigned int *sysAlarmTimer;
  Bool *tempAlarmAcknowledge;
  unsigned int *tempAlarmTimer;
  Bool *pulseAlarmAcknowledge;
  unsigned int *pulseAlarmTimer;
  Bool *respAlarmAcknowledge;
  unsigned int *respAlarmTimer;

  Bool *sysFlash;
  Bool *diasFlash;
  Bool *tempFlash;
  Bool *pulseFlash;
  Bool *displayOff;
  unsigned long *lastSysFlash;
  unsigned long *lastDiasFlash;
  unsigned long *lastTempFlash;
  unsigned long *lastPulseFlash;
} TFTData;

typedef struct {
  Bool *tempSelection;
  Bool *bpSelection;
  Bool *pulseSelection;
  Bool *respSelection;
  char (*tempCorrectedBuf)[32];
  char (*bloodPressCorrectedBuf)[48];
  char (*pulseRateCorrectedBuf)[24];
  char (*respirationRateCorrectedBuf)[16];
  unsigned int *globalTime;
} ComData;

typedef struct {
  char (*batteryState)[3]; // pointer to char array of size 5
  unsigned int *globalTime;
  unsigned int *statusInterval;
} StatusData;

typedef struct {
  double (*vReal)[256];
  double (*vImag)[256];

} EKGCapData;

typedef struct {
  double (*vReal)[256];
  double (*vImag)[256];
  double (*freqBuf)[16];

} EKGProData;



typedef struct TCB TCB; // This line is to be able to use TCB as a field inside TCB
struct TCB {
  void *taskDataPtr;
  void (*taskPtr)(void*);
  struct TCB* next; // TCB* next
  struct TCB* prev; // TCB* prev
};


#endif
