#include "digiyatra.h"
flight *searchById(flight *head, int flightId)
{
    flight *fptr = head;
    flight *ret_ptr = NULL;
    int found = 0;
    while (fptr != NULL && !found)
    {
        if (fptr->flightId == flightId)
        {
            found = 1;
            ret_ptr = fptr;
        }
        fptr = fptr->next;
    }
    return ret_ptr;
}
status_code searchBySource(flight *head, char source[])
{
    flight *fptr = head;
    status_code sc = FAILURE;
    while (fptr != NULL)
    {
        if (strcmp(fptr->source, source) == 0)
        {
            display(fptr);
            sc = SUCCESS;
        }
        fptr = fptr->next;
    }
    return sc;
}
status_code searchByDestination(flight *head, char destination[])
{
    flight *fptr = head;
    status_code sc = FAILURE;
    while (fptr != NULL)
    {
        if (strcmp(fptr->destination, destination) == 0)
        {
            display(fptr);
            sc = SUCCESS;
        }
        fptr = fptr->next;
    }
    return sc;
}
void display(flight *fptr)
{
    if (fptr == NULL)
    {
        printf("No flight to display\n");
    }
    else
    {
        printf("Flight ID : %d\n", fptr->flightId);
        printf("Source : %s\n", fptr->source);
        printf("Destination : %s\n", fptr->destination);
        printf("Departure Time : %s\n", fptr->departureTime);
        printf("Arrival Time : %s\n", fptr->arrivalTime);
        printf("Total Seats : %d\n", fptr->totalSeats);
        printf("Available Seatsn : %d\n", fptr->availableSeats);
        printf("-----------------------------\n");
    }
}
void displaySortedByDepartureTime(flight *head)
{
    flight *fptr = head;
    if(fptr==NULL)
    {
        printf("No flights\n");
    }
    while (fptr != NULL)
    {
        display(fptr);
        fptr = fptr->next;
    }
}
void displaySortedBySource(flight *head)
{
    int n = 0;
    flight *fptr = head;
    while (fptr != NULL)
    {
        n++;
        fptr = fptr->next;
    }
    flight **arr = malloc(n * sizeof(flight *)); // creating an array of flight* in heap
    int i = 0;
    for (fptr = head; fptr != NULL; fptr = fptr->next)
    {
        arr[i++] = fptr;
    }
    for (i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(arr[j]->source, arr[j + 1]->source) > 0)
            {
                flight *tptr = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tptr;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        display(arr[i]);
    }
    free(arr);
}
void displaySortedByDestination(flight *head)
{
    int n = 0;
    flight *fptr = head;
    while (fptr != NULL)
    {
        n++;
        fptr = fptr->next;
    }
    flight **arr = malloc(n * sizeof(flight *)); // creating an array of flight* in heap
    int i = 0;
    for (fptr = head; fptr != NULL; fptr = fptr->next)
    {
        arr[i++] = fptr;
    }
    for (i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(arr[j]->destination, arr[j + 1]->destination) > 0)
            {
                flight *tptr = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tptr;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        display(arr[i]);
    }
    free(arr);
}
void displaySortedBySourceThenByDepartureTime(flight *head)
{
    int n = 0;
    flight *fptr = head;
    while (fptr != NULL)
    {
        n++;
        fptr = fptr->next;
    }
    flight **arr = malloc(n * sizeof(flight *)); // creating an array of flight* in heap
    int i = 0;
    for (fptr = head; fptr != NULL; fptr = fptr->next)
    {
        arr[i++] = fptr;
    }
    for (i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            int c=strcmp(arr[j]->source, arr[j + 1]->source);
            if(c==0)//ie if same source change the comparison to departure time
            {
                c=strcmp(arr[j]->departureTime, arr[j + 1]->departureTime);
            }
            if(c > 0)
            {
                flight *tptr = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tptr;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        display(arr[i]);
    }
    free(arr);
}
status_code addFlight(flight** head,flight* flptr)
{
    status_code sc=SUCCESS;
    if(searchById(*head,flptr->flightId)!=NULL)
    {
        sc=FAILURE;
    }
    flight* curr_ptr=*head;
    flight* prev_ptr=NULL;
    while(curr_ptr!=NULL&&strcmp(curr_ptr->departureTime,flptr->departureTime)<=0)
    {
        prev_ptr=curr_ptr;
        curr_ptr=curr_ptr->next;
    }
    flptr->prev=prev_ptr;
    flptr->next=curr_ptr;
    if(prev_ptr==NULL)
    {
        *head=flptr;
    }
    else
    {
        prev_ptr->next=flptr;
    }
    if(curr_ptr!=NULL)
    {
        curr_ptr->prev=flptr;
    }
    return sc;
}
status_code deleteFlight(flight**fhead,int flightId,passenger* phead)
{
    status_code sc=FAILURE;
    flight* fptr=searchById(*fhead,flightId);
    if(fptr!=NULL)
    {
        passenger* nptr=phead;
        int found=0;
        while(nptr!=NULL&&!found)
        {
            if(nptr->flightId==flightId)
            {
                found=1;
            }
            nptr=nptr->next;
        }
        if(!found)
        {
            if(fptr->prev!=NULL)
            {
                fptr->prev->next=fptr->next;
            }
            else
            {
                *fhead=fptr->next;
            }
            if(fptr->next!=NULL)
            {
                fptr->next->prev=fptr->prev;
            }
            free(fptr);
            sc=SUCCESS;
        }
    }
    return sc;
}