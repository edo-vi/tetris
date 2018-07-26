//
// Created by edoardo on 25/07/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "game.h"
#include "block.h"

void start_game(struct game_state* gs) {
    printf("\n********************************\n***          TETRIS          ***\n********************************\n\n"
           " in ogni momento, premi 'e' per\n   uscire e le frecciette per\n       muovere i blocchi\n___________________"
           "____________\n");
    init_screen_tetris(&gs->sco,&gs->scs);
    init_board_state(&gs->sco,&gs->scs, &gs->bls);
    init_finished_blocks(&gs->sco,&gs->bls); //all zero here, obviously
}

void init_board_state(struct screen_options* sco, struct screen_state* scs, struct blocks_state* bls) {
    collocate_block_initial_position(bls,sco);
    map_active_state_to_board(scs,bls->active->normalized_pos);
}

void map_active_state_to_board(struct screen_state* scs, int active_block_position[4]) {
    for (int i=0;i<4;i++) {
        *(scs->active_board+active_block_position[i])=1;
    }
}
void move_active_block_down(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls) {
    if (hit_on_bottom(bls, sco->board_dim_y, sco->board_dim_x)) end_active_block_life(bls, sco); // if is near bottom
    clear_active_board(bls->active->normalized_pos,scs);
    for(int i=0;i<4;i++) {
        bls->active->pos[i][1]++;
    }
    convert_pos_to_normalized_pos(bls->active->pos, bls->active->normalized_pos, sco->board_dim_x);

    map_active_state_to_board(scs, bls->active->normalized_pos);
}
void move_active_block_right(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls) {
    if (hit_on_right(bls, sco->board_dim_x)) return;
    clear_active_board(bls->active->normalized_pos,scs);
    for(int i=0;i<4;i++) {
        bls->active->pos[i][0]++;
    }
    convert_pos_to_normalized_pos(bls->active->pos, bls->active->normalized_pos, sco->board_dim_x);

    map_active_state_to_board(scs, bls->active->normalized_pos);
}

void move_active_block_left(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls) {
    if (hit_on_left(bls)) return;
    clear_active_board(bls->active->normalized_pos,scs);
    for(int i=0;i<4;i++) {
        bls->active->pos[i][0]--;
    }
    convert_pos_to_normalized_pos(bls->active->pos, bls->active->normalized_pos, sco->board_dim_x);

    map_active_state_to_board(scs, bls->active->normalized_pos);
}
/*
 * Returns 0 if no borders are near, else 1
 */
int hit_on_bottom(struct blocks_state *bls, int dim_y, int dim_x) {
    struct active_block* ab = bls->active;
    for (int i=0;i<4;i++) {
        // if block position is on last line, or the pos just below are occupied by finished blocks
        if (ab->pos[i][1]==dim_y-1 || *(bls->finished_blocks+(ab->normalized_pos[i]+dim_x))==1) return 1;
    }
    return 0;
};

int hit_on_left(struct blocks_state *bls) {
    struct active_block* ab = bls->active;
    for (int i = 0; i < 4; i++) {
        if (ab->pos[i][0] == 0 || *(bls->finished_blocks+(ab->normalized_pos[i])-1)==1) return 1;
    }
    return 0;
}

int hit_on_right(struct blocks_state *bls, int dim_x) {
    struct active_block* ab = bls->active;
    for (int i = 0; i < 4; i++) {
        if (ab->pos[i][0] == dim_x - 1 || *(bls->finished_blocks+(ab->normalized_pos[i])+1)==1) return 1;
    }
    return 0;
}