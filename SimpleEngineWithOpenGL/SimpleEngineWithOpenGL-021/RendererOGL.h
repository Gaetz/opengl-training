#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include <vector>

class RendererOGL : public IRenderer
{
public:
	RendererOGL();
	virtual ~RendererOGL();
	RendererOGL(const RendererOGL&) = delete;
	RendererOGL& operator=(const RendererOGL&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void draw();
	void drawSprite(const Actor& actor, const class Texture& tex, struct Rectangle srcRect, Vector2 origin, Flip flip) const;
	void endDraw();
	void close();
	IRenderer::Type type() { return Type::OGL; }

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);

private:
	Window* window;
	VertexArray* vertexArray;
	Shader* shader;
	Matrix4 viewProj;

	std::vector<class SpriteComponent*> sprites;

};

