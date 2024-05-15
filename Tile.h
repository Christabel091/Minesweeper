#ifndef TILE_H
#define TILE_H

#include<array>


class tile {
    int tile_value;
    bool tile_isRevealed;
public:
    tile();
    bool get_tileIsRevealed() const{
        return tile_isRevealed;
    }
    void set_tileIsRevealed();
    int get_tileValue() const;
    void set_tileValue(int );
};
#endif