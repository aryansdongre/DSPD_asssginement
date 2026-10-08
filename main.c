#include "digiyatra.h"

flight *makeFlight(int id, const char *src, const char *dst,
                   const char *dep, const char *arr, int seats)
{
    flight *f = malloc(sizeof(flight));
    f->flightId = id;
    strcpy(f->source, src);
    strcpy(f->destination, dst);
    strcpy(f->departureTime, dep);
    strcpy(f->arrivalTime, arr);
    f->totalSeats = seats;
    f->prev = f->next = NULL;
    return f;
}

passenger *makePassenger(int id, const char *name, int age, char gender,
                         const char *contact, int flightId, ticketType type)
{
    passenger *p = malloc(sizeof(passenger));
    p->passengerId = id;
    strcpy(p->name, name);
    p->age = age;
    p->gender = gender;
    strcpy(p->contact, contact);
    p->flightId = flightId;
    p->ticketType = type;
    p->seatNumber = 0;
    p->prev = p->next = NULL;
    return p;
}

void tryAddFlight(flight **fhead, flight *f)
{
    if (addFlight(fhead, f) == SUCCESS)
        printf("Flight %d added\n", f->flightId);
    else
    {
        printf("Flight %d REJECTED\n", f->flightId);
        free(f);
    }
}

void tryAddPassenger(flight *fhead, passenger **phead, passenger *p)
{
    int id = p->passengerId;
    if (addPassenger(fhead, p, phead) == SUCCESS)
        printf("Passenger %d added\n", id);
    else
    {
        printf("Passenger %d REJECTED\n", id);
        free(p);
    }
}

void printPassengers(passenger *phead)
{
    printf("--- Passenger list ---\n");
    if (phead == NULL) printf("(empty)\n");
    for (passenger *p = phead; p != NULL; p = p->next)
        printf("ID %d | %s | Flight %d | Seat %d | Class %d\n",
               p->passengerId, p->name, p->flightId, p->seatNumber, p->ticketType);
}

int main(void)
{
    flight *fhead = NULL;
    passenger *phead = NULL;

    printf("\n=== 1. ADD FLIGHTS (unsorted input) ===\n");
    tryAddFlight(&fhead, makeFlight(101, "Mumbai", "Delhi", "09:30", "11:45", 3));
    tryAddFlight(&fhead, makeFlight(102, "Delhi",  "Mumbai", "06:15", "08:30", 2));
    tryAddFlight(&fhead, makeFlight(103, "Mumbai", "Goa",    "14:00", "15:10", 2));
    tryAddFlight(&fhead, makeFlight(104, "Pune",   "Delhi",  "07:45", "10:00", 5));
    tryAddFlight(&fhead, makeFlight(105, "Delhi",  "Pune",   "05:00", "07:00", 4)); // earliest: goes to the front
    tryAddFlight(&fhead, makeFlight(101, "Chennai","Kochi",  "10:00", "11:00", 2)); // duplicate ID -> rejected

    printf("\n=== 2. DISPLAY BY DEPARTURE TIME (expect 105,102,104,101,103) ===\n");
    displaySortedByDepartureTime(fhead);

    printf("\n=== 3. DISPLAY BY SOURCE ===\n");
    displaySortedBySource(fhead);

    printf("\n=== 4. DISPLAY BY DESTINATION ===\n");
    displaySortedByDestination(fhead);

    printf("\n=== 5. DISPLAY BY SOURCE THEN DEPARTURE TIME ===\n");
    displaySortedBySourceThenByDepartureTime(fhead);

    printf("\n=== 6. SEARCH ===\n");
    printf("By ID 103:\n");
    display(searchById(fhead, 103));
    printf("By ID 999 (invalid):\n");
    display(searchById(fhead, 999));
    printf("By source Mumbai (expect 101, 103):\n");
    if (searchBySource(fhead, "Mumbai") == FAILURE) printf("none\n");
    printf("By destination Delhi (expect 101, 104):\n");
    if (searchByDestination(fhead, "Delhi") == FAILURE) printf("none\n");
    printf("By destination Paris (expect none):\n");
    if (searchByDestination(fhead, "Paris") == FAILURE) printf("none\n");

    printf("\n=== 7. ADD PASSENGERS ===\n");
    tryAddPassenger(fhead, &phead, makePassenger(1, "Aryan", 20, 'M', "9876543210", 101, ECONOMY));
    tryAddPassenger(fhead, &phead, makePassenger(2, "Riya",  34, 'F', "9123456780", 101, BUSINESS));
    tryAddPassenger(fhead, &phead, makePassenger(3, "Kabir", 67, 'M', "9001122334", 101, FIRST_CLASS));
    tryAddPassenger(fhead, &phead, makePassenger(4, "Neha",  25, 'F', "9555500000", 101, ECONOMY));       // flight 101 full -> rejected
    tryAddPassenger(fhead, &phead, makePassenger(1, "Dup",   40, 'M', "9000000000", 102, ECONOMY));       // duplicate ID -> rejected
    tryAddPassenger(fhead, &phead, makePassenger(6, "Ghost", 30, 'M', "9000000001", 999, ECONOMY));       // invalid flight -> rejected
    tryAddPassenger(fhead, &phead, makePassenger(7, "Meera", 29, 'F', "9888877777", 102, ECONOMY));
    tryAddPassenger(fhead, &phead, makePassenger(8, "Omar",  52, 'M', "9444433333", 102, BUSINESS));

    flight *f103 = searchById(fhead, 103);
    f103->status = CANCELLED;
    tryAddPassenger(fhead, &phead, makePassenger(9, "Tara", 31, 'F', "9222211111", 103, ECONOMY));        // cancelled -> rejected

    printPassengers(phead);
    printf("Flight 101 available seats (expect 0):\n");
    display(searchById(fhead, 101));

    printf("\n=== 8. DELETE PASSENGERS ===\n");
    printf("Delete 2: %s\n", deletePassenger(&phead, 2, fhead) == SUCCESS ? "OK" : "FAILED");
    printf("Delete 555 (unknown): %s\n", deletePassenger(&phead, 555, fhead) == SUCCESS ? "OK" : "FAILED");
    printf("Flight 101 available seats (expect 1):\n");
    display(searchById(fhead, 101));

    printf("\n=== 9. ADD AGAIN: SHOULD REUSE SEAT 2 ===\n");
    tryAddPassenger(fhead, &phead, makePassenger(10, "Zoya", 22, 'F', "9777766666", 101, ECONOMY));
    printPassengers(phead);

    printf("\n=== 10. DELETE FLIGHTS ===\n");
    printf("Delete 101 (has passengers): %s\n", deleteFlight(&fhead, 101, phead) == SUCCESS ? "OK" : "FAILED");
    printf("Delete 999 (unknown): %s\n",        deleteFlight(&fhead, 999, phead) == SUCCESS ? "OK" : "FAILED");
    printf("Delete 104 (no passengers): %s\n",  deleteFlight(&fhead, 104, phead) == SUCCESS ? "OK" : "FAILED");
    printf("Delete 105 (head of list): %s\n",   deleteFlight(&fhead, 105, phead) == SUCCESS ? "OK" : "FAILED");
    displaySortedByDepartureTime(fhead);

    return 0;
}