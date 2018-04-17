#include "DataStructs.h"

void status(void *statusStruct) {
    StatusData *sData = (StatusData*) statusStruct;
    *(sData->batteryState) -= 1;
}