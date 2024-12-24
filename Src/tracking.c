#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "./headerFiles/tracking.h"

void track()
{
    initscr(); // Initialize the curses mode
    FILE *room;
    room = fopen("output/Room.txt", "r");
    if (room == NULL)
    {
        printw("error opening file\n\n");
        exit(1);
    }

    clear();
    refresh(); // Refresh the main screen

    int width = COLS - 4;
    int height = LINES - 4;
    int startx = 2;
    int starty = 2;

    // Draw border using box
    WINDOW *win = newwin(height, width, starty, startx);
    box(win, 0, 0);

    char line[200];
    int y = 1;
    while (fgets(line, 200, room))
    {
        int len = strlen(line);
        int x = (width - len) / 2;   // Center horizontally
        wattron(win, COLOR_PAIR(2)); // Change color
        mvwprintw(win, y++, x, "%s", line);
        wattroff(win, COLOR_PAIR(2)); // Turn off color
    }

    wrefresh(win);
    fclose(room);
    delwin(win);
    endwin(); // End curses mode
}

void find_by_name(char *name)
{
    initscr(); // Initialize the curses mode
    customer_information customer;

    FILE *f;
    f = fopen("output/Reservations.txt", "r");
    if (f == NULL)
    {
        printw("error opening file\n\n");
        exit(1);
    }
    clear();
    refresh(); // Refresh the main screen
    int width = COLS - 4;
    int height = LINES - 4;
    int startx = 2;
    int starty = 2;

    // Draw border using box
    WINDOW *win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    mvwprintw(win, 0, (width - strlen("Customer Information")) / 2, "Customer Information");
    char line[1000];
    while (1)
    {
        if (fgets(line, 1000, f) == NULL)
        {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, height / 2, (width - strlen("customer not found")) / 2, "customer not found");
            wattroff(win, COLOR_PAIR(2));
            break;
        }

        sscanf(line, "%ld,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &customer.reservation_ID, &customer.room_information.room_ID, customer.reservation_state, customer.name, &customer.Contact_information.national_ID, &customer.Number_of_nights, &customer.Check_in_date.day, &customer.Check_in_date.month, &customer.Check_in_date.year, customer.Contact_information.email, &customer.Contact_information.mobile_number);

        if (strcmp(name, customer.name) == 0)
        {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 2, (width - strlen(customer.name) - 7) / 2, "Name: %s", customer.name);
            mvwprintw(win, 3, (width - 15) / 2, "Reservation ID: %d", customer.reservation_ID);
            mvwprintw(win, 4, (width - 9) / 2, "Room ID: %d", customer.room_information.room_ID);
            mvwprintw(win, 5, (width - strlen(customer.reservation_state) - 20) / 2, "Reservation Status: %s", customer.reservation_state);
            mvwprintw(win, 6, (width - 18) / 2, "Number of Nights: %d", customer.Number_of_nights);
            mvwprintw(win, 7, (width - 20) / 2, "Check-in Date: %d-%d-%d", customer.Check_in_date.day, customer.Check_in_date.month, customer.Check_in_date.year);
            mvwprintw(win, 8, (width - strlen(customer.Contact_information.email) - 8) / 2, "Email: %s", customer.Contact_information.email);
            mvwprintw(win, 9, (width - 13) / 2, "National ID: %s", customer.Contact_information.national_ID);
            mvwprintw(win, 10, (width - 8) / 2, "Mobile: %s", customer.Contact_information.mobile_number);
            wattroff(win, COLOR_PAIR(2));
            break;
        }
    }
    wrefresh(win);
    fclose(f);
    delwin(win);
    endwin(); // End curses mode
}

