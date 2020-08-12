#pragma once
#include <vector>
using std::vector;

enum class GBufferType
{
	Diffuse = 0,
	Normal,
	WorldPos,
	NB_GBUFFER_TEXTURES
};

class GBuffer
{
public:
	GBuffer(); 
	~GBuffer();

	bool create(int width, int height);
	void destroy();

	unsigned int getBufferID() const { return bufferID; }
	class Texture* getTexture(GBufferType type);
	void setTexturesActive();

private:
	vector<class Texture*> textures;
	unsigned int bufferID;
};

