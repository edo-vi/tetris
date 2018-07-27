
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>
#include <poll.h>
#include <pthread.h>

#include "game.h"
#include "screen.h"


/*
 * GLOBALS
 */
struct game_state gs;

void change_active_block_form(struct screen_options *sco, struct screen_state *scs, struct blocks_state *bls);

int must_delay_thread=0;

void *move_block_down_periodically(void *arg) {
    struct timespec time_to_sleep;
    struct timespec second_time;
    time_to_sleep.tv_sec = 0;
    time_to_sleep.tv_nsec = (long) 400000000;

    while(1) {

        nanosleep(&time_to_sleep, &second_time);
        if (must_delay_thread==1) {
            must_delay_thread=0;
            continue;
        }
        move_active_block_down(&gs.sco, &gs.scs, &gs.bls);
    }
}

int main(void) {

    srand(time(NULL));

    start_game(&gs);

    pthread_t tid;
    pthread_create(&tid, NULL, &move_block_down_periodically, NULL);
    int ch;
    do {

        printf("\033c");

        draw_screen_tetris(&gs.sco, &gs.scs, &gs.bls);

        initscr();
        keypad(stdscr, TRUE);
        halfdelay(7);

        ch=getch();

        endwin();

        if (ch==258) { //258
            must_delay_thread=1;
            move_active_block_down(&gs.sco, &gs.scs, &gs.bls);
        }
        else if (ch==261) { //261
            move_active_block_right(&gs.sco, &gs.scs,&gs.bls);
        } else if (ch==260) {//260
            move_active_block_left(&gs.sco, &gs.scs,&gs.bls);
        } else if (ch=='w') {
            must_delay_thread=1;
            change_active_block_form(&gs.sco, &gs.scs, &gs.bls);
            draw_screen_tetris(&gs.sco, &gs.scs, &gs.bls);
        }

    } while(ch!=101);
    printf("\033c");
    return 0;
}


