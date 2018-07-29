//
// Created by edoardo on 25/07/18.
//

#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H


#include "structs.h"


void start_game(struct game_state* gs);
void init_board_state(struct screen_options* sco, struct screen_state* scs, struct blocks_state* bls);
void move_active_block_down(struct game_state *gs);
void move_active_block_right(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls);
void move_active_block_left(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls);
void map_active_state_to_board(struct screen_state* scs, int active_block_position[4]);
void map_completed_blocks_to_board(struct screen_state* scs, struct blocks_state* bls);
int hit_on_bottom(struct blocks_state *bls, int dim_y, int dim_x);
int hit_on_left(struct blocks_state *bls);
int hit_on_right(struct blocks_state *bls, int dim_x);
void clear_line_if_completed(struct blocks_state *bls, struct screen_options *sco, struct screen_state *scs);
#endif //TETRIS_GAME_H
