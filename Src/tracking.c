#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

void track()
{
    FILE *room;
    room = fopen("output/Room.txt", "r");
    char line[200];
    while (fgets(line,200,room)){
        printw("%s",line);
        refresh();
    }

    fclose(room);
}