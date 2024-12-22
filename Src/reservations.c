#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include "./headerFiles/reservations.h"
#include "./headerFiles/validation.h"
#include "./headerFiles/editReservations.h"

long generateUniqueID()
{
    time_t now = time(NULL);
    return now % 100000000;
}
void RoomReservation()
{
    Customer cst;
    printw("Enter number of nights: ");
    scanw("%d", &cst.numberOfnights);
    attron(COLOR_PAIR(9));
    while (!is_valid_nights(cst.numberOfnights))
    {
        printw("Please Enter A valid number of nights from 1 to 30 ...\n");
        scanw("%d", &cst.numberOfnights);
    }
    attroff(COLOR_PAIR(9));
    printw("Enter day, month, year: ");
    scanw("%d %d %d", &cst.day, &cst.month, &cst.year);
    attron(COLOR_PAIR(9));
    while (!is_valid_date(cst.day, cst.month, cst.year))
    {
        printw("Please Enter A valid check-in date in form of dd mm yyyy\n");
        scanw("%d %d %d", &cst.day, &cst.month, &cst.year);
    }
    attroff(COLOR_PAIR(9));
    printw("Enter name: ");
    getstr(cst.name);
    printw("Enter national ID: ");
    getstr(cst.nationalId);
    attron(COLOR_PAIR(9));
    while (!is_valid_national_id(cst.nationalId))
    {
        printw("Please Enter A valid national ID....\n");
        getstr(cst.nationalId);
    }
    attroff(COLOR_PAIR(9));
    printw("Enter email: ");
    getstr(cst.email);
    attron(COLOR_PAIR(9));
    while (!is_valid_email(cst.email))
    {
        printw("Please Enter valid email ex:student@gmail.com\n");
        getstr(cst.email);
    }
    attroff(COLOR_PAIR(9));
    printw("Enter phone: ");
    getstr(cst.phone);
    attron(COLOR_PAIR(9));
    while (!is_valid_phone(cst.phone))
    {
        printw("Please enter valid phone number containing at least 5 digits...\n");
        getstr(cst.phone);
    }
    attroff(COLOR_PAIR(9));
    attron(COLOR_PAIR(3));
    printw("Select a category:");
    printw("1. SeaView\n2. GardenView\n3. LakeView\n");
    attroff(COLOR_PAIR(3));
    int categoryChoice;
    do
    {
        categoryChoice = getch() - '0';
        switch (categoryChoice)
        {
        case 1:
            strcpy(cst.catogary, "SeaView");
            break;
        case 2:
            strcpy(cst.catogary, "GardenView");
            break;
        case 3:
            strcpy(cst.catogary, "LakeView");
            break;
        default:
            attron(COLOR_PAIR(9));
            printw("Invalid choice! Please select a valid category.\n");
            attroff(COLOR_PAIR(9));
        }
    } while (categoryChoice < 1 || categoryChoice > 3);

    FILE *fptr = fopen("output/Reservations.txt", "a");
    FILE *roomFile = fopen("output/Room.txt", "r");
    if (roomFile == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }

    char rooms[200];
    int found = 0;

    while (fgets(rooms, sizeof(rooms), roomFile))
    {
        int roomID, price;
        char status[20], category[20];

        sscanf(rooms, "%d %s %s %d", &roomID, status, category, &price);

        if (strcmp(status, "Available") == 0 && strcmp(category, cst.catogary) == 0)
        {
            cst.room_id = roomID;
            found = 1;
            break;
        }
    }
    fclose(roomFile);

    while (!found)
    {
        attron(COLOR_PAIR(9));
        printw("\nNo available room found for the selected category.\n");
        printw("Press 'c' to cancel reservation or any other key to choose another category.\n");
        attroff(COLOR_PAIR(9));
        int choice = getch();
        if (choice == 'c' || choice == 'C')
        {
            printw("Reservation cancelled.\n");
            return;
        }
        else
        {
            attron(COLOR_PAIR(3));
            printw("Select a category:\n1. SeaView\n2. GardenView\n3. LakeView\n");
            attroff(COLOR_PAIR(3));
            categoryChoice = getch() - '0';

            switch (categoryChoice)
            {
            case 1:
                strcpy(cst.catogary, "SeaView");
                break;
            case 2:
                strcpy(cst.catogary, "GardenView");
                break;
            case 3:
                strcpy(cst.catogary, "LakeView");
                break;
            default:
                printw("Invalid choice! Defaulting to Standard.\n");
                strcpy(cst.catogary, "Standard");
                break;
            }

            roomFile = fopen("output/Room.txt", "r");
            if (roomFile == NULL)
            {
                printf("Error: Could not open file.\n");
                return;
            }

            while (fgets(rooms, sizeof(rooms), roomFile))
            {
                int roomID, price;
                char status[20], category[20];

                sscanf(rooms, "%d %s %s %d", &roomID, status, category, &price);

                if (strcmp(status, "Available") == 0 && strcmp(category, cst.catogary) == 0)
                {
                    cst.room_id = roomID;
                    found = 1;
                    break;
                }
            }
            fclose(roomFile);
        }
    }

    changeRoomStat(cst.room_id);

    char *roomStatue = "unconfirmed";
    long reservationID = generateUniqueID();
    fprintf(fptr, "%ld,%d,%s,%s,%s,%d,%02d-%02d-%02d,%s,%s\n", reservationID, cst.room_id, roomStatue, cst.name, cst.nationalId, cst.numberOfnights, cst.day, cst.month, cst.year, cst.email, cst.phone);
    fclose(fptr);
}

int validateCheckIn()
{
    long res_ID;
    int d, m, y;
    printw("Enter the reservation ID: ");
    scanw("%ld", &res_ID);
    printw("Enter the check-in date (day month year): ");
    scanw("%d %d %d", &d, &m, &y);
    char line1[200];
    FILE *fptr1 = fopen("output/Reservations.txt", "r");
    if (fptr1 == NULL)
    {
        printf("Error: Could not open Reservation.txt\n");
        return 0;
    }

    int room, found = 0, i = 0;
    Customer customers[200];
    while (fgets(line1, sizeof(line1), fptr1))
    {
        sscanf(line1, "%ld,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &customers[i].reservationID, &customers[i].room_id, customers[i].status, customers[i].name, customers[i].nationalId, &customers[i].numberOfnights, &customers[i].day, &customers[i].month, &customers[i].year, customers[i].email, customers[i].phone);

        if (res_ID == customers[i].reservationID && d == customers[i].day && m == customers[i].month && y == customers[i].year)
        {
            strcpy(customers[i].status, "confirmed");
            found = 1;
        }

        i++;
    }

    fclose(fptr1);

    fptr1 = fopen("output/Reservations.txt", "w");
    int j = 0;
    while (j < i)
    {
        fprintf(fptr1, "%ld,%d,%s,%s,%s,%d,%02d-%02d-%02d,%s,%s\n", customers[j].reservationID, customers[j].room_id, customers[j].status, customers[j].name, customers[j].nationalId, customers[j].numberOfnights, customers[j].day, customers[j].month, customers[j].year, customers[j].email, customers[j].phone);
        j++;
    }
    fclose(fptr1);

    if (found)
        return customers[0].room_id;
    return 0;
}
