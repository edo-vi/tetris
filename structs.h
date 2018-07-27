//
// Created by edoardo on 26/07/18.
//

#ifndef TETRIS_STRUCTS_H
#define TETRIS_STRUCTS_H


struct block{
    enum {i,square,l,j,t,s,z} type;
    char style;
    int form;
};

struct active_block{
    struct block* block;
    int pos[4][2];
    int normalized_pos[4];
};

struct blocks_state{
    struct active_block* active;
    int dimension_completed_blocks;
    int* completed_blocks;

};



struct screen_state{
    int* active_board;
};

struct screen_options{
    char* border;
    int board_dim_x;
    int board_dim_y;
    int dimension;
};
struct game_state{
    struct screen_options sco;
    struct screen_state scs;
    struct blocks_state bls;
};

#endif //TETRIS_STRUCTS_H
