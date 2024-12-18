#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./headerFiles/reservations.h"
#include "./headerFiles/editReservations.h"
#include <curses.h>

Customer ViewCustomerDetails()
{
    long id;
    attron(COLOR_PAIR(1));
    printw("Enter reservation id or room id to view your data..\n");
    attroff(COLOR_PAIR(1));
    scanw("%ld", &id);
    FILE *file = fopen("output/Reservations.txt", "r");
    char line[200];
    int found = 0;
    while (fgets(line, 200, file))
    {
        Customer csv;
        sscanf(line, "%ld,%d,%[^,],%[^,],%d,%d-%d-%d,%[^,],%[^,],%s", &csv.reservationID, &csv.room_id, csv.status, csv.name, &csv.numberOfnights, &csv.day, &csv.month, &csv.year, csv.email, csv.nationalId, csv.phone);
        if (id == csv.reservationID || id == csv.room_id)
        {
            attron(COLOR_PAIR(2));
            printw("Name : %s \n Phone Number: %s \n Email: %s \n National Id: %s \n Number of Nights: %d \n Check in date : %02d %02d %02d\n\n", csv.name, csv.phone, csv.email, csv.nationalId, csv.numberOfnights, csv.day, csv.month, csv.year);
            attroff(COLOR_PAIR(2));
            refresh();
            fclose(file);
            return csv;
        }
    }
    fclose(file);
}

int Quit()
{
    return 0;
}

int cancel()
{
    long id;
    int room_id = 0, found = 0;
    FILE *res = fopen("output/Reservations.txt", "r");
    if (!res) {
        perror("Error opening Reservations.txt");
        exit(EXIT_FAILURE);
    }

    FILE *temp = fopen("output/tmp.txt", "w");
    if (!temp) {
        perror("Error opening tmp.txt");
        fclose(res);
        exit(EXIT_FAILURE);
    }

    printw("Enter reservation_id or Room_id...\n");
    refresh();
    scanw("%ld", &id);

    char reservation[200];
    while (fgets(reservation, sizeof(reservation), res))
    {
        long reservationId;
        int roomId, numofNights, day, month, year;
        char stat[20], name[20], email[20], nId[20], phone[20];

        sscanf(reservation, "%ld,%d,%[^,],%[^,],%d,%d-%d-%d,%[^,],%[^,],%s", 
               &reservationId, &roomId, stat, name, &numofNights, 
               &day, &month, &year, email, nId, phone);

        if ((id == reservationId || id == roomId) && !strcmp(stat, "unconfirmed"))
        {
            found = 1;
            clear();
            printw("Reservation cancelled successfully\n");
            refresh();
            room_id = roomId; // حفظ ID الغرفة لإلغاء الحجز
            continue;
        }

        fprintf(temp, "%ld,%d,%s,%s,%d,%02d-%02d-%02d,%s,%s,%s\n",
                reservationId, roomId, stat, name, numofNights, 
                day, month, year, email, nId, phone);
    }

    fclose(res);
    fclose(temp);

    if (!found) {
        clear();
        printw("ReservationId or RoomId NOT FOUND!!!!\n");
        refresh();
        remove("output/tmp.txt"); // إزالة الملف المؤقت في حالة عدم وجود حجز
        return 0;
    }

    // حذف الملف الأصلي
    if (remove("output/Reservations.txt") != 0) {
        perror("Error deleting Reservations.txt");
        exit(EXIT_FAILURE);
    }

    // إعادة تسمية الملف المؤقت
    if (rename("output/tmp.txt", "output/Reservations.txt") != 0) {
        perror("Error renaming tmp.txt");
        exit(EXIT_FAILURE);
    }

    // تغيير حالة الغرفة إذا تم تحديدها
    if (room_id) {
        changeRoomStat(room_id);
    }

    return room_id;
}


void changeRoomStat(int roomId)
{
    FILE *roomFile = fopen("output/Room.txt", "r");
    FILE *tempFile = fopen("output/tmproom.txt", "w");
    if (!roomFile || !tempFile)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[200];
    while (fgets(line, 200, roomFile))
    {
        int room_id, price;
        char stat[20], category[20];
        sscanf(line, "%d %s %s %d", &room_id, stat, category, &price);
        if (room_id == roomId)
        {
            if (!strcmp(stat, "Reserved"))
                strcpy(stat, "Available");
            else
                strcpy(stat, "Reserved");
        }
        fprintf(tempFile, "%d %s %s %d\n", room_id, stat, category, price);
    }
    fclose(roomFile);
    fclose(tempFile);

    remove("output/Room.txt");
    rename("output/tmproom.txt", "output/Room.txt");
}