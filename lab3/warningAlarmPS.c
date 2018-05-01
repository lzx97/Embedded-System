#include "DataStructs.h"

void warningAlarm(void *warningAlarmStruct) {
    WarningAlarmDataPS *wData = (WarningAlarmDataPS*) warningAlarmStruct;
    if ((globalCounter % *(wData->warningInterval)) != 0){
    return;
    }
    // Battery
    *(wData->batteryLow) = (((*(wData->batteryState)) < 40) ?  TRUE : FALSE);
    if (*(wData->bpSelection)){
    // syst
    *(wData->bpHigh) = ((((*(wData->sysNumeric)) > 130) || (*(wData->sysNumeric) < 120)) ? TRUE : FALSE);
    *(wData->bpAlarmHigh) = (((*(wData->sysNumeric)) > 130*1.20) ? TRUE : FALSE);
    // Update how many times in a row blood pressure has been at an alarm level
    if (*(wData->bpAlarmHigh)){
        (*(wData->bpAlarmCount))++;
    } else {
        (*(wData->bpAlarmCount)) = 0;
    }
    // dias
    *(wData->bpLow) = (((*(wData->diasNumeric)) > 80) || ((*(wData->diasNumeric)) <  70) ? TRUE : FALSE);
    }
    if (*(wData->pulseSelection)){
    // pulserate
    *(wData->pulseOff) = ((((*(wData->pulseNumeric)) < 60) || ((*(wData->pulseNumeric)) > 100)) ? TRUE : FALSE);
    }
    if (*(wData->tempSelection)){
    // Temperature, CHECK IF this is alarm or warning!
    *(wData->tempOff) = ((*(wData->tempNumeric) > 37.8) || (*(wData->tempNumeric) < 36.1)) ? TRUE : FALSE;
    }

}
