#ifndef TRACKING_H
#define TRACKING_H

// typedef struct
// {
//     int national_ID;
//     char email[100];
//     int mobile_number;
// } information;

// typedef struct
// {
//     int day;
//     int month;
//     int year;
// } date;

// typedef struct
// {
//     char name[100];
//     information Contact_information;
//     date Check_in_date;
//     int Number_of_nights;
//     char Room_Category[100];
//     char reservation_state[100];
//     int room_ID;
//     int reservation_ID;
// } customer_information;


typedef struct
{
    int national_ID;
    char email[100];
    int mobile_number;

} information;

typedef struct
{
    int day;
    int month;
    int year;

} date;

typedef struct
{
    char Room_Category[100];
    int room_ID;
    char room_state[100];
    int room_price;

} room;

typedef struct
{
    char name[100];
    information Contact_information;
    date Check_in_date;
    int Number_of_nights;
    char reservation_state[100];
    int reservation_ID;
    room room_information;

} customer_information;

void query();

void track();
// void find_by_name();

#endif