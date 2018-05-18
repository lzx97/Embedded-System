#include "DataStructs.h"
#include "warningSC.h"
#include "Bool.h"

// ADD METHOD TO CHECK RESP OFF


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
    int resp = 10*((*(wData->respirationRateCorrectedBuf))[1] - '0') + ((*(wData->respirationRateCorrectedBuf))[2])- '0';
    
    // Battery
    *(wData->batteryLow) = ((batterystate < 40) ?  TRUE : FALSE);
    
    // syst
    if (sys > 156 || sys < 96){           // ALARM RANGE
        if (*(wData->sysAlarmAcknowledge)){
            (*(wData->sysAlarmTimer))++;
            if (*(wData->sysAlarmTimer) > 5){
                *(wData->sysAlarm) = TRUE;
                *(wData->sysAlarmAcknowledge) = FALSE;
                *(wData->sysAlarmTimer) = 0;
            }
        } else {
            *(wData->sysAlarm) = TRUE;
            *(wData->sysAlarmTimer) = 0;
        }
    } else if (sys > 136 || sys < 114){   // WARNING RANGE
        if (*(wData->sysAlarm)){
            *(wData->sysAlarm) = FALSE;
            *(wData->sysAlarmTimer) = 0;
        }
        if (*(wData->sysAlarmAcknowledge)){
            *(wData->sysAlarmAcknowledge) = FALSE;
        }
        *(wData->sysWarning) = TRUE;
    
    } else {                              // NORMAL RANGE
        if (*(wData->sysAlarm)){
            *(wData->sysAlarm) = FALSE;
            *(wData->sysAlarmTimer) = 0;
        }
        if (*(wData->sysAlarmAcknowledge)){
            *(wData->sysAlarmAcknowledge) = FALSE;
        }
        *(wData->sysWarning) = FALSE;
    }
      
    
    // dias
    if (dias > 84 || dias < 66){      // WARNING RANGE
        *(wData->diasWarning) = TRUE;
    } else {                          // NORMAL RANGE
        *(wData->diasWarning) = FALSE;
    }
     
    // pulserate
        if (pulse > 115 || pulse < 51){           // ALARM RANGE
        if (*(wData->pulseAlarmAcknowledge)){
            (*(wData->pulseAlarmTimer))++;
            if (*(wData->pulseAlarmTimer) > 5){
                *(wData->pulseAlarm) = TRUE;
                *(wData->pulseAlarmAcknowledge) = FALSE;
                *(wData->pulseAlarmTimer) = 0;
            }
        } else {
            *(wData->pulseAlarm) = TRUE;
            *(wData->pulseAlarmTimer) = 0;
        }
    } else if (pulse > 105 || pulse < 57){   // WARNING RANGE
        if (*(wData->pulseAlarm)){
            *(wData->pulseAlarm) = FALSE;
            *(wData->pulseAlarmTimer) = 0;
        }
        if (*(wData->pulseAlarmAcknowledge)){
            *(wData->pulseAlarmAcknowledge) = FALSE;
        }
        *(wData->pulseWarning) = TRUE;
    
    } else {                              // NORMAL RANGE
        if (*(wData->pulseAlarm)){
            *(wData->pulseAlarm) = FALSE;
            *(wData->pulseAlarmTimer) = 0;
        }
        if (*(wData->pulseAlarmAcknowledge)){
            *(wData->pulseAlarmAcknowledge) = FALSE;
        }
        *(wData->pulseWarning) = FALSE;
    }
    
    // Temperature
    if (temp > 43.5 || temp < 30.7){           // ALARM RANGE
        if (*(wData->tempAlarmAcknowledge)){
            (*(wData->tempAlarmTimer))++;
            if (*(wData->tempAlarmTimer) > 5){
                *(wData->tempAlarm) = TRUE;
                *(wData->tempAlarmAcknowledge) = FALSE;
                *(wData->tempAlarmTimer) = 0;
            }
        } else {
            *(wData->tempAlarm) = TRUE;
            *(wData->tempAlarmTimer) = 0;
        }
    } else if (temp > 39.7 || temp < 34.3){   // WARNING RANGE
        if (*(wData->tempAlarm)){
            *(wData->tempAlarm) = FALSE;
            *(wData->tempAlarmTimer) = 0;
        }
        if (*(wData->tempAlarmAcknowledge)){
            *(wData->tempAlarmAcknowledge) = FALSE;
        }
        *(wData->tempWarning) = TRUE;
    
    } else {                              // NORMAL RANGE
        if (*(wData->tempAlarm)){
            *(wData->tempAlarm) = FALSE;
            *(wData->tempAlarmTimer) = 0;
        }
        if (*(wData->tempAlarmAcknowledge)){
            *(wData->tempAlarmAcknowledge) = FALSE;
        }
        *(wData->tempWarning) = FALSE;
    }

    // Respiratory rate
        if (resp > 23 || resp < 11){           // ALARM RANGE
        if (*(wData->respAlarmAcknowledge)){
            (*(wData->respAlarmTimer))++;
            if (*(wData->respAlarmTimer) > 5){
                *(wData->respAlarm) = TRUE;
                *(wData->respAlarmAcknowledge) = FALSE;
                *(wData->respAlarmTimer) = 0;
            }
        } else {
            *(wData->respAlarm) = TRUE;
            *(wData->respAlarmTimer) = 0;
        }
        } else {                              // NORMAL RANGE
        if (*(wData->respAlarm)){
            *(wData->respAlarm) = FALSE;
            *(wData->respAlarmTimer) = 0;
        }
        if (*(wData->respAlarmAcknowledge)){
            *(wData->respAlarmAcknowledge) = FALSE;
        }
    }
    
    
   }

