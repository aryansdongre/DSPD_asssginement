#ifndef FLIGHT_H
#define FLIGHT_H
#include "common.h"
typedef struct flight{
    int flightId;
    char source[30],destination[30];//flight number assumed to be same as flightId
    char departureTime[6],arrivalTime[6];
    int totalSeats,availableSeats;
    flightStatus status;
    struct flight *prev,*next;
}flight;
status_code addFlight(flight** head,flight* flptr);
flight* searchById(flight* head,int flightId);//returned flight* since it will be used in add passenger
status_code searchBySource(flight* head,char source[]);
status_code searchByDestination(flight* head,char destination[]);
void display(flight* fptr);//this function is used on the above three functions while calling do display(searchById());
void displaySortedByDepartureTime(flight* head);
void displaySortedBySource(flight* head);
void displaySortedByDestination(flight* head);
void displaySortedBySourceThenByDepartureTime(flight* head);
#endif