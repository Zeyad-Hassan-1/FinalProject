#ifndef RESERVATIONS_H
#define RESERVATIONS_H

typedef struct {
    char name[20];
    char nationalId[20];
    char email[20];
    char phone[20];
    char catogary[20];
    int day, month, year;
} Customer;


void RoomReservation(int statue,Customer customer_details);


#endif
