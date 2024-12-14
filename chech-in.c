#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "checkIn.h"
typedef struct {
    int roomID;
    char status[20];     
    char category[20];  
    int price;         
} Room;
typedef struct {
    long reservationID;
    int roomID;        
    char status[20];     // Confirmed, Unconfirmed
    char customerName[50];
    char nationalID[20];
    int day, month, year;    // Check-in date
    char email[50];
    char mobileNumber[15];
} Reservation;

// Function to validate the reservation details during check-in
int validateCheckIn(long reservationID, const char *checkInDate){
    FILE* fptr=fopen("Reaervation.txt","r");
    if (fptr==NULL) {
        printf("Error: Could not open Reservation.txt\n");
        return 0;
    }
    Reservation reservation;
    int found = 0;
    while(fscanf(fptr, "%ld,%d,%[^,],%[^,],%02d-%02d-%02d,%s,%s,%s", 
            &reservation.reservationID, &reservation.roomID, reservation.status, reservation.customerName, 
            &reservation.day, &reservation.month, &reservation.year, reservation.email, reservation.nationalID, reservation.mobileNumber) == 10){
                if(reservation.reservationID==reservationID){
                    found = 1;
                    break;
                }
    }
    fclose(fptr);
    if (!found){
         printf("Error: Reservation ID not found.\n");
         return 0;
    }
    if (compareDates(checkInDate, reservation.day, reservation.month, reservation.year) > 0) {
        printf("Error: Check-in date is earlier than the reservation date.\n");
        return 0;
    }
    return 1;

}
/*
// Function to update reservation status in the "Reservation.txt" file
*/

// Function to update room status in the "Room.txt" file
int updateRoomStatus(int roomNumber){
    FILE* fptr=fopen("Room.txt","r+");
    if (!fptr) {
        printf("Error: Could not open Room.txt\n");
        return 0;
    }
    

}