#ifndef TFTKEYPAD_H
#define TFTKEYPAD_H

#include "Datastructs.h"
void displayLoop(void *keyPadStruct);
void setupDisplay(void *keyPadStruct);
void drawDefaultMode(void *keyPadStruct);
void displayMenu(void *keyPadStruct);
void displayAnnunciate(void *keyPadStruct);

#endif
