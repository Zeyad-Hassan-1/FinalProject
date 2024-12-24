#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "./headerFiles/reservations.h"

void swap(Customer* xp, Customer* yp) {
    Customer temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(Customer arr[], int n){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].checkindate > arr[j + 1].checkindate) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}

void sort()
{
    Customer customers[200];
    FILE *res = fopen("output/Reservations.txt", "r");
    if (res == NULL) {
        perror("Error opening file for reading");
        return;
    }

    char line[200];
    int i = 0;
    while (fgets(line, sizeof(line), res)) {
        if (sscanf(line, "%ld,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &customers[i].reservationID, &customers[i].room_id, customers[i].status, customers[i].name, customers[i].nationalId, &customers[i].numberOfnights, &customers[i].day, &customers[i].month, &customers[i].year, customers[i].email, customers[i].phone) == 11) {
            customers[i].checkindate = (customers[i].year * 365) + (customers[i].month * 30) + customers[i].day;
            i++;
        }
    }
    fclose(res);

    if (i == 0) {
        printf("No records found to sort.\n");
        return;
    }

    bubbleSort(customers, i);

    res = fopen("output/Reservations.txt", "w");
    if (res == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int j = 0; j < i; j++) {
        fprintf(res, "%ld,%d,%s,%s,%s,%d,%02d-%02d-%02d,%s,%s\n", customers[j].reservationID, customers[j].room_id, customers[j].status, customers[j].name, customers[j].nationalId, customers[j].numberOfnights, customers[j].day, customers[j].month, customers[j].year, customers[j].email, customers[j].phone);
    }
    fclose(res);
}