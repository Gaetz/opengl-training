#pragma once
#include "Actor.h"
#include <vector>
#include "SpriteComponent.h"

class Tile : public Actor
{
public:
	friend class Grid;
	enum class TileState
	{
		Default,
		Path,
		Start,
		Base,
		Obstacle
	};

	Tile();
	Tile(const Tile&);
	Tile operator=(const Tile&);

	TileState getTileState() const { return tileState; }
	const Tile* getParent() const { return parent; }

	void setTileState(TileState tileStateP);

	void toggleSelect();


private:
	void updateTexture();
	SpriteComponent* sprite;
	TileState tileState;
	bool isSelected;

	// Pathfinding
	std::vector<Tile*> adjacentTiles;
	Tile* parent;
	float f;
	float g;
	float h;
	bool isInOpenSet;
	bool isInClosedSet;
	bool isBlocked;

};

