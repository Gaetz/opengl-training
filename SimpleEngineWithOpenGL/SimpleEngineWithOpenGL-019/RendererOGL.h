#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "Shader.h"

class RendererOGL : public IRenderer
{
public:
	RendererOGL();
	virtual ~RendererOGL();
	RendererOGL(const RendererOGL&) = delete;
	RendererOGL& operator=(const RendererOGL&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void drawSprite(Actor& actor, const class Texture& tex, struct Rectangle srcRect, Vector2 origin, Flip flip) const;
	void endDraw();
	void close();
	IRenderer::Type type() { return Type::OGL; }


private:
	Window* window;
	VertexArray* vertexArray;
	Shader* shader;
	Matrix4 viewProj;
};

