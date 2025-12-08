#define _XOPEN_SOURCE_EXTENDED
#include <ncurses.h>
#include <stddef.h>
#include <locale.h>
#include <stdlib.h>

void move_wch(WINDOW* win, int y, int x) {
    cchar_t t;
    win_wch(win, &t);
    wdelch(win);
    mvwadd_wch(win, y, x, &t);
}

void move_area(WINDOW* win, int y, int x, int height, int width) {
    cchar_t t[1024];
    int origin_x = getcurx(win);
    int origin_y = getcury(win);
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            mvwin_wch(win, origin_y + j, origin_x + i, &t[i + j * width]);
            mvwaddch(win, origin_y + j, origin_x + i, ' ');
        }
    }
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            mvwadd_wch(win, y + j, x + i, &t[i + j * width]);
        }
    }
    wmove(win, y, x);
}

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
    wmove(inputwin, 1, 1);
    
    waddch(inputwin, 'a');
    waddch(inputwin, 'p');
    waddch(inputwin, 'p');
    waddch(inputwin, 'l');
    waddch(inputwin, 'e');
    wmove(inputwin, 1, 1);
    move_area(inputwin, 5, 2, 1, 5);
    // move_wch(inputwin, 2, 2);
    wmove(inputwin, 3, 3);

    refresh();
    wrefresh(inputwin);

    keypad(inputwin, true);
    getch();
    endwin();

    return 0;
}

