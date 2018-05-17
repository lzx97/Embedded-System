#ifdef __cplusplus
extern "C" {
#endif
#include "Bool.h"
#include "measurePS.h"
#include "DataStructsPS.h"
#include "computePS.h"
#include "batteryStatusPS.h"
#ifdef __cplusplus
}
#endif


/* Shared global variables for storing data */
// Measure Data
unsigned int temperatureRaw = 75;
unsigned int systolicPressRaw = 80;
unsigned int diastolicPressRaw = 80;
unsigned int pulseRateRaw = 50;
Bool sysMeasureComplete = FALSE;
Bool diaMeasureComplete = FALSE;
Bool tempIncrease = FALSE;
Bool bpIncrease = FALSE;
Bool tempSelection = TRUE;
Bool bpSelection = TRUE;
Bool pulseSelection = TRUE;
unsigned int numOfMeasureCalls = 0;

// ComputeData
float tempCorrected = 0;
unsigned int systolicPressCorrected = 0;
unsigned int diastolicPressCorrected = 0;
unsigned int pulseRateCorrected = 0;

// WarningAlarm
Bool bpOutOfRange = FALSE;
Bool tempOutOfRange = FALSE;
Bool pulseOutOfRange = FALSE;
Bool bpHigh = FALSE;
Bool bpLow = FALSE;
Bool bpOff = FALSE;
Bool tempOff = FALSE;
Bool pulseOff = FALSE;
Bool batteryLow = FALSE;
unsigned int bpAlarmCount;

//Battery Status
unsigned short batteryState = 200;
/* end of shared global variables */

MeasureDataPS mData;
ComputeDataPS cData;
WarningAlarmDataPS wData;
StatusDataPS sData;


void setup() {
    Serial.begin(9600);
    pinMode(PULSE_IN, INPUT);

    // MeasureData fields
    mData.temperatureRaw = &temperatureRaw;
    mData.systolicPressRaw = &systolicPressRaw;
    mData.diastolicPressRaw = &diastolicPressRaw;
    mData.pulseRateRaw = &pulseRateRaw;
    mData.sysMeasureComplete = &sysMeasureComplete;
    mData.diaMeasureComplete = &diaMeasureComplete;
    mData.tempIncrease = &tempIncrease;
    mData.bpIncrease = &bpIncrease;
    mData.tempSelection = &tempSelection;
    mData.bpSelection = &bpSelection;
    mData.pulseSelection = &pulseSelection;
    mData.numOfMeasureCalls = &numOfMeasureCalls;

    // ComputeData fields.
    cData.temperatureRaw = &temperatureRaw;
    cData.systolicPressRaw = &systolicPressRaw;
    cData.diastolicPressRaw = &diastolicPressRaw;
    cData.pulseRateRaw = &pulseRateRaw;
    cData.tempCorrected = &tempCorrected;
    cData.systolicPressCorrected = &systolicPressCorrected;
    cData.diastolicPressCorrected = &diastolicPressCorrected;
    cData.pulseRateCorrected = &pulseRateCorrected;
    cData.tempSelection = &tempSelection;
    cData.bpSelection = &bpSelection;
    cData.pulseSelection = &pulseSelection;

    // WarningAlarmData fields
    wData.temperatureRaw = &temperatureRaw;
    wData.systolicPressRaw = &systolicPressRaw;
    wData.diastolicPressRaw = &diastolicPressRaw;
    wData.pulseRateRaw = &pulseRateRaw;
    wData.batteryState = &batteryState;
    wData.batteryState = &batteryState;
    wData.bpOutOfRange = &bpOutOfRange;
    wData.tempOutOfRange = &tempOutOfRange;
    wData.pulseOutOfRange = &pulseOutOfRange;
    wData.bpHigh = &bpHigh;
    wData.tempOff = &tempOff;
    wData.pulseOff = &pulseOff;
    wData.batteryLow = &batteryLow;
    wData.bpAlarmCount = &bpAlarmCount;
    wData.tempSelection = &tempSelection;
    wData.bpSelection = &bpSelection;
    wData.pulseSelection = &pulseSelection;

    // StatusData fields
    sData.batteryState = &batteryState;
}

