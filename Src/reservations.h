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


void RoomReservation(int statue,Customer customer_details);
void check_in(int room_id);
int validateCheckIn(long res_ID, int d, int m, int y);

#endif
