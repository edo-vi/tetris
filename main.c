
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>
#include <poll.h>
#include <pthread.h>

#include "screen.h"
#include "game.h"


struct game_state gs;
int must_delay_thread=0;

void *move_block_down_periodically(void *arg) {
    struct timespec time_to_sleep;
    struct timespec second_time;
    time_to_sleep.tv_sec = 0;
    time_to_sleep.tv_nsec = (long) 700000000;

    while(1) {

        nanosleep(&time_to_sleep, &second_time);
        if (must_delay_thread==1) {
            must_delay_thread=0;
            continue;
        }
        move_active_block_down(&gs.sco, &gs.scs);
    }
}

int main(void) {


    start_game(&gs);


    int i =0;

    pthread_t tid;
    pthread_create(&tid, NULL, &move_block_down_periodically, NULL);

    while (1) {

        printf("\033c");

        draw_screen_tetris(&gs.sco,&gs.scs);

        initscr();
        keypad(stdscr, TRUE);
        halfdelay(7);
        int ch=getch();

        endwin();


        if (ch==101) {
            printf("\033c");
            break;
        }
        else if (ch==258) {
            must_delay_thread=1;
            move_active_block_down(&gs.sco, &gs.scs);
        }
        else if (ch==261) move_active_block_right(&gs.sco, &gs.scs);



    }

    return 0;
}
