#include <stdio.h>
#include <curses.h>
#include <ctype.h>
#include <string.h>

int is_valid_email(const char *email)
{
    const char *at = strchr(email, '@');
    if (!at || at == email)
        return 0;
    const char *dot = strchr(at, '.');
    if (!dot || dot == at + 1)
        return 0;
    if (dot[1] == '\0')
        return 0;

    return 1;
}

int is_valid_date(int day, int month, int year)
{
    if (month < 1 || month > 12)
        return 0;
    if (day < 1 || day > 31)
        return 0;

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
        {
            return 0;
        }
    }

    if (month == 2)
    {
        if (day > 28)
        {
            return 0;
        }
    }

    return 1;
}

int is_valid_phone(const char *phone)
{
    if (strlen(phone) != 11)
    {
        return 0;
    }

    for (int i = 0; i < 11; i++)
    {
        if (!isdigit(phone[i]))
        {
            return 0;
        }
    }

    return 1;
}

int is_valid_national_id(const char *national_id)
{
    for (int i = 0; i < strlen(national_id); i++)
    {
        if (!isdigit(national_id[i]))
        {
            return 0;
        }
    }

    return 1;
}