#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "./headerFiles/login.h"
#include "./headerFiles/reservations.h"
#include "./headerFiles/editReservations.h"
#include "./headerFiles/menu.h"
#include "./headerFiles/tracking.h"

int isLoggedIn = 0;

void mainMenu()
{
    const char *mainChoices[] = {
        "Login",
        "Quit"};
    int n_mainChoices = sizeof(mainChoices) / sizeof(mainChoices[0]);

    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    int win_height = n_mainChoices + 4;
    int win_width = 30;
    int starty = (screen_height - win_height) / 2;
    int startx = (screen_width - win_width) / 2;

    WINDOW *menu_win = newwin(win_height, win_width, starty, startx);
    keypad(menu_win, TRUE);
    box(menu_win, 0, 0);
    refresh();
    wrefresh(menu_win);

    int highlight = 0;
    int choice = -1;

    while (!isLoggedIn)
    {
        wclear(menu_win);
        box(menu_win, 0, 0);

        for (int i = 0; i < n_mainChoices; i++)
        {
            if (i == highlight)
            {
                wattron(menu_win, COLOR_PAIR(9));
                mvwprintw(menu_win, 2 + i, 2, "%s", mainChoices[i]);
                wattroff(menu_win, COLOR_PAIR(9));
            }
            else
            {
                wattron(menu_win, COLOR_PAIR(i % 2 == 0 ? 1 : 2));
                mvwprintw(menu_win, 2 + i, 2, "%s", mainChoices[i]);
                wattroff(menu_win, COLOR_PAIR(i % 2 == 0 ? 1 : 2));
            }
        }
        wrefresh(menu_win);

        int key = wgetch(menu_win);
        switch (key)
        {
        case KEY_UP:
            highlight = (highlight - 1 + n_mainChoices) % n_mainChoices;
            break;

        case KEY_DOWN:
            highlight = (highlight + 1) % n_mainChoices;
            break;

        case '\n':
            choice = highlight + 1;
            break;

        default:
            break;
        }

        if (choice != -1)
        {
            clear();
            printw("You selected: %s\n", mainChoices[choice - 1]);
            refresh();

            switch (choice)
            {
            case 1:
                printw("Login...\n");
                {
                    int loginSuccess = login();
                    if (loginSuccess)
                    {
                        isLoggedIn = 1;
                        attron(COLOR_PAIR(4));
                        printw("Login successful! Redirecting...\n");
                        printw("Press any Key to continue...\n");
                        getch();
                        attroff(COLOR_PAIR(4));
                    }
                    else
                    {
                        attron(COLOR_PAIR(3));
                        printw("Login failed. Try again.\n");
                        attroff(COLOR_PAIR(3));
                    }
                }
                break;

            case 2:
                printw("Exiting the program...\n");
                refresh();
                return;

            default:
                printw("Invalid choice!\n");
                break;
            }

            choice = -1;
        }
    }

    secondaryMenu();
}

void secondaryMenu()
{
    Customer cst;

    const char *choices[] = {
        "Reserve a Room",
        "Check-In",
        "Cancel Reservation",
        "Check-Out",
        "Check Room Availability",
        "View Customer Details",
        "Edit Reservation Details",
        "Query(Search)",
        "Reservation Report",
        "Exit"};
    int n_choices = sizeof(choices) / sizeof(choices[0]);

    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    int win_height = n_choices + 4;
    int win_width = 50;
    int starty = (screen_height - win_height) / 2;
    int startx = (screen_width - win_width) / 2;

    WINDOW *menu_win = newwin(win_height, win_width, starty, startx);
    keypad(menu_win, TRUE);
    box(menu_win, 0, 0);
    refresh();
    wrefresh(menu_win);

    int highlight = 0;
    int choice = -1;

    while (1)
    {
        wclear(menu_win);
        box(menu_win, 0, 0);

        for (int i = 0; i < n_choices; i++)
        {
            if (i == highlight)
            {
                wattron(menu_win, COLOR_PAIR(4));
                mvwprintw(menu_win, 2 + i, 2, "%s", choices[i]);
                wattroff(menu_win, COLOR_PAIR(4));
            }
            else
            {
                wattron(menu_win, COLOR_PAIR(i % 2 == 0 ? 1 : 2));
                mvwprintw(menu_win, 2 + i, 2, "%s", choices[i]);
                wattroff(menu_win, COLOR_PAIR(i % 2 == 0 ? 1 : 2));
            }
        }
        wrefresh(menu_win);

        int key = wgetch(menu_win);
        switch (key)
        {
        case KEY_UP:
            highlight = (highlight - 1 + n_choices) % n_choices;
            break;

        case KEY_DOWN:
            highlight = (highlight + 1) % n_choices;
            break;

        case '\n':
            choice = highlight + 1;
            break;

        default:
            break;
        }

        if (choice != -1)
        {
            clear();
            printw("You selected: %s\n", choices[choice - 1]);
            refresh();

            switch (choice)
            {
            case 1:
                RoomReservation();
                attron(COLOR_PAIR(4));
                printw("Reservation saved!\n");
                attroff(COLOR_PAIR(4));
                break;

            case 2:
                printw("Check-In selected.\n");
                {
                    int validate = validateCheckIn();
                    if (validate != 0)
                    {
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
                }
                break;

            case 3:
                printw("Cancel Reservation Selected...\n");
                cancel();
                break;

            case 4:
                printw("Check-Out Selected...\n");
                break;

            case 5:
                printw("Check Room Availability Selected...\n");
                track();
                break;

            case 6:
                printw("View Customer Details...\n");
                ViewCustomerDetails();
                break;

            case 7:
                printw("Edit Reservation Selected...\n");
                break;

            case 8:
                printw("Query(Search) Selected...\n");
                query();
                break;

            case 9:
                printw("Reservation Report Selected...\n");
                break;

            case 10:
                printw("\nExiting the program...\n");
                refresh();
                return;

            default:
                printw("Invalid choice!\n");
                break;
            }

            int msg_y = (int)(screen_height * 0.8);
            int msg_x = (screen_width - strlen("Press 'c' to go back to the menu or any other key to exit...")) / 2;
            attron(COLOR_PAIR(3));
            mvprintw(msg_y, msg_x, "Press 'c' to go back to the menu or any other key to exit...");
            attroff(COLOR_PAIR(3));
            int ch = getch();
            clear();
            refresh();
            if (ch != 'c')
            {
                clear();
                printw("Exiting the program...\n");
                refresh();
                return;
            }

            choice = -1;
        }
    }
}
