#include <stdlib.h>
#include <curses.h>
#include "Src/headerFiles/menu.h"

int main()
{
    initscr();           
    cbreak();           
    keypad(stdscr, TRUE); 

    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK); 
        init_pair(4, COLOR_GREEN, COLOR_BLACK); 
        init_pair(5, COLOR_WHITE, COLOR_BLACK);
        init_pair(6, COLOR_YELLOW, COLOR_BLACK);
        init_pair(7, COLOR_RED, COLOR_BLACK); 
        init_pair(8, COLOR_GREEN, COLOR_BLACK); 
        init_pair(9, COLOR_RED, COLOR_WHITE); 

    }

    mainMenu();

    endwin(); 
    return 0;
}
