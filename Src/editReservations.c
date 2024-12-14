#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reservations.h"
#include "editReservations.h"

Customer ViewCustomerDetails(long id){
    FILE *file = fopen("output/Reservations.txt","r");
    char line[200];
    int found = 0;
    while (fgets(line,200,file)){
        Customer cst;
        sscanf(line, "%ld,%d,%[^,],%[^,],%d,%d-%d-%d,%[^,],%[^,],%s", &cst.reservationID, &cst.room_id, cst.status, cst.name, &cst.numberOfnights ,&cst.day, &cst.month, &cst.year, cst.email, cst.nationalId, cst.phone);
        if (id == cst.reservationID || id == cst.room_id)
        {
            fclose(file);
            return cst;
        }
    }
    fclose(file);
}