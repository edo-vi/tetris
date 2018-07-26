//
// Created by edoardo on 26/07/18.
//
#import "screen.h"

#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

struct block{
    enum {i,square,l,j,t,s,z} type;
    char style;
};

struct active_block{
    struct block* block;
    int pos[4][2];
    int normalized_pos[4];
};

struct blocks_state{
    struct active_block* active;
};
struct block* create_random_block(void);
void collocate_block_initial_position(struct blocks_state* bls, struct screen_options* sco);
void convert_pos_to_normalized_pos(int pos[4][2], int normalized_pos[4], int pos_x);
#endif //TETRIS_BLOCK_H
