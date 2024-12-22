#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./headerFiles/reservations.h"
#include "./headerFiles/editReservations.h"
#include <curses.h>

Customer ViewCustomerDetails()
{
    long id;
    attron(COLOR_PAIR(1));
    printw("Enter reservation id or room id to view your data..\n");
    attroff(COLOR_PAIR(1));
    scanw("%ld", &id);
    FILE *file = fopen("output/Reservations.txt", "r");
    char line[200];
    int found = 0;
    while (fgets(line, 200, file))
    {
        Customer csv;
        sscanf(line, "%ld,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &csv.reservationID, &csv.room_id, csv.status, csv.name, csv.nationalId, &csv.numberOfnights, &csv.day, &csv.month, &csv.year, csv.email, csv.phone);
        if (id == csv.reservationID || id == csv.room_id)
        {
            attron(COLOR_PAIR(2));
            printw("Name : %s \n Phone Number: %s \n Email: %s \n National Id: %s \n Number of Nights: %d \n Check in date : %02d %02d %02d\n\n", csv.name, csv.phone, csv.email, csv.nationalId, csv.numberOfnights, csv.day, csv.month, csv.year);
            attroff(COLOR_PAIR(2));
            refresh();
            fclose(file);
            return csv;
        }
    }
    fclose(file);
}

void cancel()
{
    long id;
    int room_id = 0, found = 0;
    FILE *res = fopen("output/Reservations.txt", "r");
    if (!res)
    {
        perror("Error opening Reservations.txt");
        exit(EXIT_FAILURE);
    }

    printw("Enter reservation_id or Room_id...\n");
    refresh();
    scanw("%ld", &id);

    char reservation[200];
    Customer customers[200];
    int i = 0, deletedLine;
    while (fgets(reservation, sizeof(reservation), res))
    {

        sscanf(reservation, "%ld,%d,%[^,],%s,%s,%d,%d-%d-%d,%s,%s", &customers[i].reservationID, &customers[i].room_id, customers[i].status, customers[i].name, customers[i].nationalId, &customers[i].numberOfnights, &customers[i].day, &customers[i].month, &customers[i].year, customers[i].email, customers[i].phone);

        if ((id == customers[i].reservationID || id == customers[i].room_id) && !strcmp(customers[i].status, "unconfirmed"))
        {
            found = 1;
            clear();
            printw("Reservation cancelled successfully\n");
            refresh();
            room_id = customers[i].room_id;
            deletedLine = i;
        }
    }

    fclose(res);

    res = fopen("output/Reservations.txt", "w");
    int j = 0;
    while (j < i)
    {
        if (j != deletedLine)
        {
            fprintf(res, "%ld,%d,%s,%s,%s,%d,%02d-%02d-%02d,%s,%s\n", customers[j].reservationID, customers[j].room_id, customers[j].status, customers[j].name, customers[j].nationalId, customers[j].numberOfnights, customers[j].day, customers[j].month, customers[j].year, customers[j].email, customers[j].phone);
            fclose(res);
        }
        j++;
    }

    if (room_id)
    {
        changeRoomStat(room_id);
    }
}

void changeRoomStat(int roomId)
{
    FILE *roomFile = fopen("output/Room.txt", "r");
    if (!roomFile)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[200];
    Room rooms[200];
    int i = 0;
    while (fgets(line, 200, roomFile))
    {

        sscanf(line, "%d %s %s %d", &rooms[i].room_id, rooms[i].status, rooms[i].category, &rooms[i].price);
        if (rooms[i].room_id == roomId)
        {
            if (!strcmp(rooms[i].status, "Reserved"))
                strcpy(rooms[i].status, "Available");
            else
                strcpy(rooms[i].status, "Reserved");
        }
        i++;
    }
    fclose(roomFile);
    roomFile = fopen("output/Room.txt", "w");
    if (!roomFile)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int j = 0;
    while (j < i)
    {
        fprintf(roomFile, "%d %s %s %d\n", rooms[j].room_id, rooms[j].status, rooms[j].category, rooms[j].price);
        j++;
    }
    fclose(roomFile);
}