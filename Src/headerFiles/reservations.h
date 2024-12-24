#ifndef RESERVATIONS_H
#define RESERVATIONS_H

typedef struct {
    long reservationID;
    int room_id;
    char status[20]; 
    char name[20];
    int numberOfnights;
    int day, month, year;
    float checkindate;
    char email[20];
    char phone[20];
    char catogary[20];
    char nationalId[20];
} Customer;

typedef struct {
    int room_id;
    char status[20];
    char category[20];
    int price;
} Room;

int RoomReservation(int stat, long resID, char *nId);
int validateCheckIn();


#endif
