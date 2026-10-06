#ifndef COMMON_H
#define COMMON_H
typedef enum{SCHEDULED,CHECKIN_OPEN,BOARDING,DEPARTED,CANCELLED}flightStatus;
typedef enum{NOT_CHECKED_IN,CHECKED_IN}checkinStatus;
typedef enum{NOT_BOARDED,BOARDED}boardingStatus;
typedef enum{ECONOMY,BUSINESS,FIRST_CLASS}ticketType;
typedef enum{FAILURE,SUCCESS}status_code;
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#endif