#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "./headerFiles/tracking.h"

void track()
{
    FILE *room;
    room = fopen("output/Room.txt", "r");
    char line[200];
    while (fgets(line, 200, room))
    {
        printw("%s", line);
        refresh();
    }

    fclose(room);
}

void find_by_name()
{

    FILE *f;
    customer_information customer;
    char line[1000];
    char name[100];
    refresh();
    printw("write customer name:");
    getstr(name);
    f = fopen("output/Reservations.txt", "r");
    if (f == NULL)
    {
        printw("error opening file:");
        exit(1);
    }
    int found = 1;
    while (found)
    {
        if (fgets(line, 1000, f) == NULL)
        {
            printw("customer not found");
            break;
        }
        sscanf(line, "%d,%d,%[^,],%[^,],%d,%d-%d-%d,%[^,],%d,%d", &customer.reservation_ID, &customer.room_ID, customer.reservation_state, customer.name, &customer.Number_of_nights, &customer.Check_in_date.day, &customer.Check_in_date.month, &customer.Check_in_date.year, customer.Contact_information.email, &customer.Contact_information.national_ID, &customer.Contact_information.mobile_number);
        if (strcmp(name, customer.name) == 0)
        {
            clear();
            int startx = (COLS - 40) / 2; // Center horizontally
            attron(COLOR_PAIR(4));
            mvprintw(1, startx, "Name: %s", customer.name);
            mvprintw(2, startx, "Reservation ID: %d", customer.reservation_ID);
            mvprintw(3, startx, "Room ID: %d", customer.room_ID);
            mvprintw(4, startx, "Reservation Status: %s", customer.reservation_state);
            mvprintw(5, startx, "Number of Nights: %d", customer.Number_of_nights);
            mvprintw(6, startx, "Check-in Date: %d-%d-%d", customer.Check_in_date.day, customer.Check_in_date.month, customer.Check_in_date.year);
            mvprintw(7, startx, "Email: %s", customer.Contact_information.email);
            mvprintw(8, startx, "National ID: %d", customer.Contact_information.national_ID);
            mvprintw(9, startx, "Mobile: %d", customer.Contact_information.mobile_number);
            refresh();
            attroff(COLOR_PAIR(4));
        }
    }

    fclose(f);
    return;
}