int find_by_roomID(int rid)
{
    initscr(); // Initialize the curses mode
    customer_information room;

    FILE *f;
    f = fopen("output/Room.txt", "r");
    if (f == NULL)
    {
        printw("error opening file:");
        exit(1);
    }

    clear();
    refresh(); // Refresh the main screen
    int width = COLS - 4;
    int height = LINES - 4;
    int startx = 2;
    int starty = 2;

    // Draw border using box
    WINDOW *win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    mvwprintw(win, 0, (width - strlen("Room Information")) / 2, "Room Information");

    char line[1000];
    while (1)
    {
        if (fgets(line, 1000, f) == NULL)
        {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, height / 2, (width - strlen("this room not found")) / 2, "this room not found");
            wattroff(win, COLOR_PAIR(2));
            break;
        }

        sscanf(line, "%d %s %s %d", &room.room_information.room_ID, room.room_information.room_state, room.room_information.Room_Category, &room.room_information.room_price);

        if (rid == room.room_information.room_ID)
        {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 2, (width - strlen("Room ID:") - 5) / 2, "Room ID: %d", room.room_information.room_ID);
            mvwprintw(win, 3, (width - strlen("Room State:") - 9) / 2, "Room State: %s", room.room_information.room_state);
            mvwprintw(win, 4, (width - strlen("Room Category:") - 13) / 2, "Room Category: %s", room.room_information.Room_Category);
            mvwprintw(win, 5, (width - strlen("Room Price:") - 11) / 2, "Room Price: %d", room.room_information.room_price);
            wattroff(win, COLOR_PAIR(2));

            if (strcmp(room.room_information.room_state, "Reserved") == 0)
            {
                customer_information customer;

                FILE *fc;
                fc = fopen("output/Reservations.txt", "r");
                if (fc == NULL)
                {
                    printw("error opening file:");
                    exit(1);
                }

                char linec[1000];
                while (1)
                {
                    if (fgets(linec, 1000, fc) == NULL)
                    {
                        break;
                    }
                    sscanf(linec, "%ld,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &customer.reservation_ID, &customer.room_information.room_ID, customer.reservation_state, customer.name, &customer.Contact_information.national_ID, &customer.Number_of_nights, &customer.Check_in_date.day, &customer.Check_in_date.month, &customer.Check_in_date.year, customer.Contact_information.email, &customer.Contact_information.mobile_number);

                    if (rid == customer.room_information.room_ID)
                    {
                        wattron(win, COLOR_PAIR(2));
                        mvwprintw(win, 7, (width - strlen("Guest Name:") - 11) / 2, "Guest Name: %s", customer.name);
                        mvwprintw(win, 8, (width - strlen("Reservation ID:") - 15) / 2, "Reservation ID: %d", customer.reservation_ID);
                        mvwprintw(win, 9, (width - strlen("Reservation Status:") - 19) / 2, "Reservation Status: %s", customer.reservation_state);
                        mvwprintw(win, 10, (width - strlen("Number of Nights:") - 17) / 2, "Number of Nights: %d", customer.Number_of_nights);
                        mvwprintw(win, 11, (width - strlen("Check-in Date:") - 15) / 2, "Check-in Date: %d-%d-%d", customer.Check_in_date.day, customer.Check_in_date.month, customer.Check_in_date.year);
                        mvwprintw(win, 12, (width - strlen("Email:") - 7) / 2, "Email: %s", customer.Contact_information.email);
                        mvwprintw(win, 13, (width - strlen("National ID:") - 13) / 2, "National ID: %s", customer.Contact_information.national_ID);
                        mvwprintw(win, 14, (width - strlen("Mobile:") - 7) / 2, "Mobile: %s", customer.Contact_information.mobile_number);
                        wattroff(win, COLOR_PAIR(2));
                        break;
                    }
                }
                fclose(fc);
            }
            break;
        }
    }
    wrefresh(win);
    fclose(f);
    delwin(win);
    endwin(); // End curses mode
    return 0;
}

void statues_room(char *state)
{
    initscr(); // Initialize the curses mode
    customer_information room;

    FILE *f;
    f = fopen("output/Room.txt", "r");
    if (f == NULL)
    {
        printw("error opening file\n\n");
        exit(1);
    }

    clear();
    refresh(); // Refresh the main screen
    int width = COLS - 4;
    int height = LINES - 4;
    int startx = 2;
    int starty = 2;

    // Draw border using box
    WINDOW *win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    mvwprintw(win, 0, (width - strlen("Room Status")) / 2, "Room Status");

    char line[1000];
    int y = 2;
    while (1)
    {
        if (fgets(line, 1000, f) == NULL)
        {
            break;
        }

        sscanf(line, "%d %s %s %d", &room.room_information.room_ID, room.room_information.room_state, room.room_information.Room_Category, &room.room_information.room_price);

        if (strcmp(state, room.room_information.room_state) == 0)
        {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, y++, (width - strlen("Room ID:") - 5) / 2, "Room ID: %d", room.room_information.room_ID);
            mvwprintw(win, y++, (width - strlen("Room Category:") - 13) / 2, "Room Category: %s", room.room_information.Room_Category);
            mvwprintw(win, y++, (width - strlen("Room Price:") - 11) / 2, "Room Price: %d", room.room_information.room_price);
            wattroff(win, COLOR_PAIR(2));
        }
    }
    wrefresh(win);
    fclose(f);
    delwin(win);
    endwin(); // End curses mode
}

