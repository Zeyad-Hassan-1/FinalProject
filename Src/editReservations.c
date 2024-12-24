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

void cancel(long id, int edit)
{
    int room_id = 0, found = 0;
    int deletedLine;
    FILE *res = fopen("output/Reservations.txt", "r");
    if (!res)
    {
        perror("Error opening Reservations.txt");
        exit(EXIT_FAILURE);
    }

    char reservation[200];
    Customer customers[200];
    int i = 0;
    while (fgets(reservation, sizeof(reservation), res))
    {

        sscanf(reservation, "%ld,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &customers[i].reservationID, &customers[i].room_id, customers[i].status, customers[i].name, customers[i].nationalId, &customers[i].numberOfnights, &customers[i].day, &customers[i].month, &customers[i].year, customers[i].email, customers[i].phone);

        if ((id == customers[i].reservationID || id == customers[i].room_id))
        {
            if (!strcmp(customers[i].status, "unconfirmed") || edit == 1)
            {
                found = 1;
                clear();
                if (!edit)
                {
                    printw("Reservation cancelled successfully\n");
                    refresh();
                }
                room_id = customers[i].room_id;
                deletedLine = i;
            }
        }
        i++;
    }

    fclose(res);

    res = fopen("output/Reservations.txt", "w");
    int j = 0;
    while (j < i)
    {
        if (j != deletedLine)
        {
            fprintf(res, "%ld,%d,%s,%s,%s,%d,%02d-%02d-%02d,%s,%s\n", customers[j].reservationID, customers[j].room_id, customers[j].status, customers[j].name, customers[j].nationalId, customers[j].numberOfnights, customers[j].day, customers[j].month, customers[j].year, customers[j].email, customers[j].phone);
        }
        j++;
    }

    fclose(res);
    if (room_id)
    {
        changeRoomStat(room_id);
    }
}

int changeRoomStat(int roomId)
{
    FILE *roomFile = fopen("output/Room.txt", "r");
    if (!roomFile)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[200];
    Room rooms[200];
    int i = 0, found = 0;
    while (fgets(line, 200, roomFile))
    {

        sscanf(line, "%d %s %s %d", &rooms[i].room_id, rooms[i].status, rooms[i].category, &rooms[i].price);
        if (rooms[i].room_id == roomId)
        {
            found = 1;
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
    if (!found)
    {
        attron(COLOR_PAIR(9));
        printw("Error room not found..\n");
        attroff(COLOR_PAIR(9));
    }

    int j = 0;
    while (j < i)
    {
        fprintf(roomFile, "%d %s %s %d\n", rooms[j].room_id, rooms[j].status, rooms[j].category, rooms[j].price);
        j++;
    }
    fclose(roomFile);
    return found;
}

int save()
{
    printw("Do you want to save the edits? press c to cancel or any key to save.....\n");
    int choose = getch();
    switch (choose)
    {
    case 'c':
        return 0;
        break;

    default:
        return 1;
        break;
    }
}

void edit()
{
    long id;
    FILE *res = fopen("output/Reservations.c", "r");
    printw("Please enter reservation id or room id...\n");
    scanw("%ld", &id);
    char line[200];
    Customer cust;
    int stat;
    while (fgets(line, 200, res))
    {
        sscanf(line, "%ld,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &cust.reservationID, &cust.room_id, cust.status, cust.name, cust.nationalId, &cust.numberOfnights, &cust.day, &cust.month, &cust.year, cust.email, cust.phone);
        if (id == cust.reservationID || id == cust.room_id)
        {
            changeRoomStat(id);
            if (!strcmp(cust.status, "confirmed"))
                stat = 1;
            else
                stat = 0;
        }
    }
    fclose(res);
    printw("Please re enter the new data....\n");
    int newId = RoomReservation(stat);
    if (!save())
    {
        cancel(newId, 1);
        attron(COLOR_PAIR(9));
        printw("Edits not saved\n");
        refresh();
        attroff(COLOR_PAIR(9));
    }
    else
        cancel(id, 1);
}