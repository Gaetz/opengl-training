#include "Grid.h"
#include "Enemy.h"
#include <algorithm>
#include "Tower.h"

Grid::Grid() : Actor(), selectedTile(nullptr), nextEnemyTimer(0)
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
			if (i >= NB_ROWS / 2 - 1 && i <= NB_ROWS / 2 + 1 && j >= NB_COLS / 2 - 1 && j <= NB_COLS / 2 + 1)
			{
				tiles[i][j]->setTileState(Tile::TileState::Obstacle);
			} 
			else
			{
				tiles[i][j]->setTileState(Tile::TileState::Default);
			}
		}
	}

	// Set start/end tiles
	getStartTile().setTileState(Tile::TileState::Start);
	getEndTile().setTileState(Tile::TileState::Base);

	// Fill adjacent tiles
	for (size_t i = 0; i < NB_ROWS; i++)
	{
		for (size_t j = 0; j < NB_COLS; j++)
		{
			if (i > 0)
			{
				tiles[i][j]->adjacentTiles.push_back(tiles[i - 1][j]);
			}
			if (i < NB_ROWS - 1)
			{
				tiles[i][j]->adjacentTiles.push_back(tiles[i + 1][j]);
			}
			if (j > 0)
			{
				tiles[i][j]->adjacentTiles.push_back(tiles[i][j - 1]);
			}
			if (j < NB_COLS - 1)
			{
				tiles[i][j]->adjacentTiles.push_back(tiles[i][j + 1]);
			}
		}
	}

	// Find path in reverse
	findPath(getEndTile(), getStartTile());
	updatePathTiles(getStartTile());
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

bool Grid::findPath(Tile& start, const Tile& goal)
{
	for (auto i = 0; i < NB_ROWS; i++)
	{
		for (auto j = 0; j < NB_COLS; j++)
		{
			tiles[i][j]->g = 0.0f;
			tiles[i][j]->isInOpenSet = false;
			tiles[i][j]->isInClosedSet = false;
		}
	}
	vector<Tile*> openSet;
	Tile* current = &start;
	current->isInClosedSet = true;

	do
	{
		// Add adjacent nodes to open set
		for (Tile* neighbour : current->adjacentTiles)
		{
			if (neighbour->isBlocked)
			{
				continue;
			}

			// Only check a node if it is not in the closed set
			if (!neighbour->isInClosedSet)
			{
				if (!neighbour->isInOpenSet)
				{
					// Not in open set so set parent
					neighbour->parent = current;
					neighbour->h = (neighbour->getPosition() - goal.getPosition()).length();
					// g is the parent's g + cost of traversing edge
					neighbour->g = current->g + TILESIZE;
					neighbour->f = neighbour->g + neighbour->h;
					openSet.emplace_back(neighbour);
					neighbour->isInOpenSet = true;
				}
				else 
				{
					// Compute g cost if current become the parent
					float newG = current->g + TILESIZE;
					if (newG < neighbour->g)
					{
						// Adopt this node
						neighbour->parent = current;
						neighbour->g = newG;
						// f change because g change
						neighbour->f = neighbour->g + neighbour->h;
					}
				}
			}
		}
		// If open set is empty, all possible paths are exhausted
		if (openSet.empty())
		{
			break;
		}
		// Find lowest cost node in open set
		auto iter = std::min_element(begin(openSet), end(openSet), [](Tile* a, Tile* b) { return a->f < b->f; });
		// Set to current and move from open to closed set
		current = *iter;
		openSet.erase(iter);
		current->isInOpenSet = false;
		current->isInClosedSet = true;
	} while (current != &goal);
	
	return (current == &goal);
}

void Grid::updateActor(float dt)
{
	Actor::updateActor(dt);
	nextEnemyTimer -= dt;
	if (nextEnemyTimer <= 0.0f)
	{
		new Enemy();
		nextEnemyTimer += TIME_BETWEEN_ENEMIES;
	}
}

void Grid::buildTower()
{
	if (selectedTile && !selectedTile->isBlocked)
	{
		selectedTile->isBlocked = true;
		if (findPath(getEndTile(), getStartTile()))
		{
			Tower* t = new Tower();
			t->setPosition(selectedTile->getPosition());
		}
		else
		{
			// This tower would block the path, so don't allow build
			selectedTile->isBlocked = false;
			findPath(getEndTile(), getStartTile());
		}
		updatePathTiles(getStartTile());
	}
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

void Grid::updatePathTiles(const Tile& start)
{
	Tile* t = start.parent;
	while (t != &getEndTile())
	{
		t->setTileState(Tile::TileState::Path);
		t = t->parent;
	}
}
