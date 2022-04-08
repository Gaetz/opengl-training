#include "Level.h"

array<array<TileContent, TRACK_COLS>, TRACK_ROWS> Level::grid { TileContent::Wall };

void Level::load() {
    for(auto& row : grid) {
        for(auto& col : row) {
            col = TileContent::Wall;
        }
    }
}

/*
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
*/
vector<Cube> Level::populateLevel() {
    vector<Cube> cubes;
    for(int row = 0; row < TRACK_ROWS; ++row) {
        for(int col = 0; col < TRACK_COLS; ++col) {
            if (grid[row][col] == TileContent::Wall) {
                Cube cube { Vector2 { static_cast<float>(col), static_cast<float>(row) }, GREY };
                cube.load();
                cube.updateTransform();
                cubes.push_back(cube);
            }
        }
    }
    return cubes;
}
