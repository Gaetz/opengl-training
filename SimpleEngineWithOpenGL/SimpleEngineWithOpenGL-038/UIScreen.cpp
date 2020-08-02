#include "UIScreen.h"
#include "Texture.h"
#include "Font.h"
#include "Assets.h"
#include "Game.h"

UIScreen::UIScreen() :
	title(nullptr),
	titlePosition(0.0f, 300.0f),
	state(UIState::Active),
	font(Assets::getFont("Carlito"))
{
	Game::instance().pushUI(this);
}

UIScreen::~UIScreen()
{
	if (title)
	{
		title->unload();
		delete title;
	}
}

void UIScreen::setTitle(const string& titleP, const Vector3& color, int pointSize)
{
	if (title)
	{
		title->unload();
		delete title;
		title = nullptr;
	}
	title = font.renderText(titleP, color, pointSize);
}

void UIScreen::update(float deltaTime)
{
}

void UIScreen::draw(Shader& shader)
{
	if (title)
	{
		drawTexture(shader, title, titlePosition);
	}
}

void UIScreen::processInput(const InputState& inputState)
{
}

void UIScreen::close()
{
	state = UIState::Closing;
}

void UIScreen::drawTexture(Shader& shader, Texture* texture, const Vector2& offset, float scale)
{
	Matrix4 scaleMat = Matrix4::createScale(
		static_cast<float>(texture->getWidth()) * scale,
		static_cast<float>(texture->getHeight()) * scale,
		1.0f);
	Matrix4 transMat = Matrix4::createTranslation(Vector3(offset.x, offset.y, 0.0f));
	Matrix4 world = scaleMat * transMat;
	shader.setMatrix4("uWorldTransform", world);
	texture->setActive();
	// Draw quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
