#include "DataStructs.h"
#include "peripheralCom.h"
#include "batteryStatusSC.h"

int globalCounter;

void batteryStatusSC(void *statusStruct) {
    // create string to be sent to the PS
    char start = 2;
    char stop = 3;
    char str[25];
    str[0] = 'B';
    str[1] = 'A'; // To be changed after implemented TFTKeypad
    str[2] = 'A'; // To be changed after implemented TFTKeypad
    str[3] = 'A'; // To be changed after implemented TFTKeypad
    strcat(str, &start);
    strcat(str, "Starting status\n");
    strcat(str, &stop);

    // transfer and receive 
    //peripheralCom(char *data, void *dataStruct);
}
