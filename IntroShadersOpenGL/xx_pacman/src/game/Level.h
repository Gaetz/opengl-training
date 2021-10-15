#ifndef LEVEL_H
#define LEVEL_H

#include <array>
using std::array;

#include <string>
using std::string;


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
    static array<array<TileContent, 19>, 20> content;
private:
};

#endif