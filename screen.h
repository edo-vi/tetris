//
// Created by edoardo on 25/07/18.
//

#ifndef TETRIS_SCREEN_H
#define TETRIS_SCREEN_H
#define SMALL_X 30
#define MEDIUM_X 40
#define LARGE_X 50
#define SMALL_Y 15
#define MEDIUM_Y 20
#define LARGE_Y 20

struct screen_state{
    int* active_board;
};

struct screen_options{
    char* border;
    int board_dim_x;
    int board_dim_y;
    int dimension;
};

void draw_screen_tetris(struct screen_options* sco, struct screen_state* scs);
void init_screen_tetris(struct screen_options* sco, struct screen_state* scs);

#endif //TETRIS_SCREEN_H
