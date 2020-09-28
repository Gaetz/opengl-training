#include "BackgroundSpriteComponent.h"
#include "Actor.h"

BackgroundSpriteComponent::BackgroundSpriteComponent(Actor* ownerP, const vector<Texture*>& texturesP, int drawOrderP):
	SpriteComponent(ownerP, *texturesP[0], drawOrderP),
	scrollSpeed(0.0f),
	screenSize(Vector2(WINDOW_WIDTH, WINDOW_HEIGHT))
{
	setTextures(texturesP);
}

BackgroundSpriteComponent::~BackgroundSpriteComponent()
{
}

void BackgroundSpriteComponent::update(float dt)
{
	SpriteComponent::update(dt);
	for (auto& bg : textures)
	{
		bg.offset.x += scrollSpeed * dt;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		if (bg.offset.x < -screenSize.x)
		{
			bg.offset.x = (textures.size() - 1) * screenSize.x - 1;
		}
	}
}

void BackgroundSpriteComponent::draw(Renderer& renderer)
{
	// Draw each background texture
	for (auto& bg : textures)
	{
		owner.setPosition(Vector2(bg.offset.x, bg.offset.y));
		renderer.drawSprite(owner, bg.texture, Rectangle::nullRect, Vector2::zero, Renderer::Flip::None);
	}
}

void BackgroundSpriteComponent::setTextures(const vector<Texture*>& texturesP)
{
	int count = 0;
	for (auto tex : texturesP)
	{
		BGTexture temp { *tex, Vector2(count * screenSize.x, 0) }; 	// Each texture is screen width in offset
		textures.emplace_back(temp);
		count++;
	}
}

void BackgroundSpriteComponent::setScreenSize(const Vector2& screenSizeP)
{
	screenSize = screenSizeP;
}

void BackgroundSpriteComponent::setScrollSpeed(float scrollSpeedP)
{
	scrollSpeed = scrollSpeedP;
}
