#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "reservations.h"

long generateUniqueID()
{
    time_t now = time(NULL);
    return now % 100000000;
}

void RoomReservation(int statue, Customer customer_details)

{
    FILE *fptr = fopen("output/Reservations.txt", "a");
    FILE *roomFile = fopen("output/Room.txt", "r");
    if (roomFile == NULL)
    {
        printf("Error: Could not open file.\n");
    }

    char rooms[200];
    int found = 0;

    while (fgets(rooms, sizeof(rooms), roomFile) && !found)
    {
        int roomID, price;
        char status[20], category[20];

        // تحليل السطر
        sscanf(rooms, "%d %s %s %d", &roomID, status, category, &price);

        // التحقق من الحالة والفئة
        if (strcmp(status, "Available") == 0 && strcmp(category, customer_details.catogary) == 0)
        {
            customer_details.room_id = roomID;
            found = 1;
        }
    }

    fclose(roomFile);
    char *roomStatue;
    long reservationID = generateUniqueID();
    if (statue)
        roomStatue = "confirmed";
    else
        roomStatue = "unconfirmed";
    fprintf(fptr, "%d,%d,%s,%s,%02d-%02d-%02d,%s,%s,%s\n", reservationID, customer_details.room_id, roomStatue, customer_details.name, customer_details.day, customer_details.month, customer_details.year, customer_details.email, customer_details.nationalId, customer_details.phone);
    fclose(fptr);
}

void check_in(int room_id,int reservation_id)
{
    FILE *file = fopen("output/Room.txt", "r");
    FILE *tempFile = fopen("output/Temp.txt", "w");
    if (file == NULL || tempFile == NULL)
    {
        printf("Error: Could not open file.\n");
    }
    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        int roomID, price;
        char status[20], category[20];

        // قراءة السطر
        sscanf(line, "%d %s %s %d", &roomID, status, category, &price);

        if (roomID == room_id && strcmp(status, "Available") == 0)
        {
            strcpy(status, "Reserved");
        }

        fprintf(tempFile, "%d %s %s %d\n", roomID, status, category, price);
    }

    fclose(file);
    fclose(tempFile);

    remove("output/Room.txt");
    rename("output/Temp.txt", "output/Room.txt");
}