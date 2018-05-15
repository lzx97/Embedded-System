#include <stdio.h>
#include "DataStructs.h"
#include "computeSC.h"

int globalCounter;

// SC part of the compute. Send data packet to call compute. 
void computeSC(void *computeStruct) {
    ComputeData *cData = (ComputeData*) computeStruct;

    char start = 2;
    char stopp = 3;
    char str[12];
    str[0] = 'C';
    str[1] = (*(cData->bpSelection) ? 'B' : 'b');
    str[2] = (*(cData->tempSelection) ? 'T' : 't');
    str[3] = (*(cData->pulseSelection) ? 'P' : 'p');
    strcat(str, &start);
    strcat(str, "Starting compute\n");
    strcat(str, &stopp);

    // transfer and receive 
    communicationSC(str, computeStruct);

}
