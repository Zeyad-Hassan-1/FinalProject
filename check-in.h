#ifndef CHECKIN_H
#define CHECKIN_H

// Function to validate the reservation details during check-in
int validateCheckIn(long reservationID, const char *checkInDate);

// Function to update reservation status in the "Reservation.txt" file
int updateReservationStatus(long reservationID);

// Function to update room status in the "Room.txt" file
int updateRoomStatus(int roomID);

// Helper function to compare dates
int compareDates(const Reservation reservation, const charcheckInDate);

// Utility function to fetch room number associated with a reservation ID
int getRoomNumberByReservationID(long reservationID, char *roomNumber);

// Function to handle the check-in process
void processCheckIn(long reservationID,const char *checkInDate);

#endif