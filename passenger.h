#ifndef PASSENGER_H
#define PASSENGER_H
#include "common.h"
typedef struct passenger{
    int passengerId;
    char name[50];
    int age;
    char gender;
    char contact[15];
    int flightId; 
    int seatNumber;
    ticketType ticketType;
    checkinStatus checkIn;
    boardingStatus board;
    struct passenger *prev,*next;
}passenger;
passenger* searchPassengerById(passenger* head,int passengerId);
int isSeatTaken(passenger *phead, int flightId, int seat);
#endif