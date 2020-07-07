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
		Base
	};

	Tile();

	TileState getTileState() const { return tileState; }
	void setTileState(TileState tileStateP);

	void toggleSelect();


private:
	void updateTexture();
	SpriteComponent* sprite;
	TileState tileState;
	bool isSelected;

};

