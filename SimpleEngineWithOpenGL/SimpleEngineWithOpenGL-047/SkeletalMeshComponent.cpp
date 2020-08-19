#include "SkeletalMeshComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "Actor.h"
#include "Mesh.h"
#include "Skeleton.h"
#include "Animation.h"

SkeletalMeshComponent::SkeletalMeshComponent(Actor* owner):
	MeshComponent(owner, true),
	skeleton(nullptr),
	animation(nullptr),
	animPlayRate(1.0f),
	animTime(0.0f)
{
}

void SkeletalMeshComponent::setSkeleton(const Skeleton& skeletonP)
{
	skeleton = &skeletonP;
}

void SkeletalMeshComponent::update(float dt)
{
	if (animation && skeleton)
	{
		animTime += dt * animPlayRate;
		// Wrap around anim time if past duration
		while (animTime > animation->getDuration())
		{
			animTime -= animation->getDuration();
		}

		// Recompute matrix palette
		computeMatrixPalette();
	}
}

void SkeletalMeshComponent::draw(Shader& shader)
{
	if (mesh)
	{
		// Set the world transform
		shader.setMatrix4("uWorldTransform", owner.getWorldTransform());
		// Set the matrix palette
		shader.setMatrix4Multiple("uMatrixPalette", &palette.entry[0], MAX_SKELETON_BONES);
		// Set specular power
		shader.setFloat("uSpecPower", mesh->getSpecularPower());
		// Set the active texture
		Texture* t = mesh->getTexture(textureIndex);
		if (t)
		{
			t->setActive();
		}
		// Set the mesh's vertex array as active
		VertexArray* va = mesh->getVertexArray();
		va->setActive();
		// Draw
		glDrawElements(GL_TRIANGLES, va->getNbIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

float SkeletalMeshComponent::playAnimation(const Animation* anim, float playRate)
{
	animation = anim;
	animTime = 0.0f;
	animPlayRate = playRate;
	if (!animation) {
		return 0.0f;
	}

	computeMatrixPalette();
	return animation->getDuration();
}

void SkeletalMeshComponent::computeMatrixPalette()
{
	const vector<Matrix4>& globalInvBindPoses = skeleton->getGlobalInvBindPoses();
	std::vector<Matrix4> currentPoses;
	animation->getGlobalPoseAtTime(currentPoses, skeleton, animTime);

	// Setup the palette for each bone
	for (size_t i = 0; i < skeleton->getNbBones(); i++)
	{
		// Global inverse bind pose matrix times current pose matrix
		palette.entry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}
