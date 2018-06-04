#include "DataStructs.h"
#include <arduinoFFT.h>
#include <math.h>
#include <Arduino.h>
#include "EKGCapture.h"


void EKGProcess(void *EKGStruct) {
    ComputeData *eData = (ComputeData*) EKGStruct;

    arduinoFFT fft = arduinoFFT();

    fft.Windowing(*(eData->vReal), SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    fft.Compute(*(eData->vReal), *(eData->vImag), SAMPLES, FFT_FORWARD);
    fft.ComplexToMagnitude(*(eData->vReal), *(eData->vImag), SAMPLES);

    double peak = fft.MajorPeak(*(eData->vReal), SAMPLES, FS);

    //for (int i = 16; i > 0; i--) {
      //  (*(eData->freqBuf))[i] = (*(eData->freqBuf))[i - 1];
    //}
    (*(eData->freqBuf))[0] = peak;
    //Serial.print("peak ======= ");
    //Serial.println(peak);
}
