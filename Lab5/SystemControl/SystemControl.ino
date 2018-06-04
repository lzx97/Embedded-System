#ifdef __cplusplus
extern "C" {
#endif
#include "Bool.h"
#include "DataStructs.h"
//#include "schedulerSC.h"
#ifdef __cplusplus
}
#endif
#include "warningSC.h"
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

char bloodPressCorrectedBuf[48] = {'0','0','0','0','0','0','0','0',
                                   '0','0','0','0','0','0','0','0',
                                   '0','0','0','0','0','0','0','0',
                                   '0','0','0','0','0','0','0','0',
                                   '0','0','0','0','0','0','0','0',
                                   '0','0','0','0','0','0','0','0'};
char tempCorrectedBuf[32] = {'0','0','0','0','0','0','0','0',
                             '0','0','0','0','0','0','0','0',
                             '0','0','0','0','0','0','0','0',
                             '0','0','0','0','0','0','0','0'};
char pulseRateCorrectedBuf[24] = {'0','0','0','0','0','0','0','0',
                                  '0','0','0','0','0','0','0','0',
                                  '0','0','0','0','0','0','0','0'};
char respirationRateCorrectedBuf[16]={'0','0','0','0','0','0','0','0',
                                      '0','0','0','0','0','0','0','0'}; // Maybe change the size of this here and everywhere else

char bloodPressRawBuf[40] = {'0','0','0','0','0','0','0','0',
                             '0','0','0','0','0','0','0','0',
                             '0','0','0','0','0','0','0','0',
                             '0','0','0','0','0','0','0','0',
                             '0','0','0','0','0','0','0','0'};
char temperatureRawBuf[16] = {'0','0','0','0','0','0','0','0',
                              '0','0','0','0','0','0','0','0'};
char pulseRateRawBuf[24] =    {'0','0','0','0','0','0','0','0',
                               '0','0','0','0','0','0','0','0',
                               '0','0','0','0','0','0','0','0'};
char respirationRateRawBuf[16] = {'0','0','0','0','0','0','0','0',
                                  '0','0','0','0','0','0','0','0'};

char batteryState[3] = {'0','0','0'};

double vReal[256];
double vImag[256];
double freqBuf[16];

Bool pulseWarning = FALSE;
Bool pulseAlarm = FALSE;
Bool tempWarning = FALSE;
Bool tempAlarm = FALSE;
Bool sysWarning = FALSE;
Bool diasWarning = FALSE;
Bool sysAlarm = FALSE;
Bool respAlarm = FALSE;
Bool batteryLow = FALSE;
/*
Bool bpHigh = FALSE;
Bool bpLow = FALSE;
Bool tempOff = FALSE;
Bool pulseOff = FALSE;
Bool batteryLow = FALSE;
Bool sysAlarm = FALSE;
Bool respOff = FALSE;
*/
Bool tempSelection = TRUE;
Bool bpSelection = TRUE;
Bool pulseSelection = TRUE;
Bool respSelection = TRUE;
Bool EKGSelection = TRUE;

Bool sysAlarmAcknowledge = TRUE;
Bool tempAlarmAcknowledge = TRUE;
Bool pulseAlarmAcknowledge = TRUE;
Bool respAlarmAcknowledge = TRUE;

unsigned int sysAlarmTimer = 0;
unsigned int tempAlarmTimer = 0;
unsigned int pulseAlarmTimer = 0;
unsigned int respAlarmTimer = 0;

Bool sysFlash = FALSE;
Bool diasFlash = FALSE;
Bool tempFlash = FALSE;
Bool pulseFlash = FALSE;

unsigned long lastSysFlash = 0;
unsigned long lastDiasFlash = 0;
unsigned long lastTempFlash = 0;
unsigned long lastPulseFlash = 0;

unsigned long timeNow = 0;
Bool justPressed = FALSE;
Bool displayOff = FALSE;

MeasureData mData;
ComputeData cData;
TFTData dData;
WarningAlarmData wData;
StatusData stData;
EKGCapData ecData;
EKGProData epData;

