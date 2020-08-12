#include "BoneTransform.h"

Matrix4 BoneTransform::toMatrix() const
{
    Matrix4 r = Matrix4::createFromQuaternion(rotation);
    Matrix4 t = Matrix4::createTranslation(translation);

    return r * t;
}

BoneTransform BoneTransform::interpolate(const BoneTransform& a, const BoneTransform& b, float t)
{
    BoneTransform boneTransform;
    boneTransform.rotation = Quaternion::slerp(a.rotation, b.rotation, t);
    boneTransform.translation = Vector3::lerp(a.translation, b.translation, t);
    return boneTransform;
}
