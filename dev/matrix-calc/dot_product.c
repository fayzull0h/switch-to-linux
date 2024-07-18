// A demonstration of the dot product functionality of the vector module
//
// Developed by Fayzulloh Ergashev

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "vector.h"
#include "number.h"
#include <string.h>

const int SPACES = 8;

void vector_move(int y, int x) {
    if (x == 2) {
        x = SPACES + 4 + 1;
    }
    move(y, x);
}

void draw_vector(struct vector * v, int select, char left, char right, bool is_highlighted) {
    int vsize = get_vector_n(v);
    int x = getcurx(stdscr);
    int y = getcury(stdscr);

    struct Number * ZERO = create_number(0, 0);

    for (int i = 0; i < vsize; ++i) {
        mvprintw(y + i, x, "%c", left);

        if (select == i) {
            attron(A_STANDOUT);
            if (is_highlighted) {
                attroff(A_STANDOUT);
                attron(COLOR_PAIR(1));
            }
        }

        if (num_equal(ith_element(v, i), ZERO)) {
            for (int j = 0; j < SPACES; ++j) {
                if (is_highlighted && select == i) {
                    printw(" ");
                } else {
                    printw("_");
                }
            }
        } else {
            char * str_num = str_from_num(ith_element(v, i));
            int slen = strlen(str_num);
            for (int i = 0; i < SPACES - slen; ++i) {
                printw(" ");
            }
            printw("%s", str_num);
            free(str_num);
        }
        attroff(COLOR_PAIR(1));
        attroff(A_STANDOUT);
        printw("%c", right);
    }
    free(ZERO);
}

void draw_two(struct vector * v1, struct vector * v2, int select, bool is_highlighted) {
    move(1, 0);
    int vsize = get_vector_n(v1);

    if (select >= vsize) {
        select -= vsize;
        draw_vector(v1, -1, '|', '|', false);
        move(1, SPACES + 4);
        draw_vector(v2, select, '|', '|', is_highlighted);
    } else {
        draw_vector(v1, select, '|', '|', is_highlighted);
        move(1, SPACES + 4);
        draw_vector(v2, -1, '|', '|', false);
    }
}

void input_number(struct vector * v, int which) {
    int vsize = get_vector_n(v);
    char str[10];
    
    refresh();

    echo();
    getstr(str);
    noecho();

    struct Number * num = num_from_str(str);
    set_vector_element(v, which - 1, num);
}

void get_input(struct vector * v1, struct vector * v2) {
    // Initial setup: get size of v, etc
    int vsize = get_vector_n(v1);
    int ch;
    bool is_highlighted;

    int posx = 1;
    int posy = 1;

    // Initial drawing of vectors
    int select = 0;
    draw_two(v1, v2, select, false);

    // Input loop
    while (1) {
        // Moving, but inside the vectors
        vector_move(posy, posx);
        ch = getch();

        // Analyze input and do action
        if (ch == 'k' || ch == KEY_UP) {
            if (select != 0 && select != vsize) {
                select--;
                posy--;
            }
        } else if (ch == 'j' || ch == KEY_DOWN) {
            if (select != vsize - 1 && select != vsize * 2 - 1) {
                select++;
                posy++;
            }
        } else if (ch == 'h' || ch == KEY_LEFT) {
            if (select >= vsize) {
                select -= vsize;
                posx--;
            }
        } else if (ch == 'l' || ch == KEY_RIGHT) {
            if (select < vsize) {
                select += vsize;
                posx++;
            }
        } else if (ch == 10) {
            is_highlighted = true;
            draw_two(v1, v2, select, is_highlighted);
            refresh();
            vector_move(posy, posx);
            if (posx == 1) {
                input_number(v1, posy);
            } else {
                input_number(v2, posy);
            }
            is_highlighted = false;
        }
        else if (ch == 'q') {break;}

        // Draw and refresh
        draw_two(v1, v2, select, is_highlighted);
        refresh();
    }
}

int main() {
    // Initial setup, with size of vectors
    printf("How many elements in vector? ");
    int temp = 0;
    scanf(" %d", &temp);
    struct vector * myvec1 = create_vector(temp);  
    struct vector * myvec2 = create_vector(temp);

    // Start up ncurses, with color, and prompt for input of numbers
    initscr(); 
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_GREEN);
    mvprintw(0, 0, "Enter numbers:");
    refresh();
    
    // Actually get the input
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    move(1,0);
    get_input(myvec1, myvec2);

    struct Number * dotp = dot_product(myvec1, myvec2);

    zeroify_vector(myvec1);
    zeroify_vector(myvec2);
    clear();
    mvprintw(0, 0, "Final Result: ");
    draw_two(myvec1, myvec2, -1, false);
    mvprintw(temp + 2, 0, "Dot product: %s", str_from_num(dotp));

    // Finish program
    refresh();
    getch();

    endwin();

    destroy_vector(myvec1);
    destroy_vector(myvec2);
    return 0;
}