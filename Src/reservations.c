#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "reservations.h"
#include <curses.h>
#include "validation.h"

long generateUniqueID()
{
    time_t now = time(NULL);
    return now % 100000000;
}

void RoomReservation(int statue)
{
    Customer cst;
    printw("Enter number of nights: ");
    scanw("%d", &cst.numberOfnights);
    printw("Enter day, month, year: ");
    scanw("%d %d %d", &cst.day, &cst.month, &cst.year);
    while (!is_valid_date(cst.day, cst.month, cst.year))
    {
        attron(COLOR_PAIR(1));
        printw("Please Enter A vaild check in date in form of dd mm yyyy\n");
        attroff(COLOR_PAIR(1));
        scanw("%d %d %d", &cst.day, &cst.month, &cst.year);
    }
    printw("Enter name: ");
    getstr(cst.name);
    printw("Enter national ID: ");
    getstr(cst.nationalId);
    while (!is_valid_national_id(cst.nationalId))
    {
        attron(COLOR_PAIR(1));
        printw("Please Enter A vaild national id....\n");
        attroff(COLOR_PAIR(1));
        getstr(cst.nationalId);
    }
    printw("Enter email: ");
    getstr(cst.email);
    while (!is_valid_email(cst.email))
    {
        attron(COLOR_PAIR(1));
        printw("Please Enter valid email ex:student@gmail.com");
        attroff(COLOR_PAIR(1));
        getstr(cst.email);
    }
    printw("Enter phone: ");
    getstr(cst.phone);
    while (!is_valid_phone(cst.phone))
    {
        attron(COLOR_PAIR(1));
        printw("Please enter valid phone number containing 11 digit...\n");
        attroff(COLOR_PAIR(1));
        getstr(cst.phone);
    }
    
    attron(COLOR_PAIR(3));
    printw("Select a category:");
    printw("1. SeaView\n2. GardenView\n3. LakeView\n");
    attroff(COLOR_PAIR(3));
    int categoryChoice;
    scanw("%d", &categoryChoice);

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

        if (strcmp(status, "Available") == 0 && strcmp(category, cst.catogary) == 0)
        {
            cst.room_id = roomID;
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
    fprintf(fptr, "%ld,%d,%s,%s,%d,%02d-%02d-%02d,%s,%s,%s\n", reservationID, cst.room_id, roomStatue, cst.name, cst.numberOfnights, cst.day, cst.month, cst.year, cst.email, cst.nationalId, cst.phone);
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
void cancelReservation(long reservation_ID, int room_ID)
{
    char line2[200], line3[200];
    FILE *fptr2 = fopen("output/reservation.txt", "r");
    FILE *tempFile2 = fopen("output/tempr.txt", "w");
    if (fptr2 == NULL || tempFile2 == NULL)
    {
        printf("Error: Could not open file to cancel reservation.\n");
        fclose(fptr2);
        fclose(tempFile2);
        return;
    }
    FILE *fptr3 = fopen("output/Room.txt", "r");
    FILE *tempFile3 = fopen("output/Temp.txt", "w");
    if (fptr3 == NULL || tempFile3 == NULL)
    {
        printf("Error: Could not open room file.\n");
        return;
    }

    while (fgets(line3, sizeof(line3), fptr3))
    {
        int roomID, price;
        char status[20], category[20];

        sscanf(line3, "%d %s %s %d", &roomID, status, category, &price);
        if (roomID == room_ID)
        {
            fprintf(tempFile3, "%d Available %s %d\n", roomID, category, price);
        }
        else
        {
            fprintf(tempFile3, "%d %s %s %d\n", roomID, status, category, price);
        }
    }
    fclose(fptr3);
    fclose(tempFile3);

    remove("output/Room.txt");
    rename("output/Temp.txt", "output/Room.txt");

    int room, found = 0;
    while (fgets(line2, sizeof(line2), fptr2))
    {
        long reservationID;
        char stat[20], name[50], email[50], nID[20], phone[20];
        int day, month, year, numofNights;

        sscanf(line2, "%ld,%d,%[^,],%[^,],%d,%d-%d-%d,%[^,],%[^,],%s", &reservationID, &room, stat, name, &numofNights, &day, &month, &year, email, nID, phone);

        if (reservation_ID == reservationID || room_ID == room)
        {
            if (strcmp(stat, "confirmed") == 0)
            {
                printf("Error: Cannot cancel a confirmed reservation.\n");
                fclose(fptr2);
                fclose(tempFile2);
                remove("output/tempr.txt");
                return;
            }
            found = 1;
            continue; // Skip writing this reservation to delete it
        }

        fprintf(tempFile2, "%ld,%d,%s,%s,%d,%02d-%02d-%02d,%s,%s,%s\n", reservationID, room, stat, name, numofNights, day, month, year, email, nID, phone);
    }
    fclose(fptr2);
    fclose(tempFile2);

    if (!found)
    {
        printf("Error: Reservation ID or Room ID not found.\n");
        remove("output/tempr.txt");
        return;
    }
    remove("output/Reservations.txt");
    rename("output/Tempr.txt", "output/Reservations.txt");
    printf("Reservation successfully canceled.");
}