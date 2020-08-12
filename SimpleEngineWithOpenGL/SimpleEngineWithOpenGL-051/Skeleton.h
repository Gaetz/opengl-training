#pragma once
#include "BoneTransform.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

const size_t MAX_SKELETON_BONES = 96;

class Skeleton
{
public:
	struct Bone
	{
		BoneTransform localBindPose;
		string name;
		int parent;
	};

	size_t getNbBones() const { return bones.size(); }
	const Bone& getBone(size_t index) const { return bones[index]; }
	const vector<Bone>& getBones() const { return bones; }
	const vector<Matrix4>& getGlobalInvBindPoses() const { return globalInvBindPoses; }

	void setBones(const vector<Bone>& bonesP);

	// Called automatically when the skeleton is loaded. Computes the global inverse bind pose for each bone.
	void computeGlobalInvBindPose();
	void unload();

	const string& getName() const { return name; }
	void setName(const string& nameP);


private:
	vector<Bone> bones;
	vector<Matrix4> globalInvBindPoses;
	string name;
};

