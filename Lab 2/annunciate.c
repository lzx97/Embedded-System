#include <math.h>
#include "DataStructs.h"

void annuciate(void *warningAlarmStruct) {
        WarningAlarmData *wData = (WarningAlarmData*) warningAlarmStruct;
        // Battery
        *(wData->batteryLow) = ((*(wData->batteryState)) < 40) ?  TRUE : FALSE);
        // syst
        *(wData->bpHigh) = ((*(wData->systolicPressRaw)) < dasda ? TRUE : FALSE)
        // dias
        // pulserate

}
