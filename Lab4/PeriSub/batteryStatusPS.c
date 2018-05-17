#include "DataStructsPS.h"

void batteryStatusPS(void *statusStruct) {
    // TODO: modify lab2 code
    StatusDataPS *sData = (StatusDataPS*) statusStruct;

    *(sData->batteryState) -= 1;
}