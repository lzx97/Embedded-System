#include <stdio.h>
#include "peripheralCom.h"
#include <Arduino.h>


int globalCounter;

// send a String to PS and receive a data packet from the PS
void communicationSC(char *data, void *dataStruct) {
    // send process
    Serial.write(data); // send

    // always call warningAlarm 
    if (data[0] == 'M') {
    } else if (data[0] == 'C'){
      
    } else if (data[0] == 'B'){
      
    }


    // receive process
    // TODO: implement
    
}

