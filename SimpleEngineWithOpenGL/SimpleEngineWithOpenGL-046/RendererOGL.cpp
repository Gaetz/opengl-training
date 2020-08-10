#include "RendererOGL.h"
#include "Rectangle.h"
#include "Assets.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Log.h"
#include "Game.h"
#include "UIScreen.h"
#include "SkeletalMeshComponent.h"

#include <GL/glew.h>
#include <SDL_image.h>

RendererOGL::RendererOGL():
	window(nullptr),
	context(nullptr),
	spriteVertexArray(nullptr),
	spriteViewProj(Matrix4::createSimpleViewProj(WINDOW_WIDTH, WINDOW_HEIGHT)),
	view(Matrix4::createLookAt(Vector3::zero, Vector3::unitX, Vector3::unitZ)),
	projection(Matrix4::createPerspectiveFOV(Maths::toRadians(70.0f), WINDOW_WIDTH, WINDOW_HEIGHT, 10.0f, 10000.0f)),
	ambientLight(Vector3(1.0f, 1.0f, 1.0f)),
	dirLight({ Vector3::zero, Vector3::zero, Vector3::zero })
{
}

RendererOGL::~RendererOGL()
{
}

bool RendererOGL::initialize(Window& windowP)
{
	window = &windowP;

	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// Depth buffering
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	// OpenGL Context
	context = SDL_GL_CreateContext(windowP.getSDLWindow());

	// GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Log::error(LogCategory::Video, "Failed to initialize GLEW.");
		return false;
	}

	// On some platforms, GLEW will emit a benign error code, so clear it
	glGetError();

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::error(LogCategory::Video, "Unable to initialize SDL_image");
		return false;
	}

	spriteVertexArray = new VertexArray(spriteVertices, 4, VertexArrayLayout::PosNormTex, indices, 6);

	// Create render target for mirror
	if (!createMirrorTarget())
	{
		Log::error(LogCategory::Video, "Failed to create render target for mirror.");
		return false;
	}


    return true;
}

void RendererOGL::beginDraw()
{
	glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
}

void RendererOGL::draw()
{
	draw3dScene(mirrorBuffer, mirrorView, projection, 0.25f);
	draw3dScene(0, view, projection);
	drawSprites();
	drawUI();
}

void RendererOGL::endDraw()
{
	SDL_GL_SwapWindow(window->getSDLWindow());
}

void RendererOGL::close()
{
	// Get rid of any render target textures, if they exist
	if (mirrorTexture != nullptr)
	{
		glDeleteFramebuffers(1, &mirrorBuffer);
		mirrorTexture->unload();
		delete mirrorTexture;
	}
	delete spriteVertexArray;
	SDL_GL_DeleteContext(context);
}

Vector3 RendererOGL::unproject(const Vector3& screenPoint) const
{
	// Convert screenPoint to device coordinates (between -1 and +1)
	Vector3 deviceCoord = screenPoint;
	deviceCoord.x /= WINDOW_WIDTH * 0.5f;
	deviceCoord.y /= WINDOW_HEIGHT * 0.5f;

	// Transform vector by unprojection matrix
	Matrix4 unprojection = view * projection;
	unprojection.invert();
	return Vector3::transformWithPerspDiv(deviceCoord, unprojection);
}

void RendererOGL::getScreenDirection(Vector3& outStart, Vector3& outDir) const
{
	// Get start point (in center of screen on near plane)
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	outStart = unproject(screenPoint);
	// Get end point (in center of screen, between near and far)
	screenPoint.z = 0.9f;
	Vector3 end = unproject(screenPoint);
	// Get direction vector
	outDir = end - outStart;
	outDir.normalize();
}

bool RendererOGL::createMirrorTarget()
{
	int width = static_cast<int>(WINDOW_WIDTH) / 4;
	int height = static_cast<int>(WINDOW_HEIGHT) / 4;

	// Generate a frame buffer for the mirror texture
	glGenFramebuffers(1, &mirrorBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, mirrorBuffer);

	// Create the texture we'll use for rendering
	mirrorTexture = new Texture();
	mirrorTexture->createForRendering(width, height, GL_RGB);

	// Add a depth buffer to this target
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	// Attach mirror texture as the output target for the frame buffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mirrorTexture->getTextureID(), 0);

	// Set the list of buffers to draw to for this frame buffer
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	// Make sure everything worked
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		// If it didn't work, delete the framebuffer,
		// unload/delete the texture and return false
		glDeleteFramebuffers(1, &mirrorBuffer);
		mirrorTexture->unload();
		delete mirrorTexture;
		mirrorTexture = nullptr;
		return false;
	}
	return true;
}

