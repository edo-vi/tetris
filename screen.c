//
// Created by edoardo on 25/07/18.
//

#include <stdio.h>
#include "screen.h"


void draw_screen_tetris(struct screen_state* sc) {
    for (int i=0;i<sc->board_dim_y;i++) {
        printf("%s",sc->border);
        for (int j=0; j<sc->board_dim_x;j++) {
           i==sc->board_dim_y-1? printf("_") : printf(" ");
        }
        printf("%s\n",sc->border);
    }
}
void init_screen_tetris(struct screen_state* sc) {
    char dimension;
    do {
        printf("\nScegli dimensione dello schermo\n\n Piccolo     Normale     Grande\n    1           2          3\n");
        scanf(" %c",&dimension);
    } while(dimension<'1' ||dimension>'3');
    if (dimension=='1') {
        sc->board_dim_x=30;
        sc->board_dim_y=15;
    } else if (dimension=='2') {
        sc->board_dim_x=40;
        sc->board_dim_y=20;
    } else {
        sc->board_dim_x=50;
        sc->board_dim_y=20;
    }
    sc->border="||";

}