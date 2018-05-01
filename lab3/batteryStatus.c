#include "DataStructs.h"

int globalCounter;

void batteryStatusPS(void *statusStruct) {
    // TODO: modify lab2 code
    StatusData *sData = (StatusData*) statusStruct;
    if (globalCounter % 5 != 0){
        return;
    }
    *(sData->batteryState) -= 1;
}

void batteryStateSC(void *statusStruct) {
    // create char[]

    // call com
}