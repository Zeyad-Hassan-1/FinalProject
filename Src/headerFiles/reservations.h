#ifndef RESERVATIONS_H
#define RESERVATIONS_H

typedef struct {
    long reservationID;
    int room_id;
    char status[20]; 
    char name[20];
    int numberOfnights;
    int day, month, year;
    char email[20];
    char phone[20];
    char catogary[20];
    char nationalId[20];
} Customer;


void RoomReservation(int statue);
void check_in(int room_id);
int validateCheckIn();


#endif