void setup(void) {
    Serial1.begin(9600);
    //Serial.begin(9600);
    // Add variables to measure struct
    mData.globalTime = &globalTime;
    mData.measureInterval = &measureInterval;
    
    // Raw data
    mData.bloodPressRawBuf = &bloodPressRawBuf;
    mData.pulseRateRawBuf = &pulseRateRawBuf;
    mData.temperatureRawBuf = &temperatureRawBuf;
    mData.respirationRateRawBuf = &respirationRateRawBuf;
    mData.vReal = &vReal;
    mData.vImag = &vImag;
    
    
    // measure selections
    mData.tempSelection = &tempSelection;
    mData.bpSelection = &bpSelection;
    mData.pulseSelection = &pulseSelection;
    mData.respSelection = &respSelection;


    // Add variables to compute struct
    cData.globalTime = &globalTime;
    cData.computeInterval = &computeInterval;
    cData.tempSelection = &tempSelection;
    cData.bpSelection = &bpSelection;
    cData.pulseSelection = &pulseSelection;
    cData.respSelection = &respSelection;
    cData.tempCorrectedBuf = &tempCorrectedBuf;
    cData.bloodPressCorrectedBuf = &bloodPressCorrectedBuf;
    cData.pulseRateCorrectedBuf = &pulseRateCorrectedBuf;
    cData.respirationRateCorrectedBuf = &respirationRateCorrectedBuf;
    cData.freqBuf = &freqBuf;
    cData.vReal = &vReal;
    cData.vImag = &vImag;


    // Add variables to display struct
    dData.globalTime = &globalTime;
    dData.displayInterval = &displayInterval;
    dData.bloodPressCorrectedBuf = &bloodPressCorrectedBuf;
    dData.pulseRateCorrectedBuf = &pulseRateCorrectedBuf;
    dData.tempCorrectedBuf = &tempCorrectedBuf;
    dData.respirationRateCorrectedBuf = &respirationRateCorrectedBuf;
    dData.freqBuf = &freqBuf;
    
    dData.pulseWarning = &pulseWarning;
    dData.pulseAlarm = &pulseAlarm;
    dData.tempWarning = &tempWarning;
    dData.tempAlarm = &tempAlarm;
    dData.sysWarning = &sysWarning;
    dData.diasWarning = &diasWarning;
    dData.sysAlarm = &sysAlarm;
    dData.respAlarm = &respAlarm;
    dData.batteryLow = &batteryLow;

    dData.sysAlarmAcknowledge = &sysAlarmAcknowledge;
    dData.sysAlarmTimer = &sysAlarmTimer;
    dData.tempAlarmAcknowledge = &tempAlarmAcknowledge;
    dData.tempAlarmTimer = &tempAlarmTimer;
    dData.pulseAlarmAcknowledge = &pulseAlarmAcknowledge;
    dData.pulseAlarmTimer = &pulseAlarmTimer;
    dData.respAlarmAcknowledge = &respAlarmAcknowledge;
    dData.respAlarmTimer = &respAlarmTimer;

    dData.batteryState = &batteryState;
    dData.displayInterval = &displayInterval;
    dData.tempSelection = &tempSelection;
    dData.bpSelection = &bpSelection;
    dData.pulseSelection = &pulseSelection;
    dData.respSelection = &respSelection;
    dData.EKGSelection = &EKGSelection;
    dData.sysAlarm = &sysAlarm;
    dData.timeNow = &timeNow;
    dData.justPressed = &justPressed;

    dData.lastSysFlash = &lastSysFlash;
    dData.sysFlash = &sysFlash;
    dData.lastDiasFlash = &lastDiasFlash;
    dData.diasFlash = &diasFlash;
    dData.lastTempFlash = &lastTempFlash;
    dData.tempFlash = &tempFlash;
    dData.lastPulseFlash = &lastPulseFlash;
    dData.pulseFlash = &pulseFlash;
    dData.displayOff = &displayOff;


    // Add values to warning/alarm struct
    wData.globalTime = &globalTime;
    wData.warningInterval = &warningInterval;
    
    // Raw Data
    wData.bloodPressRawBuf = &bloodPressRawBuf;
    wData.pulseRateRawBuf = &pulseRateRawBuf;
    wData.temperatureRawBuf = &temperatureRawBuf;
    /*
     * Is mData.respirationRateRawBuf = &respirationRateRawBuf;
     * supposed to be here??
     */
        wData.respirationRateRawBuf = &respirationRateRawBuf;
    /*
     * Should it be wData.respirationRateRawBuf = &respirationRateRawBuf;?
    */
    wData.bloodPressCorrectedBuf = &bloodPressCorrectedBuf;
    wData.pulseRateCorrectedBuf = &pulseRateCorrectedBuf;
    wData.tempCorrectedBuf = &tempCorrectedBuf;
    wData.respirationRateCorrectedBuf = &respirationRateCorrectedBuf;
    wData.batteryState = &batteryState;
    wData.pulseWarning = &pulseWarning;
    wData.pulseAlarm = &pulseAlarm;
    wData.tempWarning = &tempWarning;
    wData.tempAlarm = &tempAlarm;
    wData.sysWarning = &sysWarning;
    wData.diasWarning = &diasWarning;
    wData.sysAlarm = &sysAlarm;
    wData.respAlarm = &respAlarm;
    wData.batteryLow = &batteryLow;

    wData.sysAlarmAcknowledge = &sysAlarmAcknowledge;
    wData.sysAlarmTimer = &sysAlarmTimer;
    wData.tempAlarmAcknowledge = &tempAlarmAcknowledge;
    wData.tempAlarmTimer = &tempAlarmTimer;
    wData.pulseAlarmAcknowledge = &pulseAlarmAcknowledge;
    wData.pulseAlarmTimer = &pulseAlarmTimer;
    wData.respAlarmAcknowledge = &respAlarmAcknowledge;
    wData.respAlarmTimer = &respAlarmTimer;

    ecData.vReal = &vReal;
    ecData.vImag = &vImag;

    epData.vReal = &vReal;
    epData.vImag = &vImag;
    epData.freqBuf = &freqBuf;

    
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
    delay(100);


    /*
    while (1) {
        if (Serial.available() > 0) {
            char inbyte = Serial.read();
            if (inbyte == 'I') {
                break;
            }
        }
    }

    Serial.println("EE 474 Medical Monitoring System");
    Serial.println("Patient: someone");
    Serial.println("Doctors: Chris, Hideaki, Zixiang");
    */
}

