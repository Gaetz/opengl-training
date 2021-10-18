#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include "Cube.h"

#include <array>
using std::array;

#include <string>
using std::string;

#include <vector>
using std::vector;



constexpr int LEVEL_WIDTH { 19 };
constexpr int LEVEL_HEIGHT { 20 };

enum class TileContent {
    Empty = 0,
    Wall,
    Pacman
};

class Level {
public:
    void load(string path);
    static array<array<TileContent, LEVEL_WIDTH>, LEVEL_HEIGHT> content;
    vector<Cube> populateStatic();
private:
    TileContent charToTile(char col);
};

#endif