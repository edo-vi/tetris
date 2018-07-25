
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>

int main(void) {
    int i =0;
    while (i<20) {

        printf("\033c");
        for (int j=0;j<i;j++) {
            printf("\n");
        }
        printf("Hello, World!\n");

        struct timespec time_to_sleep;
        struct timespec second_time;
        time_to_sleep.tv_sec=0;
        time_to_sleep.tv_nsec=500000000;
        nanosleep(&time_to_sleep,&second_time);
        printf("\033c");
        i++;
    }

    return 0;
}