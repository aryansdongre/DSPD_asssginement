#ifndef PASSENGER_H
#define PASSENGER_H
#include "common.h"
typedef struct passenger{
    int passengerId;
    char name[50];
    int age;
    char gender;
    int contact[15];
    int flightId; 
    char seatNumber;
    ticketType ticketType;
    checkinStatus checkIn;
    boardingStatus board;
    struct passenger *prev,*next;
}passenger;
status_code addPassenger(flight* fhead,passenger* pptr,passenger** phead);
passenger* searchPassengerById(passenger* head,int passengerId);
int isSeatTaken(passenger *phead, int flightId, int seat);
#endif