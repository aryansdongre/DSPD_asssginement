#ifndef CHECKIN_QUEUE2_H
#define CHECKIN_QUEUE2_H
#include "common.h"
#include "passenger.h"
typedef struct checkinQueue{//with this implementation original order of linked list of passengers will be affected therefore cant use
    passenger* front;
    passenger* rear;
};
#endif