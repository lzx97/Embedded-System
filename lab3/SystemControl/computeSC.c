#include <stdio.h>
#include "DataStructs.h"
#include "peripheralCom.h"
#include "computeSC.h"

int globalCounter;

// SC part of the compute. Send data packet to call compute. 
void computeSC(void *computeStruct) {
    // create string to be sent to the PS
    char start = 2;
    char stopp = 3;
    char str[30];
    str[0] = 'C';
    str[1] = 'B'; // To be changed after implemented TFTKeypad
    str[2] = 'T'; // To be changed after implemented TFTKeypad
    str[3] = 'P'; // To be changed after implemented TFTKeypad
    strcat(str, &start);
    strcat(str, "Starting compute");
    strcat(str, &stopp);

    // transfer and receive 
    //    peripheralCom(char *data, void *dataStruct);
}
