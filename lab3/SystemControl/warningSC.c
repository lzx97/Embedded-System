#include "DataStructs.h"
#include "warningSC.h"
#include "Bool.h"


void annunciate(void *warningAlarmStruct) {
    WarningAlarmData *wData = (WarningAlarmData*) warningAlarmStruct;
    if ((*(wData->globalTime) % *(wData->warningInterval)) != 0){
    return;
    }
    // NOT ACTIVE DURING DEBUGGING
    /* 
    // Battery
    *(wData->batteryLow) = (((*(wData->batteryState)) < 40) ?  TRUE : FALSE);
    // syst
    *(wData->bpHigh) = (((*(wData->sysNumeric)) > 120) ? TRUE : FALSE);
    if (*(wData->alarmAcknowledge)){
        (*(wData->alarmTimer))++;
        if (*(wData->alarmTimer) > 5){
          (*(wData->sysAlarm)) = TRUE;
          (*(wData->alarmAcknowledge)) = FALSE;
        }
    }
    *(wData->sysAlarm) = (((*(wData->sysNumeric)) > 140) ? TRUE : FALSE);
    // dias
    *(wData->bpLow) = (((*(wData->diasNumeric)) < 80) ? TRUE : FALSE);
    // pulserate
    *(wData->pulseOff) = ((((*(wData->pulseNumeric)) < 60) || ((*(wData->pulseNumeric)) > 100)) ? TRUE : FALSE);
    // Temperature
    *(wData->tempOff) = ((*(wData->tempNumeric) > 37.8) || (*(wData->tempNumeric) < 36.1)) ? TRUE : FALSE;
    *
    *
    */
   }

