/* Delay for X milliseconds */

void delay(unsigned long time) {
    volatile int i, j;
    for (i = 0; i <= time; i++) {
        for (j = 0; j <= time; j++) {
            // empty
        }
    }
}