void query()
{
    clear();
    refresh(); // Refresh the main screen

    int startx = (COLS - 70) / 2; // Center horizontally
    int starty = 2;               // Start a few lines down from the top

    WINDOW *win = newwin(20, 70, starty, startx);
    box(win, 0, 0);
    mvwprintw(win, 1, (70 - strlen("Look Up Information")) / 2, "Look Up Information");

    attron(COLOR_PAIR(2));
    mvwprintw(win, 3, 2, "1. Inquire about guest information by customer name");
    mvwprintw(win, 5, 2, "2. Inquire about room and guest information by room number");
    mvwprintw(win, 7, 2, "3. Inquire about available and reserved rooms by room state");
    mvwprintw(win, 9, 2, "What do you want: ");
    attroff(COLOR_PAIR(2));

    wrefresh(win);

    int i = wgetch(win) - '0';

    if (i == 1)
    {
        char name[100];
        mvwprintw(win, 11, 2, "Enter the customer name: ");
        wrefresh(win);
        wgetstr(win, name);
        clear();
        find_by_name(name);
    }
    else if (i == 2)
    {
        int rid;
        mvwprintw(win, 11, 2, "Enter the room number: ");
        wrefresh(win);
        wscanw(win, "%d", &rid);
        clear();
        find_by_roomID(rid);
    }
    else if (i == 3)
    {
        char state[100];
        mvwprintw(win, 11, 2, "Enter 'a' for available rooms or 'r' for reserved rooms: ");
        wrefresh(win);
        int choose = wgetch(win);
        clear();
        if (choose == 'a')
        {
            statues_room("Available");
        }
        else if (choose == 'r')
        {
            statues_room("Reserved");
        }
        else
        {
            mvprintw(starty + 14, startx, "This option not found\n\n");
        }
    }
    else
    {
        mvprintw(starty + 12, startx, "This option not found\n\n");
    }

    refresh();
    delwin(win);
    endwin(); // End curses mode
}

void check_the_date()
{
    initscr();
    customer_information customer;

    FILE *f;
    f = fopen("output/Reservations.txt", "r");
    if (f == NULL)
    {
        printf("error opening file\n\n");
        exit(1);
    }
    int day, month, year;
    // Refresh the main screen
    int width = COLS - 4;
    int height = LINES - 4;
    int startx = 2;
    int starty = 2;

    // Draw border using box
    WINDOW *win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    clear();
    refresh();
    mvwprintw(win, 0, (width - 41) / 2, "check the date for registration customer");
    mvwprintw(win, 3, 2, "day: ");
    wscanw(win, "%d", &day);
    mvwprintw(win, 4, 2, "month: ");
    wscanw(win, "%d", &month);
    mvwprintw(win, 5, 2, "year: ");
    wscanw(win, "%d", &year);
    wrefresh(win);
    char line[1000];
    wclear(win);
    box(win, 0, 0);
    wrefresh(win);
    int found = 0;
    int col = 1;
    while (fgets(line, 1000, f))
    {
        sscanf(line, "%ld,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &customer.reservation_ID, &customer.room_information.room_ID, customer.reservation_state, customer.name, customer.Contact_information.national_ID, &customer.Number_of_nights, &customer.Check_in_date.day, &customer.Check_in_date.month, &customer.Check_in_date.year, customer.Contact_information.email, customer.Contact_information.mobile_number);

        if (customer.Check_in_date.day == day && customer.Check_in_date.month == month && customer.Check_in_date.year == year)
        {
            found = 1;
            wattron(win, COLOR_PAIR(4));
            mvwprintw(win, col++, (width - 6 - strlen(customer.name)) / 2, "Name: %s", customer.name);
            mvwprintw(win, col++, (width - 24) / 2, "Reservation ID: %ld", customer.reservation_ID);
            mvwprintw(win, col++, (width - 13) / 2, "Room ID: %d", customer.room_information.room_ID);
            mvwprintw(win, col++, (width - 20 - strlen(customer.reservation_state)) / 2, "Reservation Status: %s", customer.reservation_state);
            mvwprintw(win, col++, (width - 20) / 2, "Number of Nights: %d", customer.Number_of_nights);
            mvwprintw(win, col++, (width - 24) / 2, "Check-in Date: %d-%d-%d", customer.Check_in_date.day, customer.Check_in_date.month, customer.Check_in_date.year);
            mvwprintw(win, col++, (width - 7 - strlen(customer.Contact_information.email)) / 2, "Email: %s", customer.Contact_information.email);
            mvwprintw(win, col++, (width - 13 - strlen(customer.Contact_information.national_ID)) / 2, "National ID: %s", customer.Contact_information.national_ID);
            mvwprintw(win, col++, (width - 8 - strlen(customer.Contact_information.mobile_number)) / 2, "Mobile: %s", customer.Contact_information.mobile_number);
            wattroff(win, COLOR_PAIR(4));
            wattron(win, COLOR_PAIR(2));
            for (int i = 1; i < width-1; i++)
            {
                mvwprintw(win, col, i, "-");
            }
            col++;
            
            wattroff(win, COLOR_PAIR(2));
            wrefresh(win);
        }
    }
    if(!found)
    {
        wattron(win, COLOR_PAIR(9));
        mvwprintw(win, 1, (width - 6 - strlen("Not Found")) / 2, "Not Found");
        wrefresh(win);
        wattroff(win, COLOR_PAIR(9));
    }
    fclose(f);

    refresh();
    delwin(win);
    endwin();
}