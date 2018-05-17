#include "DataStructs.h"
#include "warningSC.h"
#include "Bool.h"


void annunciate(void *warningAlarmStruct) {
    WarningAlarmData *wData = (WarningAlarmData*) warningAlarmStruct;
    if ((*(wData->globalTime) % *(wData->warningInterval)) != 0){
    return;
    }
    int batterystate = 100*((*(wData->batteryState))[0] - '0')+ 10*((*(wData->batteryState))[1] - '0') + ((*(wData->batteryState))[2]) - '0'; 
    int sys = 100*((*(wData->bloodPressCorrectedBuf))[0] - '0')+ 10*((*(wData->bloodPressCorrectedBuf))[1] - '0') + ((*(wData->bloodPressCorrectedBuf))[2]) - '0';
    int dias = 100*((*(wData->bloodPressCorrectedBuf))[24] - '0')+ 10*((*(wData->bloodPressCorrectedBuf))[25] - '0') + ((*(wData->bloodPressCorrectedBuf))[26]) - '0';
    int pulse = 100*((*(wData->pulseRateCorrectedBuf))[0] - '0') + 10*((*(wData->pulseRateCorrectedBuf))[1] - '0') + ((*(wData->pulseRateCorrectedBuf))[2])- '0';
    float temp = 100*((*(wData->tempCorrectedBuf))[0] - '0') + 10*((*(wData->tempCorrectedBuf))[1] - '0') + (*(wData->tempCorrectedBuf)[2]) - '0' +  ((*(wData->tempCorrectedBuf)[3])- '0')/10;
    // Battery
    *(wData->batteryLow) = ((batterystate < 40) ?  TRUE : FALSE);
    // syst
    *(wData->bpHigh) = ((sys > 120) ? TRUE : FALSE);
    if (*(wData->alarmAcknowledge)){
        (*(wData->alarmTimer))++;
        if (*(wData->alarmTimer) > 5){
          (*(wData->sysAlarm)) = TRUE;
          (*(wData->alarmAcknowledge)) = FALSE;
        }
    }
    // sys
    *(wData->sysAlarm) = ((sys > 140) ? TRUE : FALSE);
    
    // dias
    *(wData->bpLow) = ((dias < 80) ? TRUE : FALSE);
    
    // pulserate
    *(wData->pulseOff) = ((pulse < 60) || ((pulse > 100)) ? TRUE : FALSE);
    
    // Temperature
    *(wData->tempOff) = ((temp > 37.8) || ((temp < 36.1)) ? TRUE : FALSE);
    
    
    
   }

