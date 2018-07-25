
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>
#include <poll.h>
#include "screen.h"
#include "game.h"

int main(void) {
    struct game_state gs;

    start_game(&gs);


    int i =0;

    struct timespec time_to_sleep;
    struct timespec second_time;
    time_to_sleep.tv_sec=0;
    time_to_sleep.tv_nsec=(long)700000000;


    while (1) {


        printf("\033c");

        draw_screen_tetris(&gs.sco,&gs.scs);

        initscr();
        keypad(stdscr, TRUE);
        halfdelay(7);
        int ch=getch();

        endwin();


        printf("\033c");

        if (ch==101) break;
        else if (ch==258) move_active_block_down(&gs.sco, &gs.scs);
        else if (ch==261) move_active_block_right(&gs.sco, &gs.scs);
        else move_active_block_down(&gs.sco, &gs.scs);
        i++;
    }

    return 0;
}