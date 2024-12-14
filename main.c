#include <stdlib.h>
#include <stdio.h>
#include "reservations.h"

int main()
{
    FILE *fptr;
    RoomReservation(fptr, "Reservation.txt", "a", 0, "Zeyad Hasan", "535585855", 23, 12, 2025, "Testmail@gmail.com", "01094933404","LakeView");
    return 0;
}