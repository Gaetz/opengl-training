#ifndef MATHS_VECTOR4_H
#define MATHS_VECTOR4_H

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4()
		:x(0.0f)
		,y(0.0f)
		,z(0.0f)
		,w(0.0f)
	{}

	explicit Vector4(float inX, float inY, float inZ, float inW)
		:x(inX)
		,y(inY)
		,z(inZ)
		,w(inW)
	{}

	// Cast to a const float pointer
	const float* getAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// Set all four components in one line
	void set(float inX, float inY, float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}
};

#endif