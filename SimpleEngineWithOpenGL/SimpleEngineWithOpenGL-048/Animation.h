#pragma once
#include "BoneTransform.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

class Animation
{
public:
	size_t getNbBones() const { return nbBones; }
	size_t getNbFrames() const { return nbFrames; }
	float getDuration() const { return duration; }
	float getFrameDuration() const { return frameDuration; }

	void setNbBones(size_t nbBonesP);
	void setNbFrames(size_t nbFramesP);
	void setDuration(float durationP);
	void setFrameDuration(float frameDurationP);
	void setTracks(const vector<vector<BoneTransform>>& tracksP);

	// Fills the provided vector with the global (current) pose matrices for each
	// bone at the specified time in the animation. It is expected that the time
	// is >= 0.0f and <= mDuration
	void getGlobalPoseAtTime(vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;
	void unload();

private:
	size_t nbBones;
	size_t nbFrames;
	float duration;
	float frameDuration;
	// Transform information for each frame on the track.
	// Each index in the outer vector is a bone, inner vector is a frame.
	vector<vector<BoneTransform>> tracks;
};

