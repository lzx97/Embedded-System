#ifndef TFTKEYPAD_H
#define TFTKEYPAD_H

#include "Datastructs.h"
void displayLoop(void *keyPadStruct);
void setupDisplay(void *keyPadStruct);
void drawDefaultMode(void *keyPadStruct);
void drawMenu(void *keyPadStruct);
void drawAnnunciate(void *keyPadStruct);

#endif
