#include "DataStructs.h"
#include "communicationSC.h"
#include <Arduino.h>


// SC part of the compute. Send data packet to call compute. 
void computeSC(void *computeStruct) {
    ComputeData *cData = (ComputeData*) computeStruct;
    Serial.println("inside compute"); delay(50);

    char str[13];
    str[0] = 'C';
    str[1] = ((*(cData->bpSelection)) ? 'B' : 'b');
    str[2] = ((*(cData->tempSelection)) ? 'T' : 't');
    str[3] = ((*(cData->pulseSelection)) ? 'P' : 'p');
    str[4] = ((*(cData->respSelection)) ? 'R' : 'r');
    str[5] = 'C';
    str[6] = 'o';
    str[7] = 'm';
    str[8] = 'p';
    str[9] = 'u';
    str[10] = 't';
    str[11] = 'e';
    str[12] = '>';
    
    Serial.println(str); delay(50);

    // transfer and receive 
    communicationSC(str, computeStruct);

}
