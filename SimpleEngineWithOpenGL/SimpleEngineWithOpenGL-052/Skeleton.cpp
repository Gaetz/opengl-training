#include "Skeleton.h"

void Skeleton::setBones(const vector<Bone>& bonesP)
{
	bones = bonesP;
}

void Skeleton::computeGlobalInvBindPose()
{
	// Resize to number of bones, which automatically fills identity
	globalInvBindPoses.resize(getNbBones());

	// Step 1: Compute global bind pose for each bone

	// The global bind pose for root is just the local bind pose
	globalInvBindPoses[0] = bones[0].localBindPose.toMatrix();

	// Each remaining bone's global bind pose is its local pose
	// multiplied by the parent's global bind pose
	for (size_t i = 1; i < globalInvBindPoses.size(); i++)
	{
		Matrix4 localMat = bones[i].localBindPose.toMatrix();
		globalInvBindPoses[i] = localMat * globalInvBindPoses[bones[i].parent];
	}

	// Step 2: Invert
	for (size_t i = 0; i < globalInvBindPoses.size(); i++)
	{
		globalInvBindPoses[i].invert();
	}
}

void Skeleton::unload()
{

}

void Skeleton::setName(const string& nameP)
{
	name = nameP;
}
