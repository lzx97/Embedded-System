#include "DataStructs.h"

void measureSC(void *measureStruct) {
    // create string to be sent to the PS
    char start = 2;
    char stop = 3;
    char str[25];
    str[0] = 'M';
    str[1] = 'B'; // To be changed after implemented TFTKeypad
    str[2] = 'T'; // To be changed after implemented TFTKeypad
    str[3] = 'P'; // To be changed after implemented TFTKeypad
    strcat(str, &start);
    strcat(str, "Starting measure\n");
    strcat(str, &stop);

    // transfer and receive 
    com(char *data, void *dataStruct);
}
