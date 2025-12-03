#define _XOPEN_SOURCE_EXTENDED
#include <ncurses.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

// struct barchart {
//     int max_lines;
//     int column_gap;
//     int x;
//     int y;
//     float max_value;
//     int num_columns;
//     float* y_values;
//     wchar_t** column_names;

//     bool staggered_axis_titles;
//     bool show_values_above_bar;
//     int sigfigs;
//     WINDOW * inputwin;
// }

enum direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

struct barchart {
    int width;
    int height;
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
        
// void draw_axis_name(WINDOW * inputwin,  wchar_t* name, int column, int col_gap, bool staggered){
//     int x_value = x+(column*col_gap)+2;
//     int y_value = y + 1;
//     if(staggered) {
//         y_value += column;
//     }
//     mvwaddwstr(inputwin, y_value, x_value, name);
// }

// TODO
// void clear_chart(WINDOW * inputwin, int max_lines, int max_columns, int col_gap, int y, int x){
// 
// }

// void draw_axis(WINDOW * inputwin, int y, int x, int max_lines, int max_columns, int col_gap){

//     mvwaddch(inputwin, y - max_lines, x, ACS_TTEE);
//     mvwvline(inputwin, y - max_lines + 1, x, ACS_VLINE, max_lines-1);
//     mvwaddch(inputwin, y, x, ACS_LLCORNER);
//     mvwhline(inputwin, y, x+1, ACS_HLINE, max_columns * col_gap);
//     mvwaddch(inputwin, y, x + (max_columns * col_gap) + 1, ACS_RTEE); 
// }

// void draw_max_value(WINDOW * inputwin, int y, int x, float max_value, int sigfigs, int max_lines){
//     mvwprintw(inputwin, y - max_lines, x - sigfigs - 1, "%*f", sigfigs, max_value);  
// }

    // // draw number
    // if(show_val) {
    //     int length = fmin(col_gap - 1, sigfigs);
    //     mvwprintw(inputwin, y - ifull_lines-2, x_value, "%*f", length, y_value); 
    // }

void north_bar(WINDOW * win, int y, int x, int norm, float max_value, float value) {
    float line_height = value * norm / max_value;

    float full_lines = floor(line_height);

    float remaining = line_height - full_lines;

    int rem_eights = (int)floor(remaining * 8);

    int ifull_lines = (int) full_lines;

    const wchar_t * block_choice;

    if(rem_eights == 1) {
        block_choice = L"\u2581";
    } else if(rem_eights == 2) {
        block_choice = L"\u2582";
    } else if(rem_eights == 3) {
        block_choice = L"\u2583";
    } else if(rem_eights == 4) {
        block_choice = L"\u2584";
    } else if(rem_eights == 5) {
        block_choice = L"\u2585";
    } else if(rem_eights == 6) {
        block_choice = L"\u2586";
    } else if(rem_eights == 7) {
        block_choice = L"\u2587";
    }

    for(int i = y; i > y - ifull_lines; i--){
        mvwaddwstr(win, i, x, L"\u2588");
    }
    if(rem_eights != 0) {
        mvwaddwstr(win, y - ifull_lines, x, block_choice);
    }
} 

void south_bar(WINDOW * win, int y, int x, int norm, float max_value, float value) {
    float line_height = value * norm / max_value;

    float full_lines = floor(line_height);

    float remaining = line_height - full_lines;

    int rem_half = (int)floor(remaining * 2);

    int ifull_lines = (int) full_lines;

    for(int i = y; i < y + ifull_lines; i++){
        mvwaddwstr(win, i, x, L"\u2588");
    }

    if (rem_half == 1) {
        mvwaddwstr(win, y + ifull_lines, x, L"\u2580");
    }
} 

void east_bar(WINDOW * win, int y, int x, int norm, float max_value, float value) {
    float line_height = value * norm / max_value;

    float full_lines = floor(line_height);

    float remaining = line_height - full_lines;

    int rem_eights = (int)floor(remaining * 8);

    int ifull_lines = (int) full_lines;

    const wchar_t * block_choice;

    if(rem_eights == 1) {
        block_choice = L"\u258F";
    } else if(rem_eights == 2) {
        block_choice = L"\u258E";
    } else if(rem_eights == 3) {
        block_choice = L"\u258D";
    } else if(rem_eights == 4) {
        block_choice = L"\u258C";
    } else if(rem_eights == 5) {
        block_choice = L"\u258B";
    } else if(rem_eights == 6) {
        block_choice = L"\u258A";
    } else if(rem_eights == 7) {
        block_choice = L"\u2589";
    }

    for(int i = x; i < x + ifull_lines; i++){
        mvwaddwstr(win, y, i, L"\u2588");
    }

    if(rem_eights != 0) {
        mvwaddwstr(win, y, x + ifull_lines, block_choice);
    }
} 

void west_bar(WINDOW * win, int y, int x, int norm, float max_value, float value) {
    float line_height = value * norm / max_value;

    float full_lines = floor(line_height);

    float remaining = line_height - full_lines;

    int rem_half = (int)floor(remaining * 2);

    int ifull_lines = (int) full_lines;

    for(int i = x; i > x - ifull_lines; i--){
        mvwaddwstr(win, y, i, L"\u2588");
    }

    if (rem_half == 1) {
        mvwaddwstr(win, y, x - ifull_lines, L"\u2590");
    }
} 

void draw_chart(WINDOW * win, int y, int x, struct barchart* chart) {
    // find max_value
    float max_value = 0;
    for(int i = 0; i < chart->num_labels; i++) {
        max_value = fmax(chart->values[i], max_value);
    };

    int gap, norm, start;

    switch (chart->dir) {
    case NORTH:
        gap = chart->width / chart->num_labels;
        norm = chart->height;
        start = y + chart->height;
        for(int k = 0; k < chart->num_labels; k++) {
            // mvwprintw(win, start, x + (gap * k), "34");
            north_bar(win, start, x + (gap * k), norm, max_value, chart->values[k]);
        }
        break;
    case SOUTH:
        gap = chart->width / chart->num_labels;
        norm = chart->height;
        start = y;
        for(int k = 0; k < chart->num_labels; k++) {
            south_bar(win, start, x + (gap * k), norm, max_value, chart->values[k]);
        }
        break;
    case WEST:
        gap = chart->height / chart->num_labels;
        norm = chart->width;
        start = x + chart->width;
        for(int k = 0; k < chart->num_labels; k++) {
            west_bar(win, y + (gap * k), start, norm, max_value, chart->values[k]);
        }
        break;
    case EAST:
        gap = chart->height / chart->num_labels;
        norm = chart->height;
        start = x;
        for(int k = 0; k < chart->num_labels; k++) {
            east_bar(win, y + (gap * k), start, norm, max_value, chart->values[k]);
        }
        break;
    }
    // draw_axis(win, y, x, length, col_gap);
    // draw_max_value(win, y, x, max_value, sigfigs, max_lines);
    // for(int i = 0; i < chart->num_labels; i++){
    //     draw_bar(win, y + (y_gap * i), x + (x_gap * i), y_delta, x_delta, norm, chart->values[i]);
    //     // draw_axis_name(win, y, x, col_names[i], i, col_gap, staggered);
    // }
    // resets to origin
    wmove(win, y, x);
}
