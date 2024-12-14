#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include "Src/reservations.h"
#include "Src/editReservations.h"

int main()
{
    Customer cst;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
    }

    const char *choices[] = {
        "1. Room Reservation",
        "2. Check-In",
        "3. View Customer Details"};
    int n_choices = sizeof(choices) / sizeof(choices[0]);

    while (1)
    {
        clear();

        for (int i = 0; i < n_choices; i++)
        {
            attron(COLOR_PAIR(i + 1));
            mvprintw(5 + i, 10, choices[i]);
            attroff(COLOR_PAIR(i + 1));
        }

        refresh();

        int choice = getch();

        switch (choice)
        {
        case '1':
            clear();
            printw("Starting room reservation...\n");
            refresh();
            {
                printw("Enter number of nights: ");
                scanw("%d", &cst.numberOfnights);
                printw("Enter day, month, year: ");
                scanw("%d %d %d", &cst.day, &cst.month, &cst.year);
                printw("Enter name: ");
                getstr(cst.name);
                printw("Enter national ID: ");
                getstr(cst.nationalId);
                printw("Enter email: ");
                getstr(cst.email);
                printw("Enter phone: ");
                getstr(cst.phone);
                attron(COLOR_PAIR(3));
                printw("Select a category: \n1. SeaView\n2. GardenView\n3. LakeView\n");
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

                RoomReservation(0, cst);
                printw("Reservation saved!\n");
                refresh();
                getch();
            }
            break;
        case '2':
            clear();
            printw("Check-In selected.\n");
            refresh();
            {
                long resID;
                int day, month, year;
                printw("Are you sure to confirm your reservation? Press any key to continue...");
                getch();
                printw("Enter the reservation ID: ");
                scanw("%ld", &resID);
                printw("Enter the check-in date (day month year): ");
                scanw("%d %d %d", &day, &month, &year);
                int validate = validateCheckIn(resID, day, month, year);
                if (validate != 0)
                {
                    check_in(validate);
                    printw("Your reservation was confirmed successfully.");
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    printw("Reservation not found or invalid details.\n");
                    attroff(COLOR_PAIR(3));
                }
                refresh();
                getch();
            }
            break;
        case '3':
            clear();
            printw("View Customer Details...\n");
            refresh();
            {
                long id;
                attron(COLOR_PAIR(1));
                printw("Enter reservation id or room id to view your data..\n");
                attroff(COLOR_PAIR(1));
                scanw("%ld", &id);
                Customer csv = ViewCustomerDetails(id);
                attron(COLOR_PAIR(2));
                printw("Name : %s \n Phone Number: %s \n Email: %s \n National Id: %s \n Number of Nights: %d \n Check in date : %02d %02d %02d", csv.name, csv.phone, csv.email, csv.nationalId, csv.numberOfnights,csv.day, csv.month, csv.year);
                attroff(COLOR_PAIR(2));
                refresh();
                getch();
            }
            break;
        default:
            clear();
            printw("Invalid choice! Please select a valid option.\n");
            refresh();
            getch();
            break;
        }
    }

    endwin();

    return 0;
}