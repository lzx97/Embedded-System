#include "DataStructs.h"
#include <math.h>
#include <Arduino.h>
#include "EKGCapture.h"

void EKGCapure(void *EKGStruct) {
    EKGCapData* eData = (EKGCapData*) EKGStruct;

    freq = analogRead(EKG_PIN) * 2 * M_PI;

    for (int i = 0; i < 256; i++) {
        (*(eData->vReal))[i] = 3.3 * sin(2 * M_PI * freq * i / FS);
        (*(eData->vReal))[i] = 0;
    }
}