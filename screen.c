//
// Created by edoardo on 25/07/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "game.h"


void draw_screen_tetris(struct screen_options *sco, struct screen_state *scs, struct blocks_state *bls) {
    map_active_state_to_board(scs, bls->active->normalized_pos);
    map_completed_blocks_to_board(scs,bls);
    printf("  ");
    for (int k=0;k<sco->board_dim_x;k++) {
        printf("_");
    }
    printf("\n");
    for (int i=0;i<sco->board_dim_y;i++) {
        printf("%s",sco->border);
        for (int j=0; j<sco->board_dim_x;j++) {
           if(*(scs->active_board+(i*sco->board_dim_x+j))==1 ) {
               printf("*");
           } else {
               printf(" ");
           }
        }
        printf("%s\n",sco->border);
    }

    for (int k=0;k<sco->board_dim_x+4;k++) {
        printf("=");
    }
    printf("\n");
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

    } else if (dimension=='2') {
        sco->board_dim_x=MEDIUM_X;
        sco->board_dim_y=MEDIUM_Y;
        sco->dimension=2;
        board=malloc(sizeof(int)*MEDIUM_Y*MEDIUM_X);

    } else {
        sco->board_dim_x=LARGE_X;
        sco->board_dim_y=LARGE_Y;
        sco->dimension=3;
        board=malloc(sizeof(int)*LARGE_Y*LARGE_X);

    }
    sco->border="||";
    // init active_board
    scs->active_board=board;
}

void clear_active_board(int previous_pos[4], struct screen_state* scs) {
    for(int i=0; i<4; i++) {
        *(scs->active_board+previous_pos[i])=0;
    }
}

void clear_completed_blocks(int* previous_complete_blocks, struct screen_state* scs, int dimension) {
    for (int i=0;i<dimension;i++) {
        if (*(previous_complete_blocks+i)==1) *(scs->active_board+i)=0;
    }
}