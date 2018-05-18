#ifndef TFTKEYPAD_H
#define TFTKEYPAD_H

#include "Datastructs.h"
void displayLoop(void *tftStruct);
void setupDisplay(void *tftStruct);
void drawDefaultMode(void *tftStruct);
void drawMenu(void *tftStruct);
void drawAnnunciate(void *tftStruct);
void flashAlarms(void *tftStruct);

#endif
