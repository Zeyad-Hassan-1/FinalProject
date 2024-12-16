#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "login.h"
#include "reservations.h"
#include "editReservations.h"
#include "menu.h"

int isLoggedIn = 0;

void mainMenu()
{
    const char *mainChoices[] = {
        "1. Login",
        "2. Quit"};
    int n_mainChoices = sizeof(mainChoices) / sizeof(mainChoices[0]);

    WINDOW *menu_win = newwin(10, 50, 5, 10);  // Create a window for the menu
    box(menu_win, 0, 0);  // Draw the border around the window
    refresh();
    wrefresh(menu_win);  // Refresh the menu window

    while (!isLoggedIn)
    {
        wclear(menu_win);  // Clear the window content
        box(menu_win, 0, 0);  // Draw the border again
        for (int i = 0; i < n_mainChoices; i++)
        {
            wattron(menu_win, COLOR_PAIR(i % 2 == 0 ? 1 : 2));
            mvwprintw(menu_win, 2 + i, 2, mainChoices[i]);  // Print options inside the window
            wattroff(menu_win, COLOR_PAIR(i % 2 == 0 ? 1 : 2));
        }
        wrefresh(menu_win);

        int choice = wgetch(menu_win);

        switch (choice)
        {
        case '1':
            clear();
            printw("Login...\n");
            refresh();
            {
                int loginSuccess = login();
                if (loginSuccess)
                {
                    isLoggedIn = 1;
                    attron(COLOR_PAIR(4));
                    printw("Login successful! Redirecting...\n");
                    attroff(COLOR_PAIR(4));
                    refresh();
                    getch();
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    printw("Login failed. Try again.\n");
                    attroff(COLOR_PAIR(3));
                    refresh();
                    getch();
                }
            }
            break;

        case '2': // Exit
            clear();
            printw("Exiting the program...");
            refresh();
            return;

        default:
            clear();
            attron(COLOR_PAIR(3));
            printw("Invalid choice! Please select a valid option.\n");
            attroff(COLOR_PAIR(3));
            refresh();
            getch();
            break;
        }
    }

    secondaryMenu();
}

void secondaryMenu()
{
    Customer cst;

    const char *choices[] = {
        "1. Room Reservation",
        "2. Check-In",
        "3. View Customer Details",
        "4. Quit"};
    int n_choices = sizeof(choices) / sizeof(choices[0]);

    WINDOW *menu_win = newwin(10, 50, 5, 10);  // Create a window for the secondary menu
    box(menu_win, 0, 0);  // Draw the border around the window
    refresh();
    wrefresh(menu_win);

    while (1)
    {
        wclear(menu_win);
        box(menu_win, 0, 0);  // Draw the border again
        for (int i = 0; i < n_choices; i++)
        {
            wattron(menu_win, COLOR_PAIR(i % 2 == 0 ? 1 : 2));
            mvwprintw(menu_win, 2 + i, 2, choices[i]);  // Print options inside the window
            wattroff(menu_win, COLOR_PAIR(i % 2 == 0 ? 1 : 2));
        }
        wrefresh(menu_win);

        int choice = wgetch(menu_win);

        switch (choice)
        {
        case '1':
            clear();
            printw("Starting room reservation...\n");
            refresh();
            {
                RoomReservation(0);
                attron(COLOR_PAIR(4));
                printw("Reservation saved!\n");
                attroff(COLOR_PAIR(4));
                refresh();
                attron(COLOR_PAIR(3));
                printw("Enter c to back to menu or any other key to Exit....");
                attroff(COLOR_PAIR(3));
                int choose = getch();
                switch (choose)
                {
                case 'c':
                    refresh();
                    break;

                default:
                    clear();
                    printw("Exiting the program...");
                    refresh();
                    return;
                    break;
                }
            }
            break;

        case '2':
            clear();
            printw("Check-In selected.\n");
            refresh();
            {
                int validate = validateCheckIn();
                if (validate != 0)
                {
                    check_in(validate);
                    attron(COLOR_PAIR(4));
                    printw("Your reservation was confirmed successfully.");
                    attroff(COLOR_PAIR(4));
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    printw("Reservation not found or invalid details.\n");
                    attroff(COLOR_PAIR(3));
                }
                refresh();
                attron(COLOR_PAIR(3));
                printw("\nEnter c to back to menu or any other key to Exit....\n");
                attroff(COLOR_PAIR(3));
                int choose = getch();
                switch (choose)
                {
                case 'c':
                    refresh();
                    break;

                default:
                    clear();
                    printw("Exiting the program...");
                    refresh();
                    return;
                    break;
                }
            }
            break;

        case '3':
            clear();
            printw("View Customer Details...\n");
            refresh();
            {
                ViewCustomerDetails();
                attron(COLOR_PAIR(3));
                printw("\nEnter c to back to menu or any other key to Exit....\n");
                attroff(COLOR_PAIR(3));
                int choose = getch();
                switch (choose)
                {
                case 'c':
                    refresh();
                    break;

                default:
                    clear();
                    printw("Exiting the program...");
                    refresh();
                    return;
                    break;
                }
            }
            break;

        case '4':
            clear();
            printw("\nExiting the program...\n");
            refresh();
            return;

        default:
            clear();
            attron(COLOR_PAIR(3));
            printw("Invalid choice! Please select a valid option.\n");
            attroff(COLOR_PAIR(3));
            refresh();
            getch();
            break;
        }
    }
}
