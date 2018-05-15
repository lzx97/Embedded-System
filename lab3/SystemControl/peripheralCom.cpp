#include <stdio.h>
#include "peripheralCom.h"
#include <Arduino.h>


int globalCounter;

// send a String to PS and receive a data packet from the PS
void communicationSC(char *str, void *dataStruct) {
    // send process
    Serial1.print(str);
    Serail1.fulsh(); // Wait print to complete


    // receive process 
    if (str[0] == 'M') { 
        char measureIn[12];
        while ((Serial.available() < 10)) {
            
        }
        Serial.readBytes(measureIn, 10);
        
        // TODO: store values in the measureIn to measureStruct
        // need to wait until top level code is set
        
    }

    else if (str[0] =='C') {
        char computeIn[15];
        while ((Serial.available() < 13)) {
            
        }
        
        Serial.readBytes(computeIn, 13);

        // TODO: store values in the computeIn to computeStruct
        // need to wait until top level code is set

    else if (str[0] == 'S') {
        char statusIn[5];
        while (Serial.available() < 3) {
            
        }
        
        Serial.readBytes(statusIn, 3);

        StatusData* sData = (StatusData*) dataStruct;
        (*(sData->batteryState))[0] = statusIn[0];
        (*(sData->batteryState))[1] = statusIn[1];
        (*(sData->batteryState))[2] = statusIn[2];
        
}

