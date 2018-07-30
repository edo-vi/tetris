//
// Created by edoardo on 25/07/18.
//

#ifndef TETRIS_SCREEN_H
#define TETRIS_SCREEN_H

#define SMALL_X 20   //20
#define MEDIUM_X 40
#define LARGE_X 50
#define SMALL_Y 12 // 15
#define MEDIUM_Y 20
#define LARGE_Y 20 // 20


#include "structs.h"


void draw_screen_tetris(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls);
void init_screen_tetris(struct screen_options* sco, struct screen_state* scs);
void clear_active_board(int previous_pos[4], struct screen_state* scs);
void clear_completed_blocks(int* previous_complete_blocks, struct screen_state* scs, int dimension);
#endif //TETRIS_SCREEN_H
