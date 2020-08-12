#include "GBuffer.h"
#include <GL/glew.h>
#include "Texture.h"

GBuffer::GBuffer() : bufferID(0)
{
}

GBuffer::~GBuffer()
{
}

bool GBuffer::create(int width, int height)
{
	// Create the framebuffer object
	glGenFramebuffers(1, &bufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);

	// Add a depth buffer to this target
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	const int nbGbufferTextures = static_cast<int>(GBufferType::NB_GBUFFER_TEXTURES);
	// Create textures for each output in the G-buffer
	for (int i = 0; i < nbGbufferTextures; i++)
	{
		Texture* tex = new Texture();
		// We want three 32-bit float components for each texture
		tex->createForRendering(width, height, GL_RGB32F);
		textures.emplace_back(tex);
		// Attach this texture to a color output
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,	tex->getTextureID(), 0);
	}

	// Create a vector of the color attachments
	std::vector<GLenum> attachments;
	for (int i = 0; i < nbGbufferTextures; i++)
	{
		attachments.emplace_back(GL_COLOR_ATTACHMENT0 + i);
	}

	// Set the list of buffers to draw to
	glDrawBuffers(static_cast<GLsizei>(attachments.size()),	attachments.data());

	// Make sure everything worked
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		destroy();
		return false;
	}

	return true;
}

void GBuffer::destroy()
{
	glDeleteFramebuffers(1, &bufferID);
	for (Texture* t : textures)
	{
		t->unload();
		delete t;
	}
}

Texture* GBuffer::getTexture(GBufferType type)
{
	if (textures.size() > 0)
	{
		return textures[static_cast<int>(type)];
	}
	else
	{
		return nullptr;
	}
}

void GBuffer::setTexturesActive()
{
	for (int i = 0; i < static_cast<int>(GBufferType::NB_GBUFFER_TEXTURES); i++)
	{
		textures[i]->setActive(i);
	}
}
