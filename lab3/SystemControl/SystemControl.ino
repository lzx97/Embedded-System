#ifdef __cplusplus
extern "C" {
#endif
#include "Bool.h"
#include "DataStructs.h"
#include "warningSC.h"
//#include "schedulerSC.h"
#include "computeSC.h"
#ifdef __cplusplus
}
#endif
#include "TFTKeypad.h"
#include "batteryStatusSC.h"
#include "measureSC.h"

TCB* head;
TCB* tail;

TCB MeasureTCB;
TCB ComputeTCB;
TCB tftTCB;
TCB WarningAlarmTCB;
TCB StatusTCB;

unsigned int globalTime = 0; // Change this to millis
Bool sysMeasureComplete = FALSE;
Bool diaMeasureComplete = FALSE;
Bool tempIncrease = TRUE;
Bool bpIncrease = TRUE;
unsigned int numOfMeasureCalls = 0;

unsigned int measureInterval = 5;
unsigned int computeInterval = 5;
unsigned int displayInterval = 5;
unsigned int warningInterval = 1;
unsigned int statusInterval = 5;

unsigned int temperatureRaw = 75;
unsigned int systolicPressRaw = 80;
unsigned int diastolicPressRaw = 80;
unsigned int pulseRateRaw = 50;

float tempNumeric = 0;
unsigned int sysNumeric = 0;
unsigned int diasNumeric = 0;
unsigned int pulseNumeric = 0;

