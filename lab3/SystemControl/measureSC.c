#include "DataStructs.h"
#include "peripheralCom.h"
#include "measureSC.h";

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
    str[1] = 'B'; // To be changed after implemented TFTKeypad
    str[2] = 'T'; // To be changed after implemented TFTKeypad
    str[3] = 'P'; // To be changed after implemented TFTKeypad
    strcat(str, &start);
    strcat(str, "Starting measure\n");
    strcat(str, &stopp);

    // transfer and receive 
    communicationSC(str, &measureStruct);

    // ADD COMPUTE STRUCT IF NOT ALREADY THERE
}
