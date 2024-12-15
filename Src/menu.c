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

    while (!isLoggedIn)
    {
        clear();
        for (int i = 0; i < n_mainChoices; i++)
        {
            attron(COLOR_PAIR(i % 2 == 0 ? 1 : 2));
            mvprintw(5 + i, 10, mainChoices[i]);
            attroff(COLOR_PAIR(i % 2 == 0 ? 1 : 2));
        }
        refresh();

        int choice = getch();

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

        case '2': // الخروج
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

    // بعد تسجيل الدخول، انتقل للقائمة الثانوية
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

    while (1)
    {
        clear();
        for (int i = 0; i < n_choices; i++)
        {
            attron(COLOR_PAIR(i % 2 == 0 ? 1 : 2));
            mvprintw(5 + i, 10, choices[i]);
            attroff(COLOR_PAIR(i % 2 == 0 ? 1 : 2));
        }
        refresh();

        int choice = getch();

        switch (choice)
        {
        case '1': // حجز غرفة
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
                attron(COLOR_PAIR(4));
                printw("Reservation saved!\n");
                attroff(COLOR_PAIR(4));
                refresh();
                getch();
            }
            break;

        case '2': // تسجيل الوصول
            clear();
            printw("Check-In selected.\n");
            refresh();
            {
                long resID;
                int day, month, year;
                printw("Enter the reservation ID: ");
                scanw("%ld", &resID);
                printw("Enter the check-in date (day month year): ");
                scanw("%d %d %d", &day, &month, &year);
                int validate = validateCheckIn(resID, day, month, year);
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
                getch();
            }
            break;

        case '3': // عرض التفاصيل
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
                printw("Name : %s \n Phone Number: %s \n Email: %s \n National Id: %s \n Number of Nights: %d \n Check in date : %02d %02d %02d", csv.name, csv.phone, csv.email, csv.nationalId, csv.numberOfnights, csv.day, csv.month, csv.year);
                attroff(COLOR_PAIR(2));
                refresh();
                getch();
            }
            break;

        case '4': // الخروج
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
}
