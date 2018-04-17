#include "Bool.h"
#include <stdio.h>
#include "DataStructs.h"



void setup() {
    unsigned int globalTime = 0;
    Bool sysMeasureComplete = FALSE;
    Bool diaMeasureComplete = FALSE;
    Bool tempIncrease = TRUE;
    Bool bpIncrease = TRUE;
    unsigned int numOfMeasureCalls = 0;

    unsigned int temperatureRaw = 75;
    unsigned int systolicPressRaw = 80;
    unsigned int diastolicPressRaw = 80;
    unsigned int pulseRateRaw = 50;

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
    Bool tempHigh = FALSE;
    Bool pulseLow = FALSE;

    TCB MeasureTCB;
    TCB ComputeTCB;
    TCB DisplayTCB;
    TCB WarningAlarmTCB;
    TCB StatusTCB;

    MeasureData mData;
    ComputeData cData;
    DisplayData dData;
    WarningAlarmData wData;
    StatusData stData;

    TCB* taskQueue[5];

    // Should we use & or no?
    mData.diastolicPressRaw = &diastolicPressRaw;
    mData.systolicPressRaw = &systolicPressRaw;
    mData.pulseRateRaw = &pulseRateRaw;
    mData.temperatureRaw = &temperatureRaw;
    mData.sysMeasureComplete = &mData.sysMeasureComplete;
    mData.diaMeasureComplete = diaMeasureComplete;
    mData.tempIncrease = tempIncrease;
    mData.bpIncrease = bpIncrease;
    mData.numOfMeasureCalls = numOfMeasureCalls;

    cData.diastolicPressRaw = diastolicPressRaw;
    cData.systolicPressRaw = systolicPressRaw;
    cData.pulseRateRaw = pulseRateRaw;
    cData.temperatureRaw = temperatureRaw;
    cData.diasCorrected = diasCorrected;
    cData.sysPressCorrected = sysPressCorrected;
    cData.prCorrected = prCorrected;
    cData.tempCorrected = tempCorrected;

    dData.diasCorrected = diasCorrected;
    dData.sysPressCorrected = sysPressCorrected;
    dData.prCorrected = prCorrected;
    dData.tempCorrected = tempCorrected;
    dData.bpHigh = bpHigh;
    dData.bpLow = bpLow;
    dData.tempHigh = tempHigh;
    dData.pulseLow = pulseLow;
    dData.bpOutOfRange = bpOutOfRange;
    dData.pulseOutOfRange = pulseOutOfRange;
    dData.tempOutOfRange = tempOutOfRange;

    wData.diastolicPressRaw = diastolicPressRaw;
    wData.systolicPressRaw = systolicPressRaw;
    wData.pulseRateRaw = pulseRateRaw;
    wData.temperatureRaw = temperatureRaw;
    wData.bpOutOfRange = bpOutOfRange;
    wData.pulseOutOfRange = pulseOutOfRange;
    wData.tempOutOfRange = tempOutOfRange;
    wData.batteryState = batteryState;
    wData.bpHigh = bpHigh;
    wData.bpLow = bpLow;
    wData.tempHigh = tempHigh;
    wData.pulseLow = pulseLow;

    stData.batteryState = batteryState;


    // fucntions assigned to taskPtrs are undefined for now
    // need to include "measure.h" "compute.h" etc.
    // create .h header file for each .c file may be tedious
    // I'm thinking merge all five tasks fucntion together into one tasks.c?
    MeasureTCB.taskPtr = measure;
    MeasureTCB.taskDataPtr = (void*)&mData;

    ComputeTCB.taskPtr = compute;
    ComputeTCB.taskDataPtr = (void*)&cData;

    DisplayTCB.taskPtr = display;
    DisplayTCB.taskDataPtr = (void*)&dData;

    WarningAlarmTCB.taskPtr = annuniciate;
    WarningAlarmTCB.taskDataPtr = (void*)&wData;

    StatusTCB.taskPtr = status;
    StatusTCB.taskDataPtr = (void*)&stData;


    taskQueue[0] = &MeasureTCB;
    taskQueue[1] = &ComputeTCB;
    taskQueue[2] = &DisplayTCB;
    taskQueue[3] = &WarningAlarmTCB;
    taskQueue[4] = &StatusTCB;

}


void loop() {
    //while(1){
        ssschedule();
    //}
}
