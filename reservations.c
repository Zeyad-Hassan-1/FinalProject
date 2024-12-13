#include <stdlib.h>
#include <stdio.h>
#include "reservations.h"
#define FILENAME "reservation_ids.txt"

int readLastID() {
    FILE *file = fopen(FILENAME, "r");
    int id = 10000;

    if (file == NULL) {
        return 10000;
    }

    fscanf(file, "%d", &id);
    fclose(file);
    return id;
}

void updateLastID(int id) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error: Could not open file to write.\n");
        exit(1);
    }

    fprintf(file, "%d", id);
    fclose(file);
}

int generateNewReservationID() {
    int lastID = readLastID();
    int newID = lastID + 1;
    updateLastID(newID);
    return newID;
}

void RoomReservation(FILE *fptr,char *name, char *mode, int statue,char *customerName, char *nationalId, char *email, char *mobileNumber)
{
    fptr = fopen(name, mode);
    char *roomStatue;
    int reservationID = generateNewReservationID();
    if (statue)
        roomStatue = "confirmed";
    else
        roomStatue = "unconfirmed";
    fprintf(fptr,"%d,%s,%s,%s,%s,%s\n",reservationID,roomStatue,customerName,email,nationalId,mobileNumber);
    fclose(fptr);
}