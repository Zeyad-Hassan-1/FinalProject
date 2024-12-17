// login.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./headerFiles/login.h"
#include "curses.h"

int check(char *username, char *password)
{
    FILE *file = fopen("output/users.txt", "r");

    if (file == NULL)
    {
        printf("Error: Unable to open 'users.txt' file.\n");
        return 0;
    }

    char line[Max_Line];
    char file_username[20];
    char file_password[20];

    while (fgets(line, Max_Line, file) != NULL)
    {
        sscanf(line, "%s %s", file_username, file_password);

        if (file_username != NULL && file_password != NULL)
        {
            if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0)
            {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
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

        if (check(username, password))
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
            refresh();
        }
    }
    return 0;
}
