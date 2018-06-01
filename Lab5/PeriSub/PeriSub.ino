#ifdef __cplusplus
extern "C" {
#endif
#include "Bool.h"
//#include "measurePS.h"
#include "DataStructsPS.h"
#include "computePS.h"
#include "batteryStatusPS.h"
#ifdef __cplusplus
}
#endif
#include "measurePS.h"


/* Shared global variables for storing data */
// Measure Data  
unsigned int temperatureRaw = 75;
unsigned int systolicPressRaw = 80;
unsigned int diastolicPressRaw = 80;
unsigned int pulseRateRaw = 0;
unsigned int respirationRaw = 0;
Bool sysMeasureComplete = FALSE;
Bool diaMeasureComplete = FALSE;
Bool bpIncrease = FALSE;

Bool tempSelection = TRUE;
Bool bpSelection = FALSE;
Bool pulseSelection = TRUE;
Bool respSelection = TRUE;
unsigned int numOfMeasureCalls = 0;
unsigned int bloodPressure = 80;
int patient = -1;

// ComputeData
float tempCorrected = 0;
unsigned int systolicPressCorrected = 0;
unsigned int diastolicPressCorrected = 0;
unsigned int pulseRateCorrected = 0;
unsigned int respirationCorrected = 0;

//Battery Status
unsigned short batteryState = 200;
/* end of shared global variables */

MeasureDataPS mData;
ComputeDataPS cData;
StatusDataPS sData;

unsigned long lastDebounceTime = 0;
const unsigned int debounceDelay = 300;

int ledState = LOW;
unsigned long lastBlinkTime = 0;
const unsigned int blinkInterval = 300;





void setup() {
    Serial.begin(9600);
    pinMode(PULSE_IN, INPUT);
    pinMode(BP_INC, INPUT);
    pinMode(BP_DEC, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    // MeasureData fields
    mData.temperatureRaw = &temperatureRaw;
    mData.systolicPressRaw = &systolicPressRaw;
    mData.diastolicPressRaw = &diastolicPressRaw;
    mData.pulseRateRaw = &pulseRateRaw;
    mData.respirationRaw = &respirationRaw;
    mData.sysMeasureComplete = &sysMeasureComplete;
    mData.diaMeasureComplete = &diaMeasureComplete;
    mData.bpIncrease = &bpIncrease;
    mData.tempSelection = &tempSelection;
    mData.bpSelection = &bpSelection;
    mData.pulseSelection = &pulseSelection;
    mData.respSelection = &respSelection;
    mData.numOfMeasureCalls = &numOfMeasureCalls;
    mData.bloodPressure = &bloodPressure;
    mData.patient = &patient;


    // ComputeData fields.
    cData.temperatureRaw = &temperatureRaw;
    cData.systolicPressRaw = &systolicPressRaw;
    cData.diastolicPressRaw = &diastolicPressRaw;
    cData.pulseRateRaw = &pulseRateRaw; 
    cData.respirationRaw = &respirationRaw;
    cData.tempCorrected = &tempCorrected;
    cData.systolicPressCorrected = &systolicPressCorrected;
    cData.diastolicPressCorrected = &diastolicPressCorrected;
    cData.pulseRateCorrected = &pulseRateCorrected;
    cData.respirationCorrected = &respirationCorrected;
    cData.tempSelection = &tempSelection;
    cData.bpSelection = &bpSelection;
    cData.pulseSelection = &pulseSelection;
    cData.respSelection = &respSelection;

    // StatusData fields
    sData.batteryState = &batteryState;

    attachInterrupt(digitalPinToInterrupt(BP_INC), bpUp, RISING);
    attachInterrupt(digitalPinToInterrupt(BP_DEC), bpDown, RISING);
    
}

void loop() {

    measureBloodPres(&systolicPressRaw,  &diastolicPressRaw, &sysMeasureComplete, &diaMeasureComplete, &bloodPressure, &patient);

    Serial.print("sysPres = ");
    Serial.print(systolicPressRaw);
    Serial.print(" diaPres = ");
    Serial.print(diastolicPressRaw);
    Serial.print(" bp = ");
    Serial.print(bloodPressure);
    Serial.print(" patient = ");
    Serial.println(patient);
    delay(5000);

    /*
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
                *(mData.pulseSelection) = TRUE;
            }
            else if (inBytes[3] == 'p') {
                *(mData.pulseSelection) = FALSE;
            }
            // Respiration 
            if (inBytes[4] == 'R') {
                *(mData.respSelection) = TRUE;
            }
            else if (inBytes[4] == 'r') {
                *(mData.respSelection) = FALSE;
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
            if (*(mData.respirationRaw) < 10) {
                Serial.print(0);
                Serial.flush();
            }
            Serial.print(*(mData.respirationRaw));
            Serial.flush();
        }
        
        else if (inBytes[0] == 'C') {
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
            Serial.print(*(cData.respirationCorrected));
            Serial.flush();
        }
        // Battery status case
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
    
    */
    
    /*
    // Test code for each function
    void* mDataPtr = (void*)&mData;
    measurePS(mDataPtr);
    Serial.println(*(mData.temperatureRaw));
    Serial.println(*(mData.systolicPressRaw));
    Serial.println(*(mData.diastolicPressRaw));
    Serial.println(*(mData.pulseRateRaw));
    Serial.println(*(mData.respirationRaw));
    Serial.println("Finished measure");
    //Serial.println();
    void* cDataPtr = (void*)&cData;
    computePS(cDataPtr);
    Serial.println(*(cData.tempCorrected));
    Serial.println(*(cData.systolicPressCorrected));
    Serial.println(*(cData.diastolicPressCorrected));
    Serial.println(*(cData.pulseRateCorrected));
    Serial.println(*(cData.respirationCorrected));
    Serial.println("Finished compute");
    void* sDataPtr = (void*)&sData;
    batteryStatusPS(sDataPtr);
    Serial.println(*(sData.batteryState));
    Serial.println();
    delay(5000);*/

    
    
}

void bpUp() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastDebounceTime > debounceDelay) {
        bloodPressure *= 1.1;
        lastDebounceTime = currentMillis;
    }
}

void bpDown() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastDebounceTime > debounceDelay) {
        bloodPressure *= 0.9;
        lastDebounceTime = currentMillis;
    }
}

