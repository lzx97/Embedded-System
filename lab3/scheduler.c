#include "DataStructs.h"

// Don't forget to add functions to header file

void scheduler(TCB **taskQueue) {
    TCB* curr = head;
    while (curr != tail){
        (curr->taskPtr))(curr->taskDataPtr);
        curr = curr->next;
    }
    // While loop ends before tail is executed
    // So we call it one last time to run through everything
    (curr->taskPtr))(curr->taskDataPtr);
    // Delay one second
    delay(1000);
    globalCounter++;
}


void deleteNode(TCB* node) {
    TCB* curr;
    TCB* prevNode;
    TCB* nextNode;
    if (node == head){
        // Node is head
        // 1. Set head->next to head
        curr = head;
        head = head->next;
        // 2. Set internal pointers to NULL
        curr->next = NULL;
    } else if (node == tail){
        // Node is tail
        // 1. Set tail->prev to tail
        curr = tail;
        tail = tail->prev;
        // 2. Set internal pointer to NULL
        curr->prev = NULL;
    } else {
        // Node is somewhere in between
        // 1. Find node
        curr = head->next;
        while(node != curr){
            curr = curr->next;
        }
        // 2. Node found, update neighbor pointers, set internal pointers to NULL
        prevNode = curr->prev;
        nextNode = curr->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        curr->next = NULL;
        curr->prev = NULL;
    }
    return;
}

// Do something like insert(TCBToInsert, TCBtoadd it to after)
// So calling insert(compute, measure) adds compute after measure
void insertNode(TCB* node, TCB* precNode) {
    // Since C lacks default parameters,
    // The user has to input NULL as 2nd arg if not specified
    if (NULL == precNode){
        precNode = tail;
    }
    if(NULL == head){               //  If the head pointer is pointing to nothing
      head = node;                  //  set the head and tail pointers to point to this node
      tail = node;
    } else if (tail == precNode) {                        //  otherwise, head is not NULL, add the node to the end of the list
        tail->next = node;
        node->prev = tail;          //  note that the tail pointer is still pointing
                                    //  to the prior last node at this point
        tail = node;                //  update the tail pointer
    } else {
        TCB* curr = precNode->next;
        precNode->next = node;
        curr->prev = node;
        node->next=curr;
        node->prev = precNode;
    }
    return;
}
