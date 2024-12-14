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
        return;
    }

    char rooms[200];
    int found = 0;

    while (fgets(rooms, sizeof(rooms), roomFile) && !found)
    {
        int roomID, price;
        char status[20], category[20];

        sscanf(rooms, "%d %s %s %d", &roomID, status, category, &price);

        if (strcmp(status, "Available") == 0 && strcmp(category, customer_details.catogary) == 0)
        {
            customer_details.room_id = roomID;
            found = 1;
        }
    }

    fclose(roomFile);

    if (!found)
    {
        printf("No available room found for the selected category.\n");
        return;
    }

    char *roomStatue = statue ? "confirmed" : "unconfirmed";
    long reservationID = generateUniqueID();
    fprintf(fptr, "%ld,%d,%s,%s,%d,%02d-%02d-%02d,%s,%s,%s\n", reservationID, customer_details.room_id, roomStatue, customer_details.name, customer_details.numberOfnights, customer_details.day, customer_details.month, customer_details.year, customer_details.email, customer_details.nationalId, customer_details.phone);
    fclose(fptr);
}

int validateCheckIn(long res_ID, int d, int m, int y)
{
    char line1[200];
    FILE *fptr1 = fopen("output/Reservations.txt", "r");
    FILE *tempFile = fopen("output/Tempr.txt", "w");
    if (fptr1 == NULL || tempFile == NULL)
    {
        printf("Error: Could not open Reservation.txt\n");
        fclose(fptr1);
        fclose(tempFile);
        return 0;
    }

    int room, found = 0;
    while (fgets(line1, sizeof(line1), fptr1))
    {
        long reservationID;
        char stat[20], name[50], email[50], nID[20], phone[20];
        int day, month, year, numofNights;

        sscanf(line1, "%ld,%d,%[^,],%[^,],%d,%d-%d-%d,%[^,],%[^,],%s", &reservationID, &room, stat, name, &numofNights, &day, &month, &year, email, nID, phone);

        if (res_ID == reservationID && d == day && m == month && y == year)
        {
            strcpy(stat, "confirmed");
            found = 1;
        }

        fprintf(tempFile, "%ld,%d,%s,%s,%d,%02d-%02d-%02d,%s,%s,%s\n", reservationID, room, stat, name, numofNights, day, month, year, email, nID, phone);
    }

    fclose(fptr1);
    fclose(tempFile);

    remove("output/Reservations.txt");
    rename("output/Tempr.txt", "output/Reservations.txt");

    return found ? room : 0;
}

void check_in(int room_id)
{
    FILE *file = fopen("output/Room.txt", "r");
    FILE *tempFile = fopen("output/Temp.txt", "w");
    if (file == NULL || tempFile == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }

    char line[200];

    while (fgets(line, sizeof(line), file))
    {
        int roomID, price;
        char status[20], category[20];

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