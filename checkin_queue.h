#ifndef CHECKIN_QUEUE_H
#define CHECKIN_QUEUE_H
#include "common.h"
#include "passenger.h"
typedef struct checkinNode{//wrapper around paassenger so that actual nect pointer of passenger wouldnt be affected
    passenger *passenger_ptr;//instead of int in normal queue we have used passenger*
    struct checkinNode *next;
}checkinNode;
typedef struct checkinQueue{
    checkinNode *front;
    checkinNode *rear;
}checkinQueue;
void initialse(checkinQueue* qptr);
int isEmpty(checkinQueue* qptr);
void insert(checkinQueue* qptr,passenger* pptr);
passenger* dequeue(checkinQueue* qptr);
#endif