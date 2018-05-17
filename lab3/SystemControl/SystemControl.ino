#ifdef __cplusplus
extern "C" {
#endif
#include "Bool.h"
#include "DataStructs.h"
#include "warningSC.h"
//#include "schedulerSC.h"
#ifdef __cplusplus
}
#endif
#include "computeSC.h"
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
Bool tempIncrease = FALSE;
Bool bpIncrease = FALSE;
unsigned int numOfMeasureCalls = 0;

const unsigned int measureInterval = 5;
const unsigned int computeInterval = 5;
const unsigned int displayInterval = 5;
const unsigned int warningInterval = 1;
const unsigned int statusInterval = 5;

char bloodPressCorrectedBuf[48] = {};
char tempCorrectedBuf[32] = {};
char pulseRateCorrectedBuf[24] = {};

char bloodPressRawBuf[40] = {};
char temperatureRawBuf[16] = {};
char pulseRateRawBuf[24] = {};


char batteryState[3];
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
    Serial1.begin(9600);
    Serial.begin(9600);
    // Add variables to measure struct
    mData.globalTime = &globalTime;
    mData.measureInterval = &measureInterval;
    
    // Raw data
    mData.bloodPressRawBuf = &bloodPressRawBuf;
    mData.pulseRateRawBuf = &pulseRateRawBuf;
    mData.temperatureRawBuf = &temperatureRawBuf;
    
    // measure selections
    mData.tempSelection = &tempSelection;
    mData.bpSelection = &bpSelection;
    mData.pulseSelection = &pulseSelection;
//    mData.MeasureTCB = &MeasureTCB;
//    mData.ComputeTCB = &ComputeTCB;


    // Add variables to compute struct
    cData.globalTime = &globalTime;
    cData.computeInterval = &computeInterval;
    cData.tempSelection = &tempSelection;
    cData.bpSelection = &bpSelection;
    cData.pulseSelection = &pulseSelection;
    cData.tempCorrectedBuf = &tempCorrectedBuf;
    cData.bloodPressCorrectedBuf = &bloodPressCorrectedBuf;
    cData.pulseRateCorrectedBuf = &pulseRateCorrectedBuf;


    // Add variables to display struct
    dData.globalTime = &globalTime;
    dData.displayInterval = &displayInterval;
    dData.bloodPressCorrectedBuf = &bloodPressCorrectedBuf;
    dData.pulseRateCorrectedBuf = &pulseRateCorrectedBuf;
    dData.tempCorrectedBuf = &tempCorrectedBuf;
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
    
    // Raw Data
    wData.bloodPressRawBuf = &bloodPressRawBuf;
    wData.pulseRateRawBuf = &pulseRateRawBuf;
    wData.temperatureRawBuf = &temperatureRawBuf;
    wData.bloodPressCorrectedBuf = &bloodPressCorrectedBuf;
    wData.pulseRateCorrectedBuf = &pulseRateCorrectedBuf;
    wData.tempCorrectedBuf = &tempCorrectedBuf;
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

    setupDisplay(&tftTCB);
    //Serial.println("End of setup");
    
}

void loop(void) {
    //Serial.println("Start of loop: are we here?");
    timeNow = millis();
    TCB* curr = head;
    TCB* oldcurr;
    while (curr != tail){
        //Serial.println("Task begun");delay(50);

        (*(curr->taskPtr))(curr->taskDataPtr);
        if ((curr == &MeasureTCB) && (globalTime % measureInterval == 0)){
            insertNode(&ComputeTCB, &MeasureTCB, head, tail);
        }
        oldcurr = curr;
        curr = curr->next;
        if ((oldcurr == &ComputeTCB) && (globalTime % measureInterval == 0)){
          deleteNode(&ComputeTCB,head,tail);
        }
        
    }       
    // While loop ends before tail is executed
    // So we call it one last time to run through everything
    (*(curr->taskPtr))(curr->taskDataPtr);
    // Delay one second
    globalTime++;


    Serial.print("Latest measured temp value: ");
    Serial.print(temperatureRawBuf[0]);
    Serial.print(temperatureRawBuf[1]);
    Serial.print(temperatureRawBuf[2]);
    Serial.println(temperatureRawBuf[3]);
    
    
    Serial.print("Current corrected temp value: ");
    Serial.print(tempCorrectedBuf[0]);
    Serial.print(tempCorrectedBuf[1]);
    Serial.print(tempCorrectedBuf[2]);
    Serial.println(tempCorrectedBuf[3]);
    
    Serial.print("Current corrected pulse value: ");
    Serial.print(pulseRateCorrectedBuf[0]);
    Serial.print(pulseRateCorrectedBuf[1]);
    Serial.println(pulseRateCorrectedBuf[2]);
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

