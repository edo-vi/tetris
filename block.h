//
// Created by edoardo on 26/07/18.
//

#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include "structs.h"

struct block* create_random_block(void);
void collocate_block_initial_position(struct blocks_state* bls, struct screen_options* sco);
void convert_pos_to_normalized_pos(int pos[4][2], int normalized_pos[4], int pos_x);
void init_completed_blocks(struct screen_options *sco, struct blocks_state *bls);
void change_active_block_form(struct screen_options *sco, struct screen_state *scs, struct blocks_state *bls);
void end_active_block_life(struct blocks_state *bls, struct screen_options *sco, struct screen_state *scs, int* loss);
void free_active_block(struct active_block *acb);
#endif //TETRIS_BLOCK_H
