#include "DataStructs.h"
#include "communicationSC.h"

int globalCounter;

void batteryStatusSC(void *statusStruct) {
    // create string to be sent to the PS
    StatusData *sData = (StatusData*) statusStruct;
    if ((globalCounter % *(sData->statusInterval)) != 0){
        return;
    }
    char str[13];
    str[0] = 'S';
    str[1] = 'A';
    str[2] = 'A';
    str[3] = 'A';
    str[4] = '<';
    str[5] = 'B';
    str[6] = 'a';
    str[7] = 't';
    str[8] = 'S';
    str[9] = 't';
    str[10] = 'a';
    str[11] = 't';
    str[12] = '>';

    // transfer and receive 
    communicationSC(str, statusStruct);

}
