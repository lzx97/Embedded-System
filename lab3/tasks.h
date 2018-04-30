#include "DataStructs.h"

void startUp();
void scheduler(TCB **taskQueue);
void measureData(void *measureStruct);
void computeData(void *computeStruct);
void TFTKeypad(void *keypadStruct);
void displayData(void *displayStruct);
void warningAlarm(void *warningAlarmStruct);
void peripheralCom();
void batteryStatus(void *statusStruct);