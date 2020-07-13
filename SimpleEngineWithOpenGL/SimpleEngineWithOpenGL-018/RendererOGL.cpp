#include "RendererOGL.h"
#include <GL/glew.h>
#include "Rectangle.h"
#include "Vector2.h"
#include "ResourceManager.h"

RendererOGL::RendererOGL() : window(nullptr), vertexArray(nullptr), shader(nullptr)
{
}

RendererOGL::~RendererOGL()
{
}

bool RendererOGL::initialize(Window& windowP)
{
	window = &windowP;
	vertexArray = new VertexArray(vertices, 4, indices, 6);
	shader = &ResourceManager::getShader("Basic");
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
	vertexArray->setActive();
}

void RendererOGL::drawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const
{
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
