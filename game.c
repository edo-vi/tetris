//
// Created by edoardo on 25/07/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "screen.h"
#include "block.h"

void sort(int arr[4]);

void start_game(struct game_state* gs) {
    const char martini[5] = {	0xF0, 0x9F, 0x8E, 0xAE, '\0'};
    printf("\n*********************************\n***          TETRIS           ***\n*********************************\n\n"
           "by %s Edoardo Zorzi %s 06/09/2018\n\n\n"
           " in ogni momento, premi 'e' per\n   uscire e le frecciette per\n       muovere i blocchi\n___________________"
           "____________\n", martini, martini);
    init_screen_tetris(&gs->sco,&gs->scs);
    init_board_state(&gs->sco,&gs->scs, &gs->bls);
    init_completed_blocks(&gs->sco, &gs->bls); //all zero here, obviously
    gs->loss=0;
}

void init_board_state(struct screen_options* sco, struct screen_state* scs, struct blocks_state* bls) {
    collocate_block_initial_position(bls,sco);
}

void map_active_state_to_board(struct screen_state* scs, int active_block_position[4]) {
    for (int i=0;i<4;i++) {
        *(scs->active_board+active_block_position[i])=1;
    }
}
void map_completed_blocks_to_board(struct screen_state* scs, struct blocks_state* bls) {
    for (int i=0;i<bls->dimension_completed_blocks;i++) {
        if((*(bls->completed_blocks+i))==1) {
            *(scs->active_board+i)=1;
        }
    }

}
void move_active_block_down(struct game_state *gs) {
    struct blocks_state* bls = &(gs->bls);
    struct screen_options* sco = &(gs->sco);
    struct screen_state* scs = &(gs->scs);

    if (hit_on_bottom(bls, sco->board_dim_y, sco->board_dim_x)) {
        end_active_block_life(bls, sco, scs, &(gs->loss)); // if is near bottom
        return;
    }
    clear_active_board(bls->active->normalized_pos,scs);
    for(int i=0;i<4;i++) {
        bls->active->pos[i][1]++;
    }
    convert_pos_to_normalized_pos(bls->active->pos, bls->active->normalized_pos, sco->board_dim_x);

}
void move_active_block_right(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls) {
    if (hit_on_right(bls, sco->board_dim_x)) return;
    clear_active_board(bls->active->normalized_pos,scs);
    for(int i=0;i<4;i++) {
        bls->active->pos[i][0]++;
    }
    convert_pos_to_normalized_pos(bls->active->pos, bls->active->normalized_pos, sco->board_dim_x);

}

void move_active_block_left(struct screen_options *sco, struct screen_state *scs, struct blocks_state* bls) {
    if (hit_on_left(bls)) return;
    clear_active_board(bls->active->normalized_pos,scs);
    for(int i=0;i<4;i++) {
        bls->active->pos[i][0]--;
    }
    convert_pos_to_normalized_pos(bls->active->pos, bls->active->normalized_pos, sco->board_dim_x);

}

int hit_on_bottom(struct blocks_state *bls, int dim_y, int dim_x) {
    struct active_block* ab = bls->active;
    for (int i=0;i<4;i++) {
        // if block position is on last line, or the pos just below are occupied by finished blocks
        if (ab->pos[i][1]==dim_y-1 || *(bls->completed_blocks+(ab->normalized_pos[i]+dim_x))==1) return 1;
    }
    return 0;
};

int hit_on_left(struct blocks_state *bls) {
    struct active_block* ab = bls->active;
    for (int i = 0; i < 4; i++) {
        if (ab->pos[i][0] == 0 || *(bls->completed_blocks+(ab->normalized_pos[i])-1)==1) return 1;
    }
    return 0;
}

int hit_on_right(struct blocks_state *bls, int dim_x) {
    struct active_block* ab = bls->active;
    for (int i = 0; i < 4; i++) {
        if (ab->pos[i][0] == dim_x - 1 || *(bls->completed_blocks+(ab->normalized_pos[i])+1)==1) return 1;
    }
    return 0;
}

void clear_line_if_completed(struct blocks_state *bls, struct screen_options *sco, struct screen_state *scs) {
    //create array of first column position of each row that must be checked
    int starts[4];
    for (int i =0; i<4;i++) {
        starts[i]=((bls->active->normalized_pos[i]/sco->board_dim_x)*sco->board_dim_x);
    }

    //we must order them descending and remove duplicates
    for (int i=0;i<4;i++) {
        for(int j=i+1;j<4;j++) {
            if(starts[i]==starts[j]) starts[i]=-1;
        }
    }
    sort(starts);

    // check, from bottom to top, if a line is completed (starts contains the starting position of the rows,
    // from top to bottom
    for (int i = 3; i>=0; i-- ) {
        if (starts[i]<=0) break; // we don't consider invalid starting values, here we break
                                 // because if we hit -1 then all the others will be the same

        int iscompleted = 1;
        for (int j = starts[i]; j< starts[i]+sco->board_dim_x; j++) {
            if (*(bls->completed_blocks+j)==0) {
                iscompleted=0;
                break;
            }
        }
        if (!iscompleted) {
            continue;
        }
        else {
            clear_completed_blocks(bls->completed_blocks,scs,bls->dimension_completed_blocks);
            // we increment next starts by dim_x because we lower all blocks by one row, so we must start checking again
            // in that row (only if we are not at he first element of the array and if that element is not -1
            for (int j = i; j>0; j--) {
                if (starts[j-1]>=0) starts[j-1]+=sco->board_dim_x;
            }
            for (int k = starts[i]; k< starts[i]+sco->board_dim_x; k++) {
                *(bls->completed_blocks+k)=0;
            }
            for (int l=starts[i]-1;l>0;l--) {
                if (*(bls->completed_blocks+l)==1) {
                    *(bls->completed_blocks+l)=0;
                    *(bls->completed_blocks+l+sco->board_dim_x)=1;
                }
            }

        }
    }
}
//simple selection sort
void sort(int arr[4]) {
    for(int i = 2;i>=0;i--) {
        int j = i;
        while(j+1<4 && arr[j]>arr[j+1]) {
            int tmp=arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=tmp;
            j++;
        }
    }
}