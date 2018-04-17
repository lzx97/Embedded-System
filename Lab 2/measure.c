#include "Bool.h"

int numOfCall = 0;
Bool sysMeasureComplete = FALSE;
Bool diaMeasureComplete = FALSE;
Bool reverse = FALSE;

void measure(void *measureStruct) {
     numOfCall++;
}

void measureTemp(unsigned int *temperature) {
    // cases:   0-15
    //          15-50
    //          50+
    if (!reverse) {
        if (numOfCall % 2 == 0) {
            *temperature += 2;
        }
        else {
            *temperature -= 1;
        }
    }
    else {
        if (numOfCall % 2 == 0) {
            *temperature -= 2;
        }
        else {
            *temperature += 1;
        }
    }
}  

void measureSysPres(unsigned int *sysPres) {
    if (numOfCall == 0 || diaMeasureComplete) {
        if (numOfCall % 2 == 0) {
                *sysPres += 3;
        }
        else {
            *sysPres -= 1;
        }
        if (*sysPres > 100) {
            sysMeasureComplete = TRUE;
        }
    }
}

void measureDiaPres(unsigned int *diaPres) {
    if (numOfCall == 0 || sysMeasureComplete) {
        while (*diaPres < 40) {
            if (numOfCall % 2 == 0) {
                *diaPres -= 2;
            }
            else  {
                *diaPres += 1;
            }
        }
        diaMeasureComplete = TRUE;
    }
}

