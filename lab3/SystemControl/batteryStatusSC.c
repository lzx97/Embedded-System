#include "DataStructs.h"
#include "batteryStatusSC.h"

int globalCounter;

void batteryStatusSC(void *statusStruct) {
    // create string to be sent to the PS
    StatusData *stData = (StatusData*) statusStruct;
    if ((globalCounter % *(stData->statusInterval)) != 0){
    return;
    }
    char start = 2;
    char stopp = 3;
    char str[12];
    str[0] = 'B';
    str[1] = ' ';
    str[2] = ' ';
    str[3] = ' ';
    strcat(str, &start);
    strcat(str, "Starting batterystatus\n");
    strcat(str, &stopp);

    // transfer and receive 
    communicationSC(str, statusStruct);

}