void loop() {
    char inBytes[13];
    if (Serial.available() > 12) {
        //Format[mbtp<Measure>]
        Serial.readBytes(inBytes, 13);
        
        // Measure case
        if (inBytes[0] == 'M') {
            // Set measure selection fields
            // Blood pressure
            if (inBytes[1] == 'B') {
                *(mData.bpSelection) = TRUE;
            }
            else if (inBytes[1] == 'b') {
                *(mData.bpSelection) = FALSE;
            }
            // Temperature
            if (inBytes[2] == 'T') {
                *(mData.tempSelection) = TRUE;
            }
            else if (inBytes[2] == 't') {
                *(mData.tempSelection) = FALSE;
            }
            // Pulse Rate
            if (inBytes[3] == 'P') {
                *(mData.pulseSelection) == TRUE;
            }
            else if (inBytes[3] == 'p') {
                *(mData.pulseSelection) == FALSE;
            }
            // end of measure selection processing
    
            // call measure function
            void* mDataPtr = (void*)&mData;
            measurePS(mDataPtr);
    
            // Send raw data back
            
            Serial.print(*(mData.temperatureRaw));
            Serial.flush();
            if (*(mData.systolicPressRaw) < 100) {
                Serial.print(0);
                Serial.flush();
            }
            Serial.print(*(mData.systolicPressRaw));
            Serial.flush();
            Serial.print(*(mData.diastolicPressRaw));
            Serial.flush();
            if (*(mData.pulseRateRaw) < 10) {
                Serial.print(0);
                Serial.flush();
                Serial.print(0);
                Serial.flush();
            }
            else if (*(mData.pulseRateRaw) < 100) {
                Serial.print(0);
                Serial.flush();
            }
            Serial.print(*(mData.pulseRateRaw));
            Serial.flush();
        }
        
        else if (inBytes[0] == 'C') {
            /*
            // Set measure selection fields
            // Blood pressure
            if (inBytes[1] == 'B') {
                *(cData.bpSelection) = TRUE;
            }
            else if (inBytes[1] == 'b') {
                *(cData.bpSelection) = FALSE;
            }
            // Temperature
            if (inBytes[2] == 'T') {
                *(cData.tempSelection) = TRUE;
            }
            else if (inBytes[2] == 't') {
                *(cData.tempSelection) = FALSE;
            }
            // Pulse Rate
            if (inBytes[3] == 'P') {
                *(cData.pulseSelection) == TRUE;
            }
            else if (inBytes[3] == 'p') {
                *(cData.pulseSelection) == FALSE;
            }
            // end of measure selection processing
            */
            
            // call compute
            void* cDataPtr = (void*)&cData;
            computePS(cDataPtr);

            // print corrected data
            Serial.print(*(cData.tempCorrected), 1); // 4 chars
            Serial.flush();
            if (*(cData.systolicPressCorrected) < 100) {
                Serial.print(0);
                Serial.flush();
            }
            Serial.print(*(cData.systolicPressCorrected)); // 3 chars
            Serial.flush();
            if (*(cData.diastolicPressCorrected) < 100) {
                Serial.print(0);
                Serial.flush();
            }
            Serial.print(*(cData.diastolicPressCorrected));
            
            if (*(cData.pulseRateCorrected) < 10) {
                Serial.print(0);
                Serial.flush();
                Serial.print(0);
                Serial.flush();
            }
            else if (*(cData.pulseRateCorrected) < 100) {
                Serial.print(0);
                Serial.flush();
            }
            Serial.print(*(cData.pulseRateCorrected));
            Serial.flush();
        }
        else if (inBytes[0] == 'S') {
        void* sDataPtr = (void*) &sData;
        batteryStatusPS(sDataPtr);

        if (*(sData.batteryState) < 10) {
            Serial.print(0);
            Serial.flush();
            Serial.print(0);
            Serial.flush();
        }
        else if (*(sData.batteryState) < 100) {
            Serial.print(0);
            Serial.flush();
        }
        Serial.print(*(sData.batteryState));
        Serial.flush();
    }
    }
    



    /*
    // Test code for each function
    void* mDataPtr = (void*)&mData;
        measurePS(mDataPtr);
        Serial.println(*(mData.temperatureRaw));
        Serial.println(*(mData.systolicPressRaw));
        Serial.println(*(mData.diastolicPressRaw));
        Serial.println(*(mData.pulseRateRaw));
        Serial.println("Finished measure");
        //Serial.println();
        void* cDataPtr = (void*)&cData;
        computePS(cDataPtr);
        Serial.println(*(cData.tempCorrected));
        Serial.println(*(cData.systolicPressCorrected));
        Serial.println(*(cData.diastolicPressCorrected));
        Serial.println(*(cData.pulseRateCorrected));
        Serial.println("Finished compute");
        void* sDataPtr = (void*)&sData;
        batteryStatusPS(sDataPtr);
        Serial.println(*(sData.batteryState));
        Serial.println();
        delay(1000);*/
}


