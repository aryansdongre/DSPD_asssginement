#ifndef COMMON_OPERATIONS_H
#define COMMON_OPERATIONS_H
#include "passenger.h"
#include "flight.h"
status_code addPassenger(flight* fhead,passenger* pptr,passenger** phead);
status_code deletePassenger(passenger**phead,int passengerId,flight* fhead);//to search flightByID and passengerById
status_code deleteFlight(flight**fhead,int flightId,passenger* phead);
#endif