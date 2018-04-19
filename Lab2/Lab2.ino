#include "Bool.h"
#include <stdio.h>
#include "DataStructs.h"
#include "tasks.h"

TCB* taskQueue[5];
TCB MeasureTCB;
TCB ComputeTCB;
TCB DisplayTCB;
TCB WarningAlarmTCB;
TCB StatusTCB;


unsigned int globalTime = 0;
Bool sysMeasureComplete = FALSE;
Bool diaMeasureComplete = FALSE;
Bool tempIncrease = TRUE;
Bool bpIncrease = TRUE;
unsigned int numOfMeasureCalls = 0;

unsigned int measureInterval = 5;
unsigned int computeInterval = 5;
unsigned int displayInterval = 5;
unsigned int warningInterval = 1;
unsigned int statusInterval = 5;

unsigned int temperatureRaw = 75;
unsigned int systolicPressRaw = 80;
unsigned int diastolicPressRaw = 80;
unsigned int pulseRateRaw = 50;

double tempNumeric = 0;
unsigned int sysNumeric = 0;
unsigned int diasNumeric = 0;
unsigned int pulseNumeric = 0;

unsigned char *tempCorrected = NULL;
unsigned char *sysPressCorrected = NULL;
unsigned char *diasCorrected = NULL;
unsigned char *prCorrected = NULL;

unsigned short batteryState = 200;
unsigned char bpOutOfRange = 0;
unsigned char tempOutOfRange = 0;
unsigned char pulseOutOfRange = 0;

Bool bpHigh = FALSE;
Bool bpLow = FALSE;
Bool tempOff = FALSE;
Bool pulseOff = FALSE;
Bool batteryLow = FALSE;

MeasureData mData;
ComputeData cData;
DisplayData dData;
WarningAlarmData wData;
StatusData stData;
    
void setup(void) {
    
    setupDisplay();

    


    // Add variables to measure struct
    mData.globalTime = &globalTime;
    mData.measureInterval = &measureInterval;
    mData.diastolicPressRaw = &diastolicPressRaw;
    mData.systolicPressRaw = &systolicPressRaw;
    mData.pulseRateRaw = &pulseRateRaw;
    mData.temperatureRaw = &temperatureRaw;
    mData.sysMeasureComplete = &sysMeasureComplete;
    mData.diaMeasureComplete = &diaMeasureComplete;
    mData.tempIncrease = &tempIncrease;
    mData.bpIncrease = &bpIncrease;
    mData.numOfMeasureCalls = &numOfMeasureCalls;

    // Add variables to compute struct
    cData.globalTime = &globalTime;
    cData.diastolicPressRaw = &diastolicPressRaw;
    cData.computeInterval = &computeInterval;
    cData.systolicPressRaw = &systolicPressRaw;
    cData.pulseRateRaw = &pulseRateRaw;
    cData.temperatureRaw = &temperatureRaw;
    cData.diasCorrected = &diasCorrected;
    cData.sysPressCorrected = &sysPressCorrected;
    cData.prCorrected = &prCorrected;
    cData.tempCorrected = &tempCorrected;
    cData.tempNumeric = &tempNumeric;
    cData.sysNumeric = &sysNumeric;
    cData.diasNumeric = &diasNumeric;
    cData.pulseNumeric = &pulseNumeric;

    // Add variables to display struct
    dData.globalTime = &globalTime;
    dData.displayInterval = &displayInterval;
    dData.diasCorrected = &diasCorrected;
    dData.sysPressCorrected = &sysPressCorrected;
    dData.prCorrected = &prCorrected;
    dData.tempCorrected = &tempCorrected;
    dData.bpHigh = &bpHigh;
    dData.bpLow = &bpLow;
    dData.tempOff = &tempOff;
    dData.pulseOff = &pulseOff;
    dData.bpOutOfRange = &bpOutOfRange;
    dData.pulseOutOfRange = &pulseOutOfRange;
    dData.tempOutOfRange = &tempOutOfRange;
    dData.batteryLow = &batteryLow;
    dData.tempNumeric = &tempNumeric;
    dData.sysNumeric = &sysNumeric;
    dData.diasNumeric = &diasNumeric;
    dData.pulseNumeric = &pulseNumeric;
    dData.batteryState = &batteryState;
    dData.displayInterval = &measureInterval;
    dData.diastolicPressRaw = &diastolicPressRaw;
    dData.systolicPressRaw = &systolicPressRaw;
    dData.pulseRateRaw = &pulseRateRaw;
    dData.temperatureRaw = &temperatureRaw;


    // Add values to warning/alarm struct
    wData.globalTime = &globalTime;
    wData.warningInterval = &warningInterval;
    wData.diastolicPressRaw = &diastolicPressRaw;
    wData.systolicPressRaw = &systolicPressRaw;
    wData.pulseRateRaw = &pulseRateRaw;
    wData.temperatureRaw = &temperatureRaw;
    wData.bpOutOfRange = &bpOutOfRange;
    wData.pulseOutOfRange = &pulseOutOfRange;
    wData.tempOutOfRange = &tempOutOfRange;
    wData.batteryState = &batteryState;
    wData.bpHigh = &bpHigh;
    wData.bpLow = &bpLow;
    wData.tempOff = &tempOff;
    wData.pulseOff = &pulseOff;
    wData.batteryLow = &batteryLow;
    wData.tempNumeric = &tempNumeric;
    wData.sysNumeric = &sysNumeric;
    wData.diasNumeric = &diasNumeric;
    wData.pulseNumeric = &pulseNumeric;

    // Add data to status struct
    stData.globalTime = &globalTime;
    stData.statusInterval = &statusInterval;
    stData.batteryState = &batteryState;


    // Initialize the TCBs
    MeasureTCB.taskPtr = &measureData;
    MeasureTCB.taskDataPtr = (void*)&mData;

    ComputeTCB.taskPtr = &computeData;
    ComputeTCB.taskDataPtr = (void*)&cData;

    DisplayTCB.taskPtr = &displayData;
    DisplayTCB.taskDataPtr = (void*)&dData;

    WarningAlarmTCB.taskPtr = &annuciate;
    WarningAlarmTCB.taskDataPtr = (void*)&wData;

    StatusTCB.taskPtr = &batteryStatus;
    StatusTCB.taskDataPtr = (void*)&stData;

    // Initialize the taskQueue
    taskQueue[0] = &MeasureTCB;
    taskQueue[1] = &ComputeTCB;
    taskQueue[2] = &DisplayTCB;
    taskQueue[3] = &WarningAlarmTCB;
    taskQueue[4] = &StatusTCB;
}


void loop(void) {
    schedulefun(taskQueue);
}

