#define M_PI = 3.1415926535;

#include "DataStructs.h"
#include <Arduino.h>
#include "EKGCapture.h"

void EKGCapture(void *EKGStruct) {
    MeasureData* eData = (MeasureData*) EKGStruct;

    double freq = analogRead(EKG_PIN) * 2 * M_PI;

    unsigned int fs_period = round(1000000 * (1.0 / FS));
    
    int i = 0;
    for (i = 0; i < 256; i++) {
        unsigned long microsecond = micros();
        (*(eData->vReal))[i] = 3.3 * sin(2 * M_PI * freq * i / FS);
        (*(eData->vImag))[i] = 0;
        

        while (micros() < (microsecond + fs_period)) {}
        //Serial.println((*(eData->vReal))[i]);
        Serial.println(i);
    }
}
