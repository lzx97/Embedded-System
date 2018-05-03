
int globalCounter;

// send a String to PS and receive a data packet from the PS
void communicationSC(char *data, void *dataStruct) {
    // send process
    if (globalCounter % 5 == 0) {   // Every 5 second
        // Call measure/compute/batteryStatus
        if (data[0] == 'M' || data[0] == 'C' || data[0] == 'B') {  
            int bytesent = Serial.write(data); // send
            Serial.print(data[0]);
        }
    }
    if (data[0] == 'W') {
        int bytesent = Serial.write(data); // send
        Serial.print(data[0]);
    }

    // receive process
    // TODO: implement
}


void communicationPS() {
    // TODO: implement
    if (Serial.available() > 0) {
        char received[30];
        int i = 0;
        while (Serial.available() > 0) {
            received[i] = Serial.read();
            i++;
        }
        
        //

        if (received[1] == 'M') {
            measure();
            Serial.write('');
        }
    }
}
