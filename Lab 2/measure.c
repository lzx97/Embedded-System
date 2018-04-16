int numOfCall = 0;

void measure(void *measureStruct) {
     numOfCall++;
}

void calcTemperature(int *temperature) {
    // cases:   0-15
    //          15-50
    //          50+
    if (*temperature <= 50) {
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

