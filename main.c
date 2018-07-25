
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>
#include "screen.h"

int main(void) {
    struct screen_state screen;
    init_screen_tetris(&screen);

    int i =0;

    struct timespec time_to_sleep;
    struct timespec second_time;
    time_to_sleep.tv_sec=0;
    time_to_sleep.tv_nsec=(long)700000000;

    while (i<5) {


        printf("\033c");
        draw_screen_tetris(&screen);


        nanosleep(&time_to_sleep,&second_time);
        printf("\033c");
        i++;
    }

    return 0;
}