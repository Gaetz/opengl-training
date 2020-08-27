#pragma once
#include <stdio.h>

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4():
		x(0.0f), 
		y(0.0f),
		z(0.0f),
		w(0.0f)
	{}

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

	float operator[](unsigned int i)
	{
		printf("%p %d %d\n", &x, i, (int)sizeof(float));
		printf("%p\n", getAsFloatPtr() + i);
		return *(getAsFloatPtr() + i);
	}
};