unsigned int bloodPressCorrectedBuf[16] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
float tempCorrectedBuf[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
unsigned int pulseRateCorrectedBuf[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

unsigned int bloodPressRawBuf[16] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};;
unsigned int temperatureRawBuf[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
unsigned int pulseRateRawBuf[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};


unsigned short batteryState = 200;
/*
unsigned char bpOutOfRange = 0;
unsigned char tempOutOfRange = 0;
unsigned char pulseOutOfRange = 0;
*/
Bool bpHigh = FALSE;
Bool bpLow = FALSE;
Bool tempOff = FALSE;
Bool pulseOff = FALSE;
Bool batteryLow = FALSE;
Bool sysAlarm = FALSE;

Bool tempSelection = TRUE;
Bool bpSelection = TRUE;
Bool pulseSelection = TRUE;
Bool alarmAcknowledge = TRUE; // type TBD
unsigned int alarmTimer = 0;
unsigned long timeNow = 0;
Bool justPressed = FALSE;

MeasureData mData;
ComputeData cData;
TFTData dData;
WarningAlarmData wData;
StatusData stData;

void setup(void) {
    // Add variables to measure struct
    mData.globalTime = &globalTime;
    mData.measureInterval = &measureInterval;
    
    // Raw data
    mData.bloodPressRawBuf = bloodPressRawBuf;
    mData.pulseRateRawBuf = pulseRateRawBuf;
    mData.temperatureRawBuf = temperatureRawBuf;
    
    mData.sysMeasureComplete = &sysMeasureComplete;
    mData.diaMeasureComplete = &diaMeasureComplete;
    mData.tempIncrease = &tempIncrease;
    mData.bpIncrease = &bpIncrease;
    mData.numOfMeasureCalls = &numOfMeasureCalls;
//    mData.MeasureTCB = &MeasureTCB;
//    mData.ComputeTCB = &ComputeTCB;


    // Add variables to compute struct
    cData.globalTime = &globalTime;
    cData.bloodPressRawBuf = bloodPressRawBuf;
    cData.pulseRateRawBuf = pulseRateRawBuf;
    cData.temperatureRawBuf = temperatureRawBuf;

/*
    cData.tempNumeric = &tempNumeric;
    cData.sysNumeric = &sysNumeric;
    cData.diasNumeric = &diasNumeric;
    cData.pulseNumeric = &pulseNumeric;
*/
    // Add variables to display struct
    dData.globalTime = &globalTime;
    dData.displayInterval = &displayInterval;
    dData.bloodPressCorrectedBuf = bloodPressCorrectedBuf;
    dData.pulseRateCorrectedBuf = pulseRateCorrectedBuf;
    dData.tempCorrectedBuf = tempCorrectedBuf;
    dData.bloodPressRawBuf = bloodPressRawBuf;
    dData.pulseRateRawBuf = pulseRateRawBuf;
    dData.bpHigh = &bpHigh;
    dData.bpLow = &bpLow;
    dData.tempOff = &tempOff;
    dData.pulseOff = &pulseOff;
    /*
    dData.bpOutOfRange = &bpOutOfRange;
    dData.pulseOutOfRange = &pulseOutOfRange;
    dData.tempOutOfRange = &tempOutOfRange;
    */
    dData.batteryLow = &batteryLow;
    dData.tempNumeric = &tempNumeric;
    dData.sysNumeric = &sysNumeric;
    dData.diasNumeric = &diasNumeric;
    dData.pulseNumeric = &pulseNumeric;
    dData.batteryState = &batteryState;
    dData.displayInterval = &displayInterval;
    dData.tempSelection = &tempSelection;
    dData.bpSelection = &bpSelection;
    dData.pulseSelection = &pulseSelection;
    dData.alarmAcknowledge = &alarmAcknowledge;
    dData.alarmTimer = &alarmTimer;
    dData.sysAlarm = &sysAlarm;
    dData.timeNow = &timeNow;
    dData.justPressed = &justPressed;


    // Add values to warning/alarm struct
    wData.globalTime = &globalTime;
    wData.warningInterval = &warningInterval;
    /*
    wData.bpOutOfRange = &bpOutOfRange;
    wData.pulseOutOfRange = &pulseOutOfRange;
    wData.tempOutOfRange = &tempOutOfRange;
    */
    wData.batteryState = &batteryState;
    wData.bpHigh = &bpHigh;
    wData.bpLow = &bpLow;
    wData.tempOff = &tempOff;
    wData.pulseOff = &pulseOff;
    wData.batteryLow = &batteryLow;
    wData.tempNumeric = &tempNumeric;
    wData.sysNumeric = &sysNumeric;
    wData.diasNumeric = &diasNumeric;
    wData.pulseNumeric = &pulseNumeric;
    wData.sysAlarm = &sysAlarm;
    wData.alarmAcknowledge = &alarmAcknowledge;
    wData.alarmTimer = &alarmTimer;

    // Add data to status struct
    stData.globalTime = &globalTime;
    stData.statusInterval = &statusInterval;
    stData.batteryState = &batteryState;

    // Initialize the TCBs
    MeasureTCB.taskPtr = &measurerSC;
    MeasureTCB.taskDataPtr = (void*)&mData;
    MeasureTCB.prev = NULL;
    MeasureTCB.next = &StatusTCB;

    ComputeTCB.taskPtr = &computeSC;
    ComputeTCB.taskDataPtr = (void*)&cData;
    ComputeTCB.prev = NULL;  // Compute is by default not part of the queue
    ComputeTCB.next = NULL;

    StatusTCB.taskPtr = &batteryStatusSC;
    StatusTCB.taskDataPtr = (void*)&stData;
    StatusTCB.prev = &MeasureTCB;
    StatusTCB.next = &WarningAlarmTCB;

    WarningAlarmTCB.taskPtr = &annunciate;
    WarningAlarmTCB.taskDataPtr = (void*)&wData;
    WarningAlarmTCB.prev = &StatusTCB;
    WarningAlarmTCB.next = &tftTCB;

    tftTCB.taskPtr = &displayLoop;
    tftTCB.taskDataPtr = (void*)&dData;
    tftTCB.prev = &WarningAlarmTCB;
    tftTCB.next = NULL;


    // Initialize the taskQueue
    head = &MeasureTCB;
    tail = &tftTCB;

    Serial.println("0. are we here?");
}

void loop(void) {
    Serial.println("Start of loop: are we here?");
    timeNow = millis();
    TCB* curr = head;
    TCB* oldcurr;
    while (curr != tail){
        if (curr == &MeasureTCB){
            insertNode(&ComputeTCB, &MeasureTCB, head, tail);
        }
        (*(curr->taskPtr))(curr->taskDataPtr);
        oldcurr = curr;
        curr = curr->next;
        if (oldcurr == &ComputeTCB){
          deleteNode(&ComputeTCB,head,tail);
        }
    }       
    // While loop ends before tail is executed
    // So we call it one last time to run through everything
    (*(curr->taskPtr))(curr->taskDataPtr);
    // Delay one second
    globalTime++;
}

void communicationSC1(char *data, void *dataStruct) {
    // send process
    
        char dataType = data[0];
        Serial.write(data); // send
        
        if (dataType == 'M'){
        } else if (dataType == 'C'){
        while (Serial.available() == 0){
        }
        
        ComputeData *cData = (ComputeData*) dataStruct;

        if (data[1] == 'B'){
            (*(cData->sysNumeric)) = Serial.parseInt();
            (*(cData->diasNumeric)) = Serial.parseInt();

        }
        if (data[2] == 'T'){
            (*(cData->tempNumeric)) = Serial.parseFloat();
        }
        if (data[3] == 'P'){
            (*(cData->pulseNumeric)) = Serial.parseInt();
        }
  
        } else if (dataType == 'B'){
          while (Serial.available() == 0){
        }
          StatusData *stData = (StatusData*) dataStruct;
          (*(stData->batteryState)) = Serial.parseInt();
          
        }
}

void deleteNode(struct TCB* node, struct TCB* head, struct TCB* tail) {
    TCB* curr;
    TCB* prevNode;
    TCB* nextNode;
    if (node == head){
        // Node is head
        // 1. Set head->next to head
        curr = head;
        head = head->next;
        // 2. Set internal pointers to NULL
        curr->next = NULL;
    } else if (node == tail){
        // Node is tail
        // 1. Set tail->prev to tail
        curr = tail;
        tail = tail->prev;
        // 2. Set internal pointer to NULL
        curr->prev = NULL;
    } else {
        // Node is somewhere in between
        // 1. Find node
        curr = head->next;
        while(node != curr){
            curr = curr->next;
        }
        // 2. Node found, update neighbor pointers, set internal pointers to NULL
        prevNode = curr->prev;
        nextNode = curr->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        curr->next = NULL;
        curr->prev = NULL;
    }
    return;
}

// Do insert(TCBToInsert, TCBtoadd it to after)
// So calling insert(compute, measure) adds compute after measure

void insertNode(struct TCB* node, struct TCB* precNode, struct TCB* head, struct TCB* tail) {
    // Since C lacks default parameters,
    // The user has to input NULL as 2nd arg if not specified
    if (NULL == precNode){
        precNode = tail;
    }
    if(NULL == head){               //  If the head pointer is pointing to nothing
      head = node;                  //  set the head and tail pointers to point to this node
      tail = node;
    } else if (tail == precNode) {                        //  otherwise, head is not NULL, add the node to the end of the list
        tail->next = node;
        node->prev = tail;          //  note that the tail pointer is still pointing
                                    //  to the prior last node at this point
        tail = node;                //  update the tail pointer
    } else {
        TCB* curr = precNode->next;
        precNode->next = node;
        curr->prev = node;
        node->next=curr;
        node->prev = precNode;
    }
    return;
}

