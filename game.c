//
// Created by edoardo on 25/07/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "game.h"


void start_game(struct game_state* gs) {
    printf("\n********************************\n***          TETRIS          ***\n********************************\n\n"
           " in ogni momento, premi 'e' per\n   uscire e le frecciette per\n       muovere i blocchi\n___________________"
           "____________\n");
    init_screen_tetris(&gs->sco,&gs->scs);
    init_board_state(&gs->sco,&gs->scs);
}

void init_board_state(struct screen_options* sco, struct screen_state* scs) {
    int initial_x=sco->board_dim_x/2;
    int final_x=initial_x+1;
    *(scs->active_board+initial_x)=1;
    *(scs->active_board+final_x)=1;
    *(scs->active_board+(sco->board_dim_x+initial_x))=1;
    *(scs->active_board+(sco->board_dim_x+final_x))=1;
}


void move_active_block_down(struct screen_options *sco, struct screen_state *scs) {
    int dim_x = sco->board_dim_x;
    int dim_y = sco->board_dim_y;
    for (int i = (dim_x*dim_y)-1;i>0; i--) {
        if(*(scs->active_board+i)==1) {
            *(scs->active_board+i)=0;
            int new_row=(i/dim_x)+1; //i/dim_x is the old row
            int offset=i%dim_x;
            *(scs->active_board+(new_row*dim_x+offset))=1; //update board with 1 in next row
        }
    }
}
void move_active_block_right(struct screen_options *sco, struct screen_state *scs) {
    int dim_x = sco->board_dim_x;
    int dim_y = sco->board_dim_y;
    for (int i = (dim_x*dim_y)-1;i>0; i--) {
        if(*(scs->active_board+i)==1) {
            *(scs->active_board+i)=0;
            *(scs->active_board+i+1)=1;
        }
    }
}