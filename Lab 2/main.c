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

    void (measure)(void*);
    void (compute)(void*);
    void (display)(void*);
    void (status)(void*);
    void (annunciate)(void*);

    // Define / initialize TCB structs somewhere here
    typedef struct TCB {
    void (*myTask)(void*);
    void* taskDataPtr;
    } TCB;


    struct TCB MeasureTCB = {.myTask = (*measure), .taskDataPtr = *MeasureData};
    struct TCB ComputeTCB;
    struct TCB DisplayTCB;
    struct TCB WarningAlarmTCB;
    struct TCB StatusTCB;

    TCB taskQueue[5]; // Make a queue of TCB structs
    taskQueue[0] = MeasureTCB;
    taskQueue[1] = ComputeTCB;
    taskQueue[2] = DisplayTCB;
    taskQueue[3] = WarningAlarmTCB;
    taskQueue[4] = StatusTCB;

}


void loop() {
    //while(1){
        ssschedule();
    //}
}
