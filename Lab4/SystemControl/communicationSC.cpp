#include <Arduino.h>
#include "DataStructs.h"

// send a String to PS and receive a data packet from the PS
void communicationSC(char *str, void *dataStruct) {
    // send process
    Serial1.write(str,13);
    Serial1.flush(); // Wait print to complete

    // receive process 
    if (str[0] == 'M') { 
        char measureIn[14];
        while ((Serial1.available() < 12)) {

        }
        Serial1.readBytes(measureIn, 12);
        
        // Store values in the measureIn to measureStruct
        MeasureData* mData = (MeasureData*) dataStruct;
        // Add statements checking if a variable is being tracked currently
        float oldpulse = (float) 100*((*(mData->pulseRateRawBuf))[0] - '0') + 10*((*(mData->pulseRateRawBuf))[1] - '0') + ((*(mData->pulseRateRawBuf))[2])- '0';
        float oldtemp = (float) 10*((*(mData->temperatureRawBuf))[0] - '0') + (*(mData->temperatureRawBuf)[1]) - '0';
        float oldresp = (float) 10*((*(mData->respirationRateRawBuf))[1] - '0') + ((*(mData->respirationRateRawBuf))[2])- '0';

        float pulse = (float) 100*(measureIn[7] - '0') + 10*(measureIn[8] - '0') + (measureIn[9])- '0';
        float temp = (float) 10*(measureIn[0] - '0') + (measureIn[1] - '0');
        float resp = (float) 10*(measureIn[10] - '0') + (measureIn[11])- '0';
        if ((*(mData->tempSelection)) == TRUE && (temp > 1.15*oldtemp || temp < 0.85*oldtemp)){
            for (int i = 7; i > 0; i--){ 
                (*(mData->temperatureRawBuf))[2*i] = (*(mData->temperatureRawBuf))[2*(i-1)]; // temp
                (*(mData->temperatureRawBuf))[2*i+1] = (*(mData->temperatureRawBuf))[2*(i-1)+1]; 
            }
            (*(mData->temperatureRawBuf))[0] = measureIn[0];
            (*(mData->temperatureRawBuf))[1] = measureIn[1];
            
        }
        if ((*(mData->bpSelection)) == TRUE){
            for (int i = 7; i > 0; i--){ 
                (*(mData->bloodPressRawBuf))[3*i] = (*(mData->bloodPressRawBuf))[3*(i-1)]; // temp
                (*(mData->bloodPressRawBuf))[3*i+1] = (*(mData->bloodPressRawBuf))[3*(i-1)+1]; 
                (*(mData->bloodPressRawBuf))[3*i+2] = (*(mData->bloodPressRawBuf))[3*(i-1)+2]; 
                (*(mData->bloodPressRawBuf))[24+2*i] = (*(mData->bloodPressRawBuf))[24+2*(i-1)]; 
                (*(mData->bloodPressRawBuf))[24+2*i+1] = (*(mData->bloodPressRawBuf))[24+2*(i-1)+1]; 
            }
        (*(mData->bloodPressRawBuf))[0] = measureIn[2];
        (*(mData->bloodPressRawBuf))[1] = measureIn[3];
        (*(mData->bloodPressRawBuf))[2] = measureIn[4];
        (*(mData->bloodPressRawBuf))[24] = measureIn[5];
        (*(mData->bloodPressRawBuf))[25] = measureIn[6];
        }
        if ((*(mData->pulseSelection)) == TRUE && (pulse> 1.15*oldpulse || pulse < 0.85*oldpulse)){
            for (int i = 7; i > 0; i--){ 
                (*(mData->pulseRateRawBuf))[3*i] = (*(mData->pulseRateRawBuf))[3*(i-1)]; // temp
                (*(mData->pulseRateRawBuf))[3*i+1] = (*(mData->pulseRateRawBuf))[3*(i-1)+1]; 
                (*(mData->pulseRateRawBuf))[3*i+2] = (*(mData->pulseRateRawBuf))[3*(i-1)+2]; 
            }
        (*(mData->pulseRateRawBuf))[0] = measureIn[7];
        (*(mData->pulseRateRawBuf))[1] = measureIn[8];
        (*(mData->pulseRateRawBuf))[2] = measureIn[9];
        }
        if ((*(mData->respSelection)) == TRUE && (resp > 1.15*oldresp || resp < 0.85*oldresp)){
            for (int i = 7; i > 0; i--){ 
                (*(mData->respirationRateRawBuf))[2*i] = (*(mData->respirationRateRawBuf))[2*(i-1)]; // temp
                (*(mData->respirationRateRawBuf))[2*i+1] = (*(mData->respirationRateRawBuf))[2*(i-1)+1]; 
            }
        (*(mData->respirationRateRawBuf))[0] = measureIn[10];
        (*(mData->respirationRateRawBuf))[1] = measureIn[11];
        }
        
    } else if (str[0] =='C') {
        char computeIn[17];
        while ((Serial1.available() < 15)) {     
            }
        
        Serial1.readBytes(computeIn, 15);
        // TODO: store values in the computeIn to computeStruct
        // need to wait until top level code is set
        ComputeData* cData = (ComputeData*) dataStruct;
        
        if ((*(cData->tempSelection)) == TRUE){
            for (int i = 7; i > 0; i--){
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
            for (int i = 7; i > 0; i--){
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
            for (int i = 7; i > 0; i--){
                (*(cData->pulseRateCorrectedBuf))[3*i] = (*(cData->pulseRateCorrectedBuf))[3*(i-1)]; // pulse
                (*(cData->pulseRateCorrectedBuf))[3*i+1] = (*(cData->pulseRateCorrectedBuf))[3*(i-1)+1]; 
                (*(cData->pulseRateCorrectedBuf))[3*i+2] = (*(cData->pulseRateCorrectedBuf))[3*(i-1)+2]; 
            }
            (*(cData->pulseRateCorrectedBuf))[0] = computeIn[10]; // pulse 
            (*(cData->pulseRateCorrectedBuf))[1] = computeIn[11];
            (*(cData->pulseRateCorrectedBuf))[2] = computeIn[12];
        }
        if ((*(cData->respSelection)) == TRUE){
            for (int i = 7; i > 0; i--){ 
                (*(cData->respirationRateCorrectedBuf))[2*i] = (*(cData->respirationRateCorrectedBuf))[2*(i-1)]; // temp
                (*(cData->respirationRateCorrectedBuf))[2*i+1] = (*(cData->respirationRateCorrectedBuf))[2*(i-1)+1]; 
            }
        (*(cData->respirationRateCorrectedBuf))[0] = computeIn[13];
        (*(cData->respirationRateCorrectedBuf))[1] = computeIn[14];
        }
    } else if (str[0] == 'S') {
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