void loop(void) {
    //Serial.println("Start of loop: are we here?");
    timeNow = millis();
    TCB* curr = head;
    TCB* oldcurr;
    while (curr != tail){
        //Serial.println("Task begun");delay(50);
         //Serial.println("Inside task loop");
        (*(curr->taskPtr))(curr->taskDataPtr);
        if ((curr == &MeasureTCB) && (globalTime % measureInterval == 0)){
            //Serial.println("adding compute");
            insertNode(&ComputeTCB, &MeasureTCB, head, tail);
            //Serial.println("compute added");
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
    //Serial.println("Done with loop"); delay(50);
    // Delay one second
    globalTime++;
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

void serialEvent() {
    
    while (Serial.available() > 0) {
        char inbyte = Serial.read();
        if (inbyte == 'P') {
            Serial.println("Paused");
            while (inbyte != 'S') {
                if (Serial.available() > 0) {
                    inbyte = Serial.read();
                }
            }
            Serial.println("Resumed");
        }
        /*
        else if (inbyte == 'S') {
            // schecule measure
        }
        */
        else if (inbyte == 'D') {
            displayOff = (displayOff) ? FALSE : TRUE;
            if (displayOff){
                Serial.println("Display switched off");
            } else {
                Serial.println("Display switched on");
            }
        }
        else if (inbyte == 'M') {
            // print all measure data
            
            Serial.println("Printing latest measured data");
            Serial.print("Blood pressure: ");  Serial.print(bloodPressRawBuf[0]);Serial.print(bloodPressRawBuf[1]); Serial.print(bloodPressRawBuf[2]);
            Serial.print (" / "); Serial.print(bloodPressRawBuf[24]); Serial.println(bloodPressRawBuf[25]);
            Serial.print("Body temperature: "); Serial.print(temperatureRawBuf[0]); Serial.println(temperatureRawBuf[1]);
            Serial.print("Pulse rate: "); Serial.print(pulseRateRawBuf[0]);Serial.print(pulseRateRawBuf[1]);Serial.println(pulseRateRawBuf[2]);
            Serial.print("Respiratory rate: "); Serial.print(respirationRateRawBuf[0]); Serial.println(respirationRateRawBuf[1]);
            Serial.print("EKG rate: "); Serial.println(freqBuf[0]);
            Serial.println("All the latest measured data printed");
            
        }
        else if (inbyte == 'W') {

            // print all warning-alarm data
            Serial.println("\nPrinting latest warning/alarm data");
            Serial.print("Blood pressure: ");  Serial.print(bloodPressCorrectedBuf[0]);Serial.print(bloodPressCorrectedBuf[1]);Serial.print(bloodPressCorrectedBuf[2]);
            Serial.print (" / "); Serial.print(bloodPressCorrectedBuf[24]); Serial.print(bloodPressCorrectedBuf[25]); Serial.print(bloodPressCorrectedBuf[26]);
            if (sysAlarm) {
              Serial.print(" ALARM: Systolic out of range ");
            } else if (sysWarning || diasWarning) {
              Serial.print(" WARNING: ");
              if (sysWarning && diasWarning){
                Serial.print("Systolic & Diastolic out of range");
              } else if(sysWarning){
                Serial.print("Systolic out of range");
              } else {
                Serial.print("Diastolic out of range");
              }
            }
            Serial.println("");
            Serial.print("Body temperature: "); Serial.print(tempCorrectedBuf[0]); Serial.print(tempCorrectedBuf[1]);Serial.print(tempCorrectedBuf[2]);Serial.print(tempCorrectedBuf[3]);
            if (tempAlarm){
              Serial.print(" ALARM: Temperature out of range ");
            } else if (tempWarning) {
              Serial.print(" Warning: Temperature out of range ");
            }
            Serial.println("");
            Serial.print("Pulse rate: "); Serial.print(pulseRateCorrectedBuf[0]);Serial.print(pulseRateCorrectedBuf[1]);Serial.print(pulseRateCorrectedBuf[2]);
            if (pulseAlarm){
              Serial.print(" ALARM: Pulserate out of range ");
            } else if (pulseWarning) {
              Serial.print(" Warning: Pulserate out of range ");
            }
            Serial.println("");
            Serial.print("Respiratory rate: "); Serial.print(respirationRateCorrectedBuf[0]); Serial.print(respirationRateCorrectedBuf[1]);
            if (respAlarm){
              Serial.print(" ALARM: Respiratory rate out of range");
            }
            Serial.println("");
            Serial.print("EKG rate: "); Serial.println(freqBuf[0]);            
            Serial.println("All the latest warning/alarm data printed");
        }
        else {
            Serial.println("Invalid Input");
        }
    }
}
