#include "barchart.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    /* NCURSES START */
    initscr();
    noecho();
    cbreak();
    
    // get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW * inputwin = newwin(yMax, xMax, 0, 0);

    box(inputwin, 0, 0);

    struct barchart* chart = alloc_barchart(5);
    chart->values[0] = 34;
    chart->values[1] = 100;
    chart->values[2] = 20;
    chart->values[3] = 45;
    chart->values[4] = 60;
    wchar_t* a = L"a";
    wchar_t* b = L"b";
    wchar_t* c = L"c";
    chart->labels[0] = a;
    chart->labels[1] = b;
    chart->labels[2] = c;
    chart->dir = EAST;
    chart->height = yMax / 2;
    chart->width = xMax / 2;
    draw_chart(inputwin, 5, 10, chart);
    refresh();
    wrefresh(inputwin);

    keypad(inputwin, true);
    curs_set(0);
    getch();
    endwin();
    free_barchart(chart);
    return 0;
}
