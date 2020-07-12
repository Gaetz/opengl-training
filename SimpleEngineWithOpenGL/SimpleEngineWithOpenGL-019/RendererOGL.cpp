#include "RendererOGL.h"
#include <GL/glew.h>
#include "Rectangle.h"
#include "ResourceManager.h"
#include "Actor.h"

RendererOGL::RendererOGL():
	window(nullptr),
	vertexArray(nullptr),
	shader(nullptr),
	viewProj(Matrix4::createSimpleViewProj(WINDOW_WIDTH, WINDOW_HEIGHT))
{
}

RendererOGL::~RendererOGL()
{
}

bool RendererOGL::initialize(Window& windowP)
{
	window = &windowP;
	vertexArray = new VertexArray(vertices, 4, indices, 6);
	shader = &ResourceManager::getShader("Transform");
    return true;
}

void RendererOGL::beginDraw()
{
	glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Enable alpha blending on the color buffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Active shader and vertex array
	shader->use();
	shader->setMatrix4("uViewProj", viewProj);
	vertexArray->setActive();
}

void RendererOGL::drawSprite(Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const
{
	Matrix4 scaleMat = Matrix4::createScale((float)tex.getWidth(), (float)tex.getHeight(), 1.0f);
	Matrix4 world = scaleMat * actor.getWorldTransform();
	Matrix4 pixelTranslation = Matrix4::createTranslation(Vector3(-WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, 0.0f)); // Screen pixel coordinates
	shader->setMatrix4("uWorldTransform", world * pixelTranslation);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void RendererOGL::endDraw()
{
	SDL_GL_SwapWindow(window->getSDLWindow());
}

void RendererOGL::close()
{
	delete vertexArray;
}
