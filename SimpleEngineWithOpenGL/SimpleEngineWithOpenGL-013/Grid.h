#pragma once
#include "Actor.h"
#include "Tile.h"
#include <vector>
using std::vector;

class Grid : public Actor
{
public:
	Grid();

	void processClick(int x, int y);
	Tile& getStartTile();
	Tile& getEndTile();
	bool findPath(Tile& start, const Tile& goal);

private:
	void selectTile(size_t row, size_t col);
	void updatePathTiles(const Tile& start);

	class Tile* selectedTile;

	// 2D vector of tiles in grid
	vector<vector<class Tile*>> tiles;

	const size_t NB_ROWS = 7;
	const size_t NB_COLS = 16;
	const float TILESIZE = 64.0f;

	// Start y position of top left corner
	const float START_Y = 192.0f;


};

