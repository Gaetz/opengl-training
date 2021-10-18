#include "Level.h"

array<array<TileContent, LEVEL_WIDTH>, LEVEL_HEIGHT> Level::content {};

void Level::load(string path) {
    std::ifstream levelFile(path);
    string line;
    int row {0};
    for (string line; std::getline( levelFile, line ); ) {
        for(int col = 0; col < LEVEL_WIDTH; ++col) {
            content[row][col] = charToTile(line[col]);
        }
        ++row;
    }
}

TileContent Level::charToTile(char col) {
    switch (col)
    {
    case 'x':
        return TileContent::Wall;
    default:
        return TileContent::Empty;
    }
}
