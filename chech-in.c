#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "checkIn.h"
//#include "reservations.h"
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
int updateRoomStatus(int roomID){
    FILE* fptr=fopen("Room.txt","r+");
    if (!fptr) {
        printf("Error: Could not open Room.txt\n");
        return 0;
    }
     FILE *temp = fopen("TempRoom.txt", "w");
    if (!temp) {
        printf("Error: Could not create TempRoom.txt\n");
        fclose(fptr);
        return 0;
    }
    Room room;

    // تحديث حالة الغرفة إلى "Reserved"
    while (fscanf(fptr, "%d %s %s %d", &room.roomID, room.status, room.category, &room.price) == 4) {
        if (room.roomID == roomID) {
            fprintf(temp, "%d Reserved %s %d\n", room.roomID, room.category, room.price);
        } else {
            fprintf(temp, "%d %s %s %d\n", room.roomID, room.status, room.category, room.price);
        }
    }

    fclose(fptr);
    fclose(temp);

    // استبدال الملف الأصلي
    remove("Room.txt");
    rename("TempRoom.txt", "Room.txt");

    return 1;
}
// Helper function to compare dates
int compareDates(const Reservation *reservation, const char *checkInDate) {
    int resDay = reservation->day;
    int resMonth = reservation->month;
    int resYear = reservation->year;

    int checkDay, checkMonth, checkYear;
    sscanf(checkInDate, "%d-%d-%d", &checkDay, &checkMonth, &checkYear);

    if (resYear < checkYear) {
        return -1; // Reservation date is earlier
    } else if (resYear > checkYear) {
        return 1; // Check-in date is earlier
    }

    if (resMonth < checkMonth) {
        return -1; // Reservation date is earlier
    } else if (resMonth > checkMonth) {
        return 1; // Check-in date is earlier
    }

    if (resDay < checkDay) {
        return -1; // Reservation date is earlier
    } else if (resDay > checkDay) {
        return 1; // Check-in date is earlier
    }

    return 0; // Dates are equal
}
