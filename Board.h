#ifndef BOARD_H
#define BOARD_H


#include "Tile.h"
#include<array>

class Board {
    int mine_count;
    int height;
    int width;
    tile *board;
    int count;
    bool lost;

public:
    Board(int, int, int);
    bool is_valid_mine_placement(int row, int coln, int random_rowNum, int random_colnNum); 
    void place_mines(int, int);
    void update_count();
    void revealed_board();
    bool reveal_tile(int , int);
    bool have_won(int ,int);
    bool have_lost(int ,int);
    void recurse_tile(int, int);
    ~Board();
};

#endif