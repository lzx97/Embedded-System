#include "Bool.h"
#include "DataStructsPS.h"
#include "measurePS.h"

TCB* taskQueue[5];
TCB measureTCB;

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
Bool tempSelection = FALSE;
Bool bpSelection = FALSE;
Bool pulseSelection = FALSE;
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
  wData.batteryLow= &batteryLow;
  wData.bpAlarmCount = &bpAlarmCount;
  wData.tempSelection = &tempSelection;
  wData.bpSelection = &bpSelection;
  wData.pulseSelection = &pulseSelection;

  // StatusData fields
  sData.batteryState = &batteryState;

  measureTCB.taskPtr = &measurePS;
  measureTCB.taskDataPtr = (void*)&mData;

  taskQueue[0] = &measureTCB;
}

void loop() {
  // put your main code here, to run repeatedly:
  //void* mDataptr = (void*) &mData;
   (*(taskQueue[0]->taskPtr))(taskQueue[0]->taskDataPtr);
  /*Serial.println(*(mData.temperatureRaw));
  Serial.println(*(mData.systolicPressRaw));
  Serial.println(*(mData.diastolicPressRaw));
  Serial.println(*(mData.pulseRateRaw));*/
  Serial.println();
  delay(1000);
}
