#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include "Src/reservations.h"

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
        "3. Cancel Reservation"};
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
                printw("Enter category: ");
                //بيقولك عبد الله حط الcategories المتاحة واليوزر يختار منها
                getstr(cst.catogary);
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
                int roomId;
                printw("Are you sure to confirm your reservation ? press any key to continue ...");
                getch();
                scanw("%d",&roomId);
                check_in(roomId);
                printw("Your reservation was confirmed successfully");
                refresh();
                getch();
            }
            break;
        case '3':
            clear();
            printw("Cancel Reservation selected.\n");
            refresh();
            getch();
            break;
        default:
            clear();
            printw("Invalid choice! Please select a valid option.\n");
            refresh();
            getch();
            break;
        }
    }

    // إنهاء مكتبة curses
    endwin();

    return 0;
}
