#include <Arduino.h>
#include "DataStructs.h"

// send a String to PS and receive a data packet from the PS
void communicationSC(char *str, void *dataStruct) {
    // send process
    Serial1.print(str);
    Serial1.flush(); // Wait print to complete


    // receive process 
    if (str[0] == 'M') { 
        char measureIn[12];
        while ((Serial1.available() < 10)) {
            
        }
        Serial1.readBytes(measureIn, 10);
        
        // TODO: store values in the measureIn to measureStruct
        // need to wait until top level code is set
        MeasureData* mData = (MeasureData*) dataStruct;
        //(*(mData->temperatureRawBuf))[0] = measure[0];
        //(*(mData->bloodPressRawBuf))
        
    }

    else if (str[0] =='C') {
        char computeIn[15];
        while ((Serial1.available() < 13)) {
            
        }
        
        Serial1.readBytes(computeIn, 13);

        // TODO: store values in the computeIn to computeStruct
        // need to wait until top level code is set
        ComputeData* cData = (ComputeData*) dataStruct;
        (*(cData->tempCorrectedBuf))[0] = computeIn[0]; // temp
        (*(cData->tempCorrectedBuf))[1] = computeIn[1];
        (*(cData->tempCorrectedBuf))[2] = computeIn[2];
        (*(cData->tempCorrectedBuf))[3] = computeIn[3];
        (*(cData->bloodPressCorrectedBuf))[0] = computeIn[4]; // sys
        (*(cData->bloodPressCorrectedBuf))[1] = computeIn[5];
        (*(cData->bloodPressCorrectedBuf))[2] = computeIn[6];
        (*(cData->bloodPressCorrectedBuf))[24] = computeIn[7]; //dias
        (*(cData->bloodPressCorrectedBuf))[25] = computeIn[8];
        (*(cData->bloodPressCorrectedBuf))[26] = computeIn[9];
        (*(cData->pulseRateCorrectedBuf))[0] = computeIn[10]; // pulse 
        (*(cData->pulseRateCorrectedBuf))[1] = computeIn[11];
        (*(cData->pulseRateCorrectedBuf))[2] = computeIn[12];
    }
        
        /*
        if ((*(cData->tempSelection)) == TRUE){
            for (int i = 7; i > 0; i++){
                (*(cData->tempCorrectedBuf))[4*i] = (*(cData->tempCorrectedBuf))[4*(i-1)]; // temp
                (*(cData->tempCorrectedBuf))[4*i+1] = (*(cData->tempCorrectedBuf))[4*(i-1)+1]; 
                (*(cData->tempCorrectedBuf))[4*i+2] = (*(cData->tempCorrectedBuf))[4*(i-1)+2]; 
                (*(cData->tempCorrectedBuf))[4*i+3] = (*(cData->tempCorrectedBuf))[4*(i-1)+3]; 
            }
            (*(cData->tempCorrectedBuf))[0] = computeIn[0]; // temp
            (*(cData->tempCorrectedBuf))[1] = computeIn[1]; 
            (*(cData->tempCorrectedBuf))[2] = computeIn[2]; 
            (*(cData->tempCorrectedBuf))[3] = computeIn[3]; 
        }
        
        if ((*(cData->bpSelection)) == TRUE){
            for (int i = 7; i > 0; i++){
                (*(cData->bloodPressCorrectedBuf))[3*i] = (*(cData->bloodPressCorrectedBuf))[3*(i-1)]; // Sys
                (*(cData->bloodPressCorrectedBuf))[3*i+1] = (*(cData->bloodPressCorrectedBuf))[3*(i-1)+1]; 
                (*(cData->bloodPressCorrectedBuf))[3*i+2] = (*(cData->bloodPressCorrectedBuf))[3*(i-1)+2]; 
                (*(cData->bloodPressCorrectedBuf))[24+3*i] = (*(cData->bloodPressCorrectedBuf))[24+3*(i-1)]; // Dias
                (*(cData->bloodPressCorrectedBuf))[24+3*i+1] = (*(cData->bloodPressCorrectedBuf))[24+3*(i-1)+1]; 
                (*(cData->bloodPressCorrectedBuf))[24+3*i+2] = (*(cData->bloodPressCorrectedBuf))[24+3*(i-1)+2]; 
            }
          (*(cData->bloodPressCorrectedBuf))[0] = computeIn[4]; // sys
          (*(cData->bloodPressCorrectedBuf))[1] = computeIn[5];
          (*(cData->bloodPressCorrectedBuf))[2] = computeIn[6];
          (*(cData->bloodPressCorrectedBuf))[24] = computeIn[7]; //dias
          (*(cData->bloodPressCorrectedBuf))[25] = computeIn[8];
          (*(cData->bloodPressCorrectedBuf))[26] = computeIn[9];
          }
        if ((*(cData->pulseSelection)) == TRUE){
            for (int i = 7; i > 0; i++){
                (*(cData->pulseRateCorrectedBuf))[3*i] = (*(cData->pulseRateCorrectedBuf))[3*(i-1)]; // pulse
                (*(cData->pulseRateCorrectedBuf))[3*i+1] = (*(cData->pulseRateCorrectedBuf))[3*(i-1)+1]; 
                (*(cData->pulseRateCorrectedBuf))[3*i+2] = (*(cData->pulseRateCorrectedBuf))[3*(i-1)+2]; 
            }
            (*(cData->pulseRateCorrectedBuf))[0] = computeIn[10]; // pulse 
            (*(cData->pulseRateCorrectedBuf))[1] = computeIn[11];
            (*(cData->pulseRateCorrectedBuf))[2] = computeIn[12];
        }
        
    }*/ 
    else if (str[0] == 'S') {
        char statusIn[5];
        while (Serial1.available() < 3) {
            
        }
        
        Serial1.readBytes(statusIn, 3);

        StatusData* sData = (StatusData*) dataStruct;
        (*(sData->batteryState))[0] = statusIn[0];
        (*(sData->batteryState))[1] = statusIn[1];
        (*(sData->batteryState))[2] = statusIn[2];
    }
}

