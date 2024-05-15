#include "Tile.h"

tile::tile () : tile_value(0) {
    tile_isRevealed = false;
}

int tile::get_tileValue() const{
    return tile_value;
}

void tile::set_tileValue(int value){
    tile_value = value;
}

void tile::set_tileIsRevealed() {
    tile_isRevealed = true;
}

