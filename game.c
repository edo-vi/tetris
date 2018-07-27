//
// Created by edoardo on 25/07/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "screen.h"
#include "block.h"

void start_game(struct game_state* gs) {
    printf("\n********************************\n***          TETRIS          ***\n********************************\n\n"
           " in ogni momento, premi 'e' per\n   uscire e le frecciette per\n       muovere i blocchi\n___________________"
           "____________\n");
    init_screen_tetris(&gs->sco,&gs->scs);
    init_board_state(&gs->sco,&gs->scs, &gs->bls);
    init_completed_blocks(&gs->sco, &gs->bls); //all zero here, obviously
}

void init_board_state(struct screen_options* sco, struct screen_state* scs, struct blocks_state* bls) {
    collocate_block_initial_position(bls,sco);
    //map_active_state_to_board(scs,bls->active->normalized_pos);
}

void map_active_state_to_board(struct screen_state* scs, int active_block_position[4]) {
    for (int i=0;i<4;i++) {
        *(scs->active_board+active_block_position[i])=1;
    }
}
void map_completed_blocks_to_board(struct screen_state* scs, struct blocks_state* bls) {
    for (int i=0;i<bls->dimension_completed_blocks;i++) {
        if((*(bls->completed_blocks+i))==1) {
            *(scs->active_board+i)=1;
        }
    }

}
void move_active_block_down(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls) {
    if (hit_on_bottom(bls, sco->board_dim_y, sco->board_dim_x)) {
        clear_active_board(bls->active->normalized_pos,scs);
        end_active_block_life(bls, sco, scs); // if is near bottom
        return;
    }
    clear_active_board(bls->active->normalized_pos,scs);
    for(int i=0;i<4;i++) {
        bls->active->pos[i][1]++;
    }
    convert_pos_to_normalized_pos(bls->active->pos, bls->active->normalized_pos, sco->board_dim_x);

    //map_active_state_to_board(scs, bls->active->normalized_pos);
}
void move_active_block_right(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls) {
    if (hit_on_right(bls, sco->board_dim_x)) return;
    clear_active_board(bls->active->normalized_pos,scs);
    for(int i=0;i<4;i++) {
        bls->active->pos[i][0]++;
    }
    convert_pos_to_normalized_pos(bls->active->pos, bls->active->normalized_pos, sco->board_dim_x);

    //map_active_state_to_board(scs, bls->active->normalized_pos);
}

void move_active_block_left(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls) {
    if (hit_on_left(bls)) return;
    clear_active_board(bls->active->normalized_pos,scs);
    for(int i=0;i<4;i++) {
        bls->active->pos[i][0]--;
    }
    convert_pos_to_normalized_pos(bls->active->pos, bls->active->normalized_pos, sco->board_dim_x);

    //map_active_state_to_board(scs, bls->active->normalized_pos);
}
/*
 * Returns 0 if no borders are near, else 1
 */
int hit_on_bottom(struct blocks_state *bls, int dim_y, int dim_x) {
    struct active_block* ab = bls->active;
    for (int i=0;i<4;i++) {
        // if block position is on last line, or the pos just below are occupied by finished blocks
        if (ab->pos[i][1]==dim_y-1 || *(bls->completed_blocks+(ab->normalized_pos[i]+dim_x))==1) return 1;
    }
    return 0;
};

int hit_on_left(struct blocks_state *bls) {
    struct active_block* ab = bls->active;
    for (int i = 0; i < 4; i++) {
        if (ab->pos[i][0] == 0 || *(bls->completed_blocks+(ab->normalized_pos[i])-1)==1) return 1;
    }
    return 0;
}

int hit_on_right(struct blocks_state *bls, int dim_x) {
    struct active_block* ab = bls->active;
    for (int i = 0; i < 4; i++) {
        if (ab->pos[i][0] == dim_x - 1 || *(bls->completed_blocks+(ab->normalized_pos[i])+1)==1) return 1;
    }
    return 0;
}

void clear_line_if_completed(struct blocks_state *bls, struct screen_options *sco, struct screen_state *scs) {
    int max = 0;
    for (int i =0; i<4;i++) {
        if (max<bls->active->normalized_pos[i]) max=bls->active->normalized_pos[i];
    }
    int row = max/sco->board_dim_x;
    int start=row*sco->board_dim_x;
    int iscompleted = 1;
    for (int j = start; j< start+sco->board_dim_x; j++) {
        if (*(bls->completed_blocks+j)==0) {
            iscompleted=0;
            break;
        }
    }

    if (iscompleted) {
        clear_completed_blocks(bls->completed_blocks,scs,bls->dimension_completed_blocks);
        for (int k = start; k< start+sco->board_dim_x; k++) {
            *(bls->completed_blocks+k)=0;
        }
        for (int l=start-1;l>0;l--) {
            if (*(bls->completed_blocks+l)==1) {
                *(bls->completed_blocks+l)=0;
                *(bls->completed_blocks+l+sco->board_dim_x)=1;
            }
        }

    }

}