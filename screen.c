//
// Created by edoardo on 25/07/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "screen.h"


void draw_screen_tetris(struct screen_options* sco, struct screen_state* scs) {
    printf("  ");
    for (int k=0;k<sco->board_dim_x;k++) {
        printf("_");
    }
    printf("\n");
    for (int i=0;i<sco->board_dim_y;i++) {
        printf("%s",sco->border);
        for (int j=0; j<sco->board_dim_x;j++) {
           if(i==sco->board_dim_y-1) {
               printf("_");
           }
           else if(*(scs->active_board+(i*sco->board_dim_x+j))==1 ) {
               printf("*");
           } else {
               printf(" ");
           }
        }
        printf("%s\n",sco->border);
    }
}
void init_screen_tetris(struct screen_options* sco, struct screen_state* scs) {
    char dimension;
    int* board;
    do {
        printf("\nScegli dimensione dello schermo\n\n Piccolo     Normale     Grande\n    1           2          3\n");
        scanf(" %c",&dimension);
    } while(dimension<'1' ||dimension>'3');
    if (dimension=='1') {
        sco->board_dim_x=SMALL_X;
        sco->board_dim_y=SMALL_Y;
        sco->dimension=1;
        board=malloc(sizeof(int)*SMALL_Y*SMALL_X);
        for(int i=0;i<SMALL_Y*SMALL_X;i++) {
            *(board+i)=0;
        }
    } else if (dimension=='2') {
        sco->board_dim_x=MEDIUM_X;
        sco->board_dim_y=MEDIUM_Y;
        sco->dimension=2;
        board=malloc(sizeof(int)*MEDIUM_Y*MEDIUM_X);
        for(int i=0;i<MEDIUM_Y*MEDIUM_X;i++) {
            *(board+i)=0;
        }
    } else {
        sco->board_dim_x=LARGE_X;
        sco->board_dim_y=LARGE_Y;
        sco->dimension=3;
        board=malloc(sizeof(int)*LARGE_Y*LARGE_X);
        for(int i=0;i<LARGE_Y*LARGE_X;i++) {
            *(board+i)=0;
        }
    }
    sco->border="||";
    // init active_board
    scs->active_board=board;
}
