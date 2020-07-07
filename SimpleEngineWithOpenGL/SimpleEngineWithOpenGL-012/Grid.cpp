#include "Grid.h"
#include "Tile.h"

Grid::Grid() : Actor(), selectedTile(nullptr)
{
	// 7 rows, 16 columns
	tiles.resize(NB_ROWS);
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i].resize(NB_COLS);
	}

	// Create tiles
	for (size_t i = 0; i < NB_ROWS; i++)
	{
		for (size_t j = 0; j < NB_COLS; j++)
		{
			tiles[i][j] = new Tile();
			tiles[i][j]->setPosition(Vector2(TILESIZE / 2.0f + j * TILESIZE, START_Y + i * TILESIZE));
			tiles[i][j]->setTileState(Tile::TileState::Default);
		}
	}

	// Set start/end tiles
	getStartTile().setTileState(Tile::TileState::Start);
	getEndTile().setTileState(Tile::TileState::Base);
}

void Grid::processClick(int x, int y)
{
	y -= static_cast<int>(START_Y - TILESIZE / 2);
	if (y >= 0)
	{
		x /= static_cast<int>(TILESIZE);
		y /= static_cast<int>(TILESIZE);
		if (x >= 0 && x < static_cast<int>(NB_COLS) && y >= 0 && y < static_cast<int>(NB_ROWS))
		{
			selectTile(y, x);
		}
	}
}

Tile& Grid::getStartTile()
{
	return *tiles[3][0];
}

Tile& Grid::getEndTile()
{
	return *tiles[3][15];
}

void Grid::selectTile(size_t row, size_t col)
{
	// Make sure it's a valid selection
	Tile::TileState state = tiles[row][col]->getTileState();
	if (state != Tile::TileState::Start && state != Tile::TileState::Base)
	{
		// Deselect previous one
		if (selectedTile)
		{
			selectedTile->toggleSelect();
		}
		selectedTile = tiles[row][col];
		selectedTile->toggleSelect();
	}
}
