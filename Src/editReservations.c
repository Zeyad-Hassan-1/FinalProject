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
        sscanf(line, "%ld,%d,%[^,],%[^,],%d,%d-%d-%d,%[^,],%[^,],%s", &csv.reservationID, &csv.room_id, csv.status, csv.name, &csv.numberOfnights, &csv.day, &csv.month, &csv.year, csv.email, csv.nationalId, csv.phone);
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

int Quit()
{
    return 0;
}