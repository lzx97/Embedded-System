#include "DataStructs.h"
#include "measureSC.h";
#ifdef __cplusplus
extern "C" {
#endif
#include "peripheralCom.h"
#ifdef __cplusplus
}
#endif



// TCB MeasureTCB;
// TCB ComputeTCB;

void measurerSC(void *measureStruct) {
    MeasureData *mData = (MeasureData*) measureStruct;
    if ((*(mData->globalTime) % (*(mData->measureInterval))) != 0){
       // if(*(mData->MeasureTCB.next) == *(mData->&ComputeTCB)){
          //
        //}
        return;
    }
    // create string to be sent to the PS
    char start = 2;
    char stopp = 3;
    char str[25];
    str[0] = 'M';
    str[1] = (*(mData->bpSelection) ? 'B' : 'b');
    str[2] = (*(mData->tempSelection) ? 'T' : 't');
    str[3] = (*(mData->pulseSelection) ? 'P' : 'p');
    strcat(str, &start);
    strcat(str, "Starting measure\n");
    strcat(str, &stopp);

    // transfer and receive 
    // communicationSC(str, measureStruct);

    // ADD COMPUTE STRUCT IF NOT ALREADY THERE
}
