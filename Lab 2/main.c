#include "Bool.h"
#include <stdio.h>
#include "DataStructs.h"


void setup() {
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
    StatusData sData;

    TCB* taskQueue[5];

    void (measure)(void*);
    void (compute)(void*);
    void (display)(void*);
    void (status)(void*);
    void (annunciate)(void*);



    // HOW DO YOU INITIALIZE TCB?????

    //TCB taskQueue[5]; // Make a queue of TCB structs
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
