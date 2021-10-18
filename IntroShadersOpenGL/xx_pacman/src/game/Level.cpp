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

vector<Cube> Level::populateStatic() {
    vector<Cube> cubes;
    for(int row = 0; row < LEVEL_HEIGHT; ++row) {
        for(int col = 0; col < LEVEL_WIDTH; ++col) {
            if (content[row][col] == TileContent::Wall) {
                Cube cube { Vector2 { static_cast<float>(col), static_cast<float>(row) }, GREY };
                cube.load();
                cubes.push_back(cube);
            }
        }
    }
    return cubes;
}