#ifndef BOARDING_HISTORY_H
#define BOARDING_HISTORY_H
#include "common.h"
#include "passenger.h"
typedef struct history
{
    // int passengerId;
    // char name[50];
    // int flightId;
    // char seatNumber[5];
    passenger* passenger_ptr;
    int boardingTime[6];
    struct history* next;
}history;
typedef struct boardingHistory
{
    history* top;
}boardingHistory;
void initialise(boardingHistory* hptr);
void push(boardingHistory* hptr,passenger* pptr);//whenever deque in queue of boarding we update boarding history(this function caled inside dequeue of boarding_queue),pptr taken from dequeue
#endif