//
// Created by edoardo on 25/07/18.
//
#include "screen.h"
#include "block.h"

#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

struct game_state{
    struct screen_options sco;
    struct screen_state scs;
    struct blocks_state bls;
};

void start_game(struct game_state* gs);
void init_board_state(struct screen_options* sco, struct screen_state* scs, struct blocks_state* bls);
void move_active_block_down(struct screen_options *sco, struct screen_state *sc);
void move_active_block_right(struct screen_options *sco, struct screen_state *scs);
#endif //TETRIS_GAME_H
