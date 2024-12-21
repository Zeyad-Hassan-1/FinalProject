// login.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./headerFiles/login.h"
#include "curses.h"


int check_info(char *username, char *password)
{
    FILE *f2;
    f2 = fopen("output/users.txt", "r");
    char line[max_linelength];
    char st_username[max_usernamelength];
    char st_password[max_passwordlength];
    if (f2 == NULL)
    {
        printf("file not found\n");
        return 0;
    }
    while (fgets(line, sizeof(line), f2))
    {
        sscanf(line, "%s %s", st_username, st_password);
        if (strcmp(username, st_username) == 0 && strcmp(password, st_password) == 0)
        {
            fclose(f2);
            return 1;
        }
    }
    fclose(f2);
    return 0;
}

int login()
{
    char username[20], password[20];
    while (1)
    {
        clear();
        printw("Enter your username: ");
        getstr(username);

        printw("Enter your password: ");
        getstr(password);
        refresh();

        if (check_info(username, password))
        {
            clear();
            printw("Login successful! Access granted.\n");
            refresh();
            return 1;
        }
        else
        {
            clear();
            printw("Invalid username or password. Please try again.\n");
            printw("Press any key to try again...");
            getch();
            refresh();
        }
    }
    return 0;
}