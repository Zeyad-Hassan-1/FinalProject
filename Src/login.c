// login.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h" // Include the header file
#include "curses.h"

// Function to check if the username and password match any entry in users.txt
int check(char *username, char *password)
{
    FILE *file = fopen("output/users.txt", "r");

    // If the file does not exist or cannot be opened
    if (file == NULL)
    {
        printf("Error: Unable to open 'users.txt' file.\n");
        return 0; // File not found or cannot be opened
    }

    char line[Max_Line];
    char file_username[20]; // Pointer to username
    char file_password[20]; // Pointer to password

    // Read each line from the file
    while (fgets(line, Max_Line, file) != NULL)
    {
        // Extract the username and password from the line
        sscanf(line,"%s %s",file_username,file_password);

        // Check if the entered username and password match
        if (file_username != NULL && file_password != NULL)
        {
            if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0)
            {
                fclose(file);
                return 1; // Match found
            }
        }
    }

    fclose(file);
    return 0; // No match found
}

// Function to handle the login process
int login()
{
    // Keep asking for credentials until valid ones are entered
    char username[20], password[20];
    while (1)
    {
        clear();
        printw("Enter your username: ");
        getstr(username);

        printw("Enter your password: ");
        getstr(password);
        refresh();

        // Check if credentials are valid
        if (check(username, password))
        {
            clear();
            printw("Login successful! Access granted.\n");
            refresh();
            return 1; // تسجيل الدخول ناجح
        }
        else
        {
            clear();
            printw("Invalid username or password. Please try again.\n");
            refresh();
        }
    }
    return 0; // احتياطي فقط، لن يتم الوصول هنا
}
