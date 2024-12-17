#ifndef RESERVATIONS_H
#define RESERVATIONS_H

typedef struct {
    long reservationID;
    char name[20];
    char nationalId[20];
    char email[20];
    char status[20]; 
    char phone[20];
    char catogary[20];
    int day, month, year;
    int room_id;
    int numberOfnights;
} Customer;


void RoomReservation(int statue);
void check_in(int room_id);
int validateCheckIn();
void cancelReservation (long reservation_ID,int room_ID);

#endif
