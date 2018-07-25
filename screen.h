//
// Created by edoardo on 25/07/18.
//

#ifndef TETRIS_SCREEN_H
#define TETRIS_SCREEN_H

struct screen_state{
    char* border;
    int board_dim_x;
    int board_dim_y;
};
void draw_screen_tetris(struct screen_state* sc);
void init_screen(struct screen_state* sc);
#endif //TETRIS_SCREEN_H
