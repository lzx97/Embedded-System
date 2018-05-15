#include "DataStructs.h"
#include "communicationSC.h"

int globalCounter;

// SC part of the compute. Send data packet to call compute. 
void computeSC(void *computeStruct) {
    ComputeData *cData = (ComputeData*) computeStruct;

    // global counter checker
    //if () {
        //return;
    //}

    char str[13];
    str[0] = 'C';
    str[1] = 'A';
    str[2] = 'A';
    str[3] = 'A';
    str[4] = '<';
    str[5] = 'C';
    str[6] = 'o';
    str[7] = 'm';
    str[8] = 'p';
    str[9] = 'u';
    str[10] = 't';
    str[11] = 'e';
    str[12] = '>';

    // transfer and receive 
    communicationSC(str, computeStruct);

}
