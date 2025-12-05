#define _XOPEN_SOURCE_EXTENDED
#include <ncurses.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct point {
    int y;
    int x;
};

enum direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

struct barchart {
    int width;
    int height;
    int xmargin;
    int ymargin;
    enum direction dir;
    int num_labels;
    float* values;
    wchar_t** labels;
};

struct barchart* alloc_barchart(int num_labels) {
    float* values = calloc(num_labels, sizeof(float));
    wchar_t** labels = malloc(num_labels * sizeof(wchar_t*));
    struct barchart * chart = malloc(sizeof(struct barchart));
    *chart = (struct barchart) {
        0,
        0,
        1,
        1,
        NORTH,
        num_labels,
        values,
        labels
    };
    return chart;
}

void free_barchart(struct barchart* chart) {
    free(chart->values);
    free(chart->labels);
    free(chart);
}
        
#define X_MARGIN 3
#define Y_MARGIN 3

void draw_axis(WINDOW * win, int y, int x, enum direction dir, int length, int gap) {   
    int xdelta = 0;
    int ydelta = 0;
    char line = ' ';
    char tick = ' ';
    switch(dir) {
        case NORTH:
            ydelta = -1;
            line = '|';
            tick = '-';
            break;
        case SOUTH:
            ydelta = 1;
            line = '|';
            tick = '-';
            break;
        case EAST:
            xdelta = 1;
            line = '-';
            tick = '|';
            break;
        case WEST:
            xdelta = -1;
            line = '-';
            tick = '|';
        break;
    }
    int ycurr = y;
    int xcurr = x;
    wmove(win, ycurr, xcurr);
    for(int i = 0; i < length; i++) {
        if(i % gap == 0)
            waddch(win, tick);
        else
            waddch(win, line);
        ycurr = ycurr + ydelta;
        xcurr = xcurr + xdelta;
        wmove(win, ycurr, xcurr);
    }
    wmove(win, y, x);
}

void dirtodelta(struct point* p, enum direction dir) {
    switch(dir) {
        case EAST: *p = (struct point) { 0, 1 }; break;
        case WEST: *p = (struct point) { 0, -1 }; break;
        case NORTH: *p = (struct point) { -1, 0 }; break;
        case SOUTH: *p = (struct point) { 1, 0 }; break;
    };
}

const wchar_t* _block_symbols[] = {
  L"\u2580",
  L"\u2581",
  L"\u2582",
  L"\u2583",
  L"\u2584",
  L"\u2585",
  L"\u2586",
  L"\u2587",
  L"\u2588",
  L"\u2589",
  L"\u258A",
  L"\u258B",
  L"\u258C",
  L"\u258D",
  L"\u258E",
  L"\u258F",
  L"\u2590",
};

void set_end_symbol(cchar_t* wch, enum direction dir, int eights) {
    switch(dir) {
        case NORTH: setcchar(wch, _block_symbols[eights], 0, 0, NULL); break;
        case SOUTH: setcchar(wch, _block_symbols[8 - eights], A_REVERSE, 0, NULL); break;
        case EAST: setcchar(wch, _block_symbols[16 - eights], 0, 0, NULL); break;
        case WEST: setcchar(wch, _block_symbols[8 + eights], A_REVERSE, 0, NULL); break;
    };
}

void draw_bar(WINDOW * win, int y, int x, enum direction dir, int norm, float max_value, float value) {
    float line_height = value * norm / max_value;

    float full_lines = floor(line_height);

    float remaining = line_height - full_lines;

    int rem_eights = (int)floor(remaining * 8);

    int ifull_lines = (int) full_lines;

    struct point delta;
    dirtodelta(&delta, dir);

    wmove(win, y, x);
    int ycurr = y;
    int xcurr = x;
    for(int i = 0; i < ifull_lines; i++) {
        waddwstr(win, L"\u2588");
        ycurr = ycurr + delta.y;
        xcurr = xcurr + delta.x;
        wmove(win, ycurr, xcurr);
    }
    if(rem_eights != 0) {
        cchar_t last_char;
        set_end_symbol(&last_char, dir, rem_eights);
        wadd_wch(win, &last_char);
    }
    wmove(win, y, x);
}

void draw_chart(WINDOW * win, int y, int x, struct barchart* chart) {
    // find max_value
    float max_value = 0;
    for(int i = 0; i < chart->num_labels; i++) {
        max_value = fmax(chart->values[i], max_value);
    };

    int gap, norm, startx, starty, width, height;
    width = chart->width - chart->xmargin; 
    height = chart->height - chart->ymargin; 

    switch (chart->dir) {
    case NORTH:
        gap = width / chart->num_labels;
        norm = height;
        starty = y + height;
        startx = x + chart->xmargin;
        draw_axis(win, starty, startx - 1, NORTH, height, 4);
        draw_axis(win, starty + 1, startx, EAST, width, gap);
        for(int k = 0; k < chart->num_labels; k++) {
            draw_bar(win, starty, startx + (gap * k), NORTH, norm, max_value, chart->values[k]);
        }
        break;
    case SOUTH:
        gap = width / chart->num_labels;
        norm = height;
        starty = y + chart->ymargin;
        startx = x;
        draw_axis(win, starty, startx + width + 1, SOUTH, height, 4);
        draw_axis(win, starty - 1, startx, EAST, width, gap);
        for(int k = 0; k < chart->num_labels; k++) {
            draw_bar(win, starty, startx + (gap * k), SOUTH, norm, max_value, chart->values[k]);
        }
        break;
    case WEST:
        gap = height / chart->num_labels;
        norm = width;
        startx = x + width;
        starty = y + chart->ymargin;
        draw_axis(win, starty, startx + 1, SOUTH, height, gap);
        draw_axis(win, starty - 1, x + width, WEST, width, 4);
        for(int k = 0; k < chart->num_labels; k++) {
            draw_bar(win, starty + (gap * k), startx, WEST, norm, max_value, chart->values[k]);
        }
        break;
    case EAST:
        gap = height / chart->num_labels;
        norm = width;
        startx = x + chart->xmargin;
        starty = y;
        draw_axis(win, starty, startx - 1, SOUTH, height, gap);
        draw_axis(win, starty + height, startx, EAST, width, 4);
        for(int k = 0; k < chart->num_labels; k++) {
            draw_bar(win, starty + (gap * k), startx, EAST, norm, max_value, chart->values[k]);
        }
        break;
    }
    wmove(win, y, x);
}
