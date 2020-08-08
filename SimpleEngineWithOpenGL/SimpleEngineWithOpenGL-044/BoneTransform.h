#pragma once
#include "Matrix4.h"
class BoneTransform
{
public:
	Matrix4 toMatrix() const;
	static BoneTransform interpolate(const BoneTransform& a, const BoneTransform& b, float t);

	Quaternion rotation;
	Vector3 translation;
};

