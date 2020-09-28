#include "Tile.h"
#include "Assets.h"

Tile::Tile() : 
	Actor(), 
	sprite(nullptr),
	tileState(TileState::Default),
	isSelected(false)
{
	sprite = new SpriteComponent(this, Assets::getTexture("TileBrown"));
}

void Tile::setTileState(TileState tileStateP)
{
	tileState = tileStateP;
	updateTexture();
}

void Tile::toggleSelect()
{
	isSelected = !isSelected;
	updateTexture();
}

void Tile::updateTexture()
{
	std::string text;
	switch (tileState)
	{
	case TileState::Start:
		text = "TileTan";
		break;
	case TileState::Base:
		text = "TileGreen";
		break;
	case TileState::Path:
		if (isSelected)
			text = "TileGreySelected";
		else
			text = "TileGrey";
		break;
	case TileState::Default:
	default:
		if (isSelected)
			text = "TileBrownSelected";
		else
			text = "TileBrown";
		break;
	}
	sprite->setTexture(Assets::getTexture(text));
}
