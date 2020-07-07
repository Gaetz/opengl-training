#pragma once
#include "Actor.h"
#include <vector>

class Grid : public Actor
{
public:
	Grid();

	void processClick(int x, int y);
	class Tile& getStartTile();
	class Tile& getEndTile();


private:
	void selectTile(size_t row, size_t col);

	class Tile* selectedTile;

	// 2D vector of tiles in grid
	std::vector<std::vector<class Tile*>> tiles;

	const size_t NB_ROWS = 7;
	const size_t NB_COLS = 16;

	// Start y position of top left corner
	const float START_Y = 192.0f;

	const float TILESIZE = 64.0f;

};

