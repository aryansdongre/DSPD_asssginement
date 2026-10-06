#ifndef BOARDING_QUEUE
#define BOARDING_QUEUE
#include "common.h"
#include "passenger.h"
typedef struct boardingNode
{
    passenger* passenger_ptr;
    //ticketType type; can be skipped
    struct boardingNode* next;
}boardingNode;
typedef struct boardingQueue{
    boardingNode *front;
    boardingNode *rear;
}boardingQueue;
typedef struct priorityBoardingQueue
{
    boardingQueue arr[3];
}priorityBoardingQueue;
void initialise(priorityBoardingQueue *qptr);
int  isEmpty(priorityBoardingQueue *qptr);
void  insert(priorityBoardingQueue *qptr, passenger *pptr);
passenger* dequeue(priorityBoardingQueue *q);//passenger* returned and not boardingNode* similar to how we do in normal queue ie return int and not node* because it gets freed inside function dequeue
#endif