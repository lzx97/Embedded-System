#ifndef DATASTRUCTSPS_H
#define DATASTRUCTSPS_H
#include <stdio.h>
#include "Bool.h"

typedef struct {
	// Raw
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    unsigned int *respirationRaw;
	// Flags for simulating
    Bool *sysMeasureComplete;
    Bool *diaMeasureComplete;
    Bool *bpIncrease;
	// Flags for selection
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
	// For simulation
    unsigned int *bloodPressure;
    unsigned int *numOfMeasureCalls;
} MeasureDataPS;

typedef struct {
    // Raw
    unsigned int *temperatureRaw;
    unsigned int *systolicPressRaw;
    unsigned int *diastolicPressRaw;
    unsigned int *pulseRateRaw;
    unsigned int *respirationRaw;
    // Corrected
    float *tempCorrected;
    unsigned int *systolicPressCorrected;
    unsigned int *diastolicPressCorrected;
    unsigned int *pulseRateCorrected;
    unsigned int *respirationCorrected;
	// Flags
    Bool *tempSelection;
    Bool *bpSelection;
    Bool *pulseSelection;
} ComputeDataPS;

typedef struct {
    unsigned short *batteryState;

} StatusDataPS;

#endif
