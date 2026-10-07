#include "digiyatra.h"
passenger *searchPassengerById(passenger *head, int passengerId)
{
    passenger *pptr = head;
    passenger *ret_ptr = NULL;
    int found = 0;
    while (pptr != NULL && !found)
    {
        if (pptr->passengerId == passengerId)
        {
            found = 1;
            ret_ptr = pptr;
        }
        pptr = pptr->next;
    }
    return ret_ptr;
}
int isSeatTaken(passenger *phead, int flightId, int seat)
{
    for (passenger *p = phead; p != NULL; p = p->next)
        if (p->flightId == flightId && p->seatNumber == seat)
        {
            return 1;
        }
    return 0;
}
status_code addPassenger(flight *head, passenger *pptr, passenger **phead)
{
    status_code sc = FAILURE;
    flight *fptr = searchById(head, pptr->flightId);
    if (fptr == NULL)
    {
        sc = FAILURE;
    }
    else if (searchPassengerById(*phead, pptr->passengerId) == NULL) // if passenger doesnt exist
    {
        if (fptr->availableSeats == 0)
        {
            sc = FAILURE;
        }
        else
        {
            int seat = 1;
            while (seat <= fptr->totalSeats && isSeatTaken(*phead, fptr->flightId, seat))
            {
                seat++;
            }
            pptr->seatNumber = seat;
            pptr->checkIn = NOT_CHECKED_IN;
            pptr->board = NOT_BOARDED;
            fptr->availableSeats--;
            pptr->next = *phead;
            pptr->prev = NULL;
            if (*phead != NULL)
            {
                (*phead)->prev = pptr;
            }
            *phead = pptr;
            sc = SUCCESS;
        }
    }
    return sc;
}
status_code deletePassenger(passenger **phead, int passengerId, flight *fhead)
{
    status_code sc = FAILURE;
    passenger *pptr = searchPassengerById(*phead, passengerId);
    if (pptr != NULL)
    {
        int flightId = pptr->flightId;
        flight *fptr = searchById(fhead, flightId);
        if (fptr != NULL)
        {

            if (pptr->prev != NULL)
            {
                pptr->prev->next = pptr->next;
            }
            else
            {
                *phead = pptr->next;
            }
            if (pptr->next != NULL)
            {
                pptr->next->prev = pptr->prev;
            }
            fptr->availableSeats++;
            free(pptr);
            sc = SUCCESS;
        }
    }
    return sc;
}