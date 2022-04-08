#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include "Cube.h"
#include "Constants.h"

#include <array>
#include <string>
#include <vector>

using std::array;
using std::string;
using std::vector;


enum class TileContent {
    Empty = 0,
    Wall
};

class Level {
public:
    void load();
    static array<array<TileContent, TRACK_COLS>, TRACK_ROWS> grid;
    vector<Cube> populateLevel();
private:
    //TileContent charToTile(char col);
};

#endif