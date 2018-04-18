/* Schedule function that keeps track of the global time
*/

void timeDelay(unsigned long msDelay);
int turnCounter;
int globalTime;
unsigned long delayTime;
// Make a pointer to a global time variable (int that increases by one each loop)

// Needs to access taskQueue, turnCounter, globalTime
void schedule(void *taskQueue){
    funPtr = taskQueue[turnCounter]; // Find the next function pointer
    void (*funPtr)(void*);  // Call the corresponding function

    // Update time and turnCounter
    turnCounter = (turnCounter + 1) % sizeof(taskQueue); // Loops from 0,1,2,3,4,5,0,1,...
    globalTime++;
    timeDelay(delayTime); // Choose delayTime such that it takes one second for timeDelay
}