void RendererOGL::draw3dScene(unsigned int frameBuffer, const Matrix4& view, const Matrix4& proj, float viewportScale)
{
	// Set the current frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	// Set viewport size based on scale
	glViewport(0, 0,
		static_cast<int>(WINDOW_WIDTH * viewportScale),
		static_cast<int>(WINDOW_HEIGHT * viewportScale)
	);

	// Clear the color and depth buffer
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawMeshes(view);
}

void RendererOGL::setMirrorView(const Matrix4& view)
{
	mirrorView = view;
}

void RendererOGL::drawMeshes(const Matrix4& currentView)
{
	// Enable depth buffering/disable alpha blend
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	Matrix4 viewProj = currentView * projection;

	// Draw classic meshes
	Shader& shader = Assets::getShader("Phong");
	shader.use();
	// Update view-projection matrix
	shader.setMatrix4("uViewProj", viewProj);
	// Lights
	setLightUniforms(shader);
	// Draw
	for (auto mc : meshes)
	{
		if (mc->getVisible())
		{
			mc->draw(Assets::getShader("Phong"));
		}
	}

	// Draw skeletal meshes
	Shader& skinnedShader = Assets::getShader("Skinned");
	skinnedShader.use();
	skinnedShader.setMatrix4("uViewProj", viewProj);
	setLightUniforms(skinnedShader);
	for (auto sk : skMeshes)
	{
		if (sk->getVisible())
		{
			sk->draw(skinnedShader);
		}
	}
}

void RendererOGL::addSprite(SpriteComponent* sprite)
{
	// Insert the sprite at the right place in function of drawOrder
	int spriteDrawOrder = sprite->getDrawOrder();
	auto iter = begin(sprites);
	for (; iter != end(sprites); ++iter)
	{
		if (spriteDrawOrder < (*iter)->getDrawOrder()) break;
	}
	sprites.insert(iter, sprite);
}

void RendererOGL::removeSprite(SpriteComponent* sprite)
{
	auto iter = std::find(begin(sprites), end(sprites), sprite);
	sprites.erase(iter);
}

void RendererOGL::drawSprites()
{
	glDisable(GL_DEPTH_TEST);
	// Enable alpha blending on the color buffer
	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// Active shader and vertex array
	Shader& spriteShader = Assets::getShader("Sprite");
	spriteShader.use();
	spriteShader.setMatrix4("uViewProj", spriteViewProj);
	spriteVertexArray->setActive();

	for (auto sprite : sprites)
	{
		if (sprite->getVisible())
		{
			sprite->draw(*this);
		}
	}
}

void RendererOGL::drawUI()
{
	for (auto ui : Game::instance().getUIStack())
	{
		ui->draw(Assets::getShader("Sprite"));
	}
}

void RendererOGL::drawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const
{
	Matrix4 scaleMat = Matrix4::createScale((float)tex.getWidth(), (float)tex.getHeight(), 1.0f);
	Matrix4 world = scaleMat * actor.getWorldTransform();
	Assets::getShader("Sprite").setMatrix4("uWorldTransform", world);
	tex.setActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void RendererOGL::addMesh(MeshComponent* mesh)
{
	if (mesh->getSkeletal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(mesh);
		skMeshes.emplace_back(sk);
	}
	else
	{
		meshes.emplace_back(mesh);
	}
}

void RendererOGL::removeMesh(MeshComponent* mesh)
{
	if (mesh->getSkeletal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(mesh);
		auto iter = std::find(skMeshes.begin(), skMeshes.end(), sk);
		skMeshes.erase(iter);
	}
	else
	{
		auto iter = std::find(begin(meshes), end(meshes), mesh);
		meshes.erase(iter);
	}
}

void RendererOGL::setViewMatrix(const Matrix4& viewP)
{
	view = viewP;
}

void RendererOGL::setLightUniforms(Shader& shader)
{
	// Camera position is from inverted view
	Matrix4 invertedView = view;
	invertedView.invert();
	shader.setVector3f("uCameraPos", invertedView.getTranslation());
	// Ambient
	shader.setVector3f("uAmbientLight", ambientLight);
	// Directional light
	shader.setVector3f("uDirLight.direction", dirLight.direction);
	shader.setVector3f("uDirLight.diffuseColor", dirLight.diffuseColor);
	shader.setVector3f("uDirLight.specColor", dirLight.specColor);

}

void RendererOGL::setAmbientLight(const Vector3& ambientP)
{
	ambientLight = ambientP;
}
