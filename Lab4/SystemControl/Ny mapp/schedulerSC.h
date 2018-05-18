#ifndef SCHEDULERSC_H
#define SCHEDULERSC_H

#include "DataStructs.h"

void scheduler(struct TCB* head, struct TCB* tail, unsigned long globalTime);
void deleteNode(struct TCB* node, struct TCB* head, struct TCB* tail);
void insertNode(struct TCB* node,struct TCB* precNode, struct TCB* head, struct TCB* tail);
#endif
