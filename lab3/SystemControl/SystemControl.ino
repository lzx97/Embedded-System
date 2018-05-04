#include "Bool.h"
#include <stdio.h>
#include "DataStructs.h"
#include "batteryStatusSC.h"
#include "measureSC.h"
#include "peripheralCom.h"
#include "TFTKeypad.h"

TCB* head;
TCB* tail;

TCB MeasureTCB;
TCB ComputeTCB;
TCB tftTCB;
TCB WarningAlarmTCB;
TCB StatusTCB;

unsigned int globalTime = 0; // Change this to millis
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
Bool sysAlarm = FALSE;

Bool tempSelection = TRUE;
Bool bpSelection = TRUE;
Bool pulseSelection = TRUE;
Bool alarmAcknowledge = TRUE; // type TBD
unsigned int alarmTimer = 0;

MeasureData mData;
ComputeData cData;
TFTData dData;
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
    mData.MeasureTCB = &MeasureTCB;
    mData.ComputeTCB = &ComputeTCB;

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
    dData.bloodPressCorrectedBuf = &bloodPressCorrectedBuf;
    dData.prCorrectedBuf = &prCorrectedBuf;
    dData.tempCorrectedBuf = &tempCorrectedBuf;
    dData.bloodPressRawBuf = &bloodPressRawBuf;
    dData.pulseRateRawBuf = &pulseRateRawBuf;
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
    dData.displayInterval = &displayInterval;
    dData.tempSelection = &tempSelection;
    dData.bpSelection = &bpSelection;
    dData.pulseSelection = &pulseSelection;
    dData.alarmAcknowledge = &alarmAcknowledge;
    dData.alarmTimer = &alarmTimer;
    dData.sysAlarm = &sysAlarm;


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
    wData.sysAlarm = &sysAlarm;

    // Add data to status struct
    stData.globalTime = &globalTime;
    stData.statusInterval = &statusInterval;
    stData.batteryState = &batteryState;


    // Initialize the TCBs
    MeasureTCB.taskPtr = &measureData;
    MeasureTCB.taskDataPtr = (void*)&mData;
    MeasureTCB.prev = NULL;
    MeasureTCB.next = &ComputeTCB;

    ComputeTCB.taskPtr = &computeData;
    ComputeTCB.taskDataPtr = (void*)&cData;
    ComputeTCB.prev = &MeasureTCB;
    ComputeTCB.next = &tftTCB;

    tftTCB.taskPtr = &TFTData;
    tftTCB.taskDataPtr = (void*)&dData;
    tftTCB.prev = &ComputeTCB;
    tftTCB.next = &WarningAlarmTCB;

    WarningAlarmTCB.taskPtr = &annuciate;
    WarningAlarmTCB.taskDataPtr = (void*)&wData;
    WarningAlarmTCB.prev = &tftTCB;
    WarningAlarmTCB.next = &StatusTCB;

    StatusTCB.taskPtr = &batteryStatus;
    StatusTCB.taskDataPtr = (void*)&stData;
    StatusTCB.prev = &WarningAlarmTCB;
    StatusTCB.next = NULL;

    // Initialize the taskQueue
    head = &MeasureTCB;
    tail = &StatusTCB;

}


void loop(void) {
    start_time = millis();
    schedule();
    (*globalTime)++;
    while (millis() < start_time + 1000){ 
        // Wait until one second has passed
    }
}

