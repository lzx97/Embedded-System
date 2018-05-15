#include "DataStructs.h"
#include "measureSC.h";
#include "communicationSC.h"

int globalCounter;

// TCB MeasureTCB;
// TCB ComputeTCB;

void measurerSC(void *measureStruct) {
    MeasureData *mData = (MeasureData*) measureStruct;
    //if ((*(mData->globalTime) % (*(mData->measureInterval))) != 0){
        //return;
    //}

    // create the command string to be sent to the PS
    char str[13];
    str[0] = 'M';
    str[1] = (*(mData->bpSelection) ? 'B' : 'b');
    str[2] = (*(mData->tempSelection) ? 'T' : 't');
    str[3] = (*(mData->pulseSelection) ? 'P' : 'p');
    str[4] = '<';
    str[5] = 'M';
    str[6] = 'e';
    str[7] = 'a';
    str[8] = 's';
    str[9] = 'u';
    str[10] = 'r';
    str[11] = 'e';
    str[12] = '>';

    
    communicationSC(str, measureStruct);
}
