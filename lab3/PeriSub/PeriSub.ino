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
    pinMode(PIN_IN, INPUT);

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
    Serial.write("hello");
    

    /*for (int i = 0; i < 10; i++) {
        Serial.print('<');
        Serial.print(i * 3);
        Serial.print('>');
        Serial.println();
    }*/
    delay(2000);


    // Test code for each function
    /*  void* mDataPtr = (void*)&mData;
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
