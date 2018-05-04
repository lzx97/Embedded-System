#include <stdio.h>
#include "DataStructs.h"
//#include "peripheralCom.h"
#include "computeSC.h"

int globalCounter;

// SC part of the compute. Send data packet to call compute. 
void computeSC(void *computeStruct) {
    // create string to be sent to the PS
  char *str = "CbtpCompute";
  
    // transfer and receive 
    communicationSC(str, computeStruct);
}
