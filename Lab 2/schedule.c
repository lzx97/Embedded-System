/* Schedule function that keeps track of the global time
*/

void timeDelay(unsigned long msDelay);
int turnCounter;
// Make a pointer to a global time variable (int that increases by one each loop)

void schedule(){

    turnCounter = (turnCounter + 1) % 5;
    // Everytime schedule is called, increment counter (c = (c + 1) % numOfTasks;)
}
