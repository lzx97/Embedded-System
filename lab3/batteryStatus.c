#include "DataStructs.h"

int globalCounter;

void batteryStatusPS(void *statusStruct) {
    // TODO: modify lab2 code
    StatusData *sData = (StatusData*) statusStruct;
    if (globalCounter % 5 != 0){
        return;
    }
    *(sData->batteryState) -= 1;
}

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
    com(char *data, void *dataStruct);
}