#ifndef SCHEDULERSC_H
#define SCHEDULERSC_H

#include "DataStructs.h"

void scheduler();
void deleteNode(TCB* node);
void insertNode(TCB* node, TCB* precNode);
#endif
