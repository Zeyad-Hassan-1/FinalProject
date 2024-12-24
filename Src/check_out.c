#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./headerFiles/reservations.h"
#include "./headerFiles/editReservations.h"
#include <curses.h>


void changereservation(int roomId)
{
    FILE *reservationFile=fopen("output/Reservations.txt","r");
    if (!reservationFile)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[200];
    Customer customers[200];
    int i = 0,deleted_line;
    while (fgets(line, 200, reservationFile ))
    {

        sscanf(line, "%ld,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &customers[i].reservationID, &customers[i].room_id, customers[i].status, customers[i].name, customers[i].nationalId, &customers[i].numberOfnights, &customers[i].day, &customers[i].month, &customers[i].year, customers[i].email, customers[i].phone);
        if (customers[i].room_id == roomId)
        {
            deleted_line=i;
        }
        i++;
    }
    fclose(reservationFile);
    reservationFile=fopen("output/Reservations.txt","w");
    int j = 0;
    while (j < i)
    {
        if (j != deleted_line)
        {
            fprintf(reservationFile, "%ld,%d,%s,%s,%s,%d,%02d-%02d-%02d,%s,%s\n", customers[j].reservationID, customers[j].room_id, customers[j].status, customers[j].name, customers[j].nationalId, customers[j].numberOfnights, customers[j].day, customers[j].month, customers[j].year, customers[j].email, customers[j].phone);
        }
        j++;
    }
    fclose(reservationFile);
}

void checkOut()
{
    FILE *reservationFile, *roomFile;
    int no_of_nights = 0, room_number, found = 0;
    int price;
    char line1[200];
    int total_bill;
    Customer customers;
    Room room;
    int reciept;
    printw("Enter the room number to check out: ");
    scanw("%d", &room_number);

    reservationFile = fopen("output/Reservations.txt", "r");

    if (reservationFile == NULL)
    {
        printw("Error opening file.\n");
        return;
    }

    while (fgets(line1, sizeof(line1), reservationFile))
    {
        sscanf(line1, "%ld,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &customers.reservationID, &customers.room_id, customers.status, customers.name, customers.nationalId, &customers.numberOfnights, &customers.day, &customers.month, &customers.year, customers.email, customers.phone);
        if (customers.room_id == room_number && strcmp(customers.status, "confirmed") == 0)
        {
            found = 1;
            no_of_nights = customers.numberOfnights;
            changeRoomStat(room_number);
            break;
        }
    }
    roomFile = fopen("output/Room.txt", "r");
    while (fgets(line1, sizeof(line1), roomFile) && no_of_nights > 0)
    {
        sscanf(line1, "%d %s %s %d", &room.room_id, room.status, room.category, &room.price);
        if (room.room_id == room_number)
        {
            price = room.price;

            break;
        }
    }

    fclose(reservationFile);
    fclose(roomFile);

    if (found)
    {
        printw("Check-out completed for room %d.\n", room_number);
        printw("no of nights is %d\n", no_of_nights);
        printw("price per night is %d\n", price);
        reciept = no_of_nights * price;
        printw("your reciept is %d", reciept);
        changereservation(room_number);
    }
    else
    {
        printw("No confirmed reservation found for room %d.\n", room_number);
    }
}
