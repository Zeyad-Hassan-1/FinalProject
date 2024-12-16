#include <stdlib.h>
#include <curses.h>
#include "Src/menu.h"

int main()
{
    initscr();           // بدء شاشة ncurses
    cbreak();            // إدخال الأحرف مباشرة دون انتظار Enter
    keypad(stdscr, TRUE); // تفعيل مفاتيح الأسهم

    if (has_colors()) // تفعيل الألوان
    {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);  // خلفية زرقاء
        init_pair(2, COLOR_YELLOW, COLOR_BLACK); // نص أصفر
        init_pair(3, COLOR_RED, COLOR_BLACK);    // نص أحمر
        init_pair(4, COLOR_GREEN, COLOR_BLACK);  // نص أخضر
    }

    mainMenu(); // استدعاء القائمة الرئيسية

    endwin(); // إنهاء ncurses
    return 0;
}
