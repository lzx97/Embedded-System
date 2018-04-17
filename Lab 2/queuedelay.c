/* Delay for X milliseconds */

void timeDelay(unsigned long delay1){
    volatile int c, d;
    for (c = 1; c <= 32767; c++)
        for (d = 1; d <= delay1; d++){
        }
    }
}


