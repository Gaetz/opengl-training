#ifndef MATHS_MATRIX4_H
#define MATHS_MATRIX4_H

#include <memory>
#include "Vector4.h"
#include <vector>
#include "Quaternion.h"

// Col major order 4*4 matrix
class Matrix4
{
public:
	Vector4 mat[4];

	Matrix4()
	{
		*this = Matrix4::identity;
	}

	inline void assign(const Vector4 (&inMat)[4])
	{
		int n = 0;
        for (n = 0; n < 4; n++)
            mat[n] = inMat[n];
	}

	inline Matrix4(const Matrix4& that)
    {
        assign(that.mat);
    }

	inline Matrix4(const Vector4 (&inMat)[4])
    {
        assign(inMat);
    }

	const float* getAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0]);
	}

	inline Vector4& operator[](const int i)
	{
		return mat[i];
	}

	inline Matrix4& operator=(const Matrix4& that)
    {
        assign(that.mat);
		return  *this;
    }

	inline Matrix4 operator+(const Matrix4& that) const
    {
        Matrix4 result;
        int n;
        for (n = 0; n < 4; n++)
            result.mat[n] = mat[n] + that.mat[n];
        return result;
    }

    inline Matrix4& operator+=(const Matrix4& that)
    {
        return (*this = *this + that);
    }

    inline Matrix4 operator-(const Matrix4& that) const
    {
        Matrix4 result;
        int n;
        for (n = 0; n < 4; n++)
            result.mat[n] = mat[n] - that.mat[n];
        return result;
    }

    inline Matrix4& operator-=(const Matrix4& that)
    {
        return (*this = *this - that);
    }

	// Matrix multiplication (a * b)
	friend Matrix4 operator*(Matrix4& a, Matrix4& b)
	{
		Vector4 vec0;
		Vector4 vec1;
		Vector4 vec2;
		Vector4 vec3;

		vec0[0] = 
		a[0][0] * b[0][0] +
		a[1][0] * b[0][1] +
		a[2][0] * b[0][2] +
		a[3][0] * b[0][3];

		vec0[1] = 
		a[0][1] * b[0][0] +
		a[1][1] * b[0][1] +
		a[2][1] * b[0][2] +
		a[3][1] * b[0][3];

		vec0[2] = 
		a[0][2] * b[0][0] +
		a[1][2] * b[0][1] +
		a[2][2] * b[0][2] +
		a[3][2] * b[0][3];

		vec0[3] = 
		a[0][3] * b[0][0] +
		a[1][3] * b[0][1] +
		a[2][3] * b[0][2] +
		a[3][3] * b[0][3];

		vec1[0] = 
		a[0][0] * b[1][0] +
		a[1][0] * b[1][1] +
		a[2][0] * b[1][2] +
		a[3][0] * b[1][3];

		vec1[1] = 
		a[0][1] * b[1][0] +
		a[1][1] * b[1][1] +
		a[2][1] * b[1][2] +
		a[3][1] * b[1][3];

		vec1[2] = 
		a[0][2] * b[1][0] +
		a[1][2] * b[1][1] +
		a[2][2] * b[1][2] +
		a[3][2] * b[1][3];

		vec1[3] = 
		a[0][3] * b[1][0] +
		a[1][3] * b[1][1] +
		a[2][3] * b[1][2] +
		a[3][3] * b[1][3];

		vec2[0] = 
		a[0][0] * b[2][0] +
		a[1][0] * b[2][1] +
		a[2][0] * b[2][2] +
		a[3][0] * b[2][3];

		vec2[1] = 
		a[0][1] * b[2][0] +
		a[1][1] * b[2][1] +
		a[2][1] * b[2][2] +
		a[3][1] * b[2][3];

		vec2[2] = 
		a[0][2] * b[2][0] +
		a[1][2] * b[2][1] +
		a[2][2] * b[2][2] +
		a[3][2] * b[2][3];

		vec2[3] = 
		a[0][3] * b[2][0] +
		a[1][3] * b[2][1] +
		a[2][3] * b[2][2] +
		a[3][3] * b[2][3];

		vec3[0] = 
		a[0][0] * b[3][0] +
		a[1][0] * b[3][1] +
		a[2][0] * b[3][2] +
		a[3][0] * b[3][3];

		vec3[1] = 
		a[0][1] * b[3][0] +
		a[1][1] * b[3][1] +
		a[2][1] * b[3][2] +
		a[3][1] * b[3][3];

		vec3[2] = 
		a[0][2] * b[3][0] +
		a[1][2] * b[3][1] +
		a[2][2] * b[3][2] +
		a[3][2] * b[3][3];

		vec3[3] = 
		a[0][3] * b[3][0] +
		a[1][3] * b[3][1] +
		a[2][3] * b[3][2] +
		a[3][3] * b[3][3];

		Vector4 newMat[4] { vec0, vec1, vec2, vec3 };
		Matrix4 retVal(newMat);

		return retVal;
	}

	Matrix4& operator*=(Matrix4& right)
	{
		*this = *this * right;
		return *this;
	}

	// Invert the matrix - super slow
	void invert();

	Vector3 getTranslation() const
	{
		auto transVector = mat[3];
		return Vector3(transVector[0], transVector[1], transVector[2]);
	}

	Vector3 getXAxis() const
	{
		auto xVector = mat[0];
		return Vector3::normalize(Vector3(xVector[0], xVector[1], xVector[2]));
	}

	Vector3 getYAxis() const
	{
		auto yVector = mat[1];
		return Vector3::normalize(Vector3(yVector[0], yVector[1], yVector[2]));
	}

	Vector3 getZAxis() const
	{
		auto zVector = mat[2];
		return Vector3::normalize(Vector3(zVector[0], zVector[1], zVector[2]));
	}

	Vector3 getScale() const
	{
		Vector3 retVal;
		retVal.x = Vector3(mat[0].x, mat[0].y, mat[0].z).length();
		retVal.y = Vector3(mat[1].x, mat[1].y, mat[1].y).length();
		retVal.z = Vector3(mat[2].x, mat[2].y, mat[2].z).length();
		return retVal;
	}

	static Matrix4 createScale(float xScale, float yScale, float zScale)
	{
		Vector4 temp[4] =
		{
			Vector4 { xScale, 0.0f, 0.0f, 0.0f },
			Vector4 { 0.0f, yScale, 0.0f, 0.0f },
			Vector4 { 0.0f, 0.0f, zScale, 0.0f },
			Vector4 { 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 createScale(const Vector3& scaleVector)
	{
		return createScale(scaleVector.x, scaleVector.y, scaleVector.z);
	}

	static Matrix4 createScale(float scale)
	{
		return createScale(scale, scale, scale);
	}

	static Matrix4 createRotationX(float theta)
	{
		Vector4 temp[4] =
		{
			Vector4 { 1.0f, 0.0f, 0.0f , 0.0f },
			Vector4 { 0.0f, Maths::cos(theta), -Maths::sin(theta), 0.0f },
			Vector4 { 0.0f, Maths::sin(theta), Maths::cos(theta), 0.0f },
			Vector4 { 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	static Matrix4 createRotationY(float theta)
	{
		Vector4 temp[4] =
		{
			Vector4 { Maths::cos(theta), 0.0f, Maths::sin(theta), 0.0f },
			Vector4 { 0.0f, 1.0f, 0.0f, 0.0f },
			Vector4 { -Maths::sin(theta), 0.0f, Maths::cos(theta), 0.0f },
			Vector4 { 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	static Matrix4 createRotationZ(float theta)
	{
		Vector4 temp[4] =
		{
			Vector4 { Maths::cos(theta), Maths::sin(theta), 0.0f, 0.0f },
			Vector4 { -Maths::sin(theta), Maths::cos(theta), 0.0f, 0.0f },
			Vector4 { 0.0f, 0.0f, 1.0f, 0.0f },
			Vector4 { 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	static Matrix4 createTranslation(const Vector3& trans)
	{
		Vector4 temp[4] =
		{
			Vector4 { 1.0f, 0.0f, 0.0f, 0.0f },
			Vector4 { 0.0f, 1.0f, 0.0f, 0.0f },
			Vector4 { 0.0f, 0.0f, 1.0f, 0.0f },
			Vector4 { trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 createSimpleViewProj(float width, float height)
	{
		Vector4 temp[4] =
		{
			Vector4 { 2.0f / width, 0.0f, 0.0f, 0.0f },
			Vector4 { 0.0f, 2.0f / height, 0.0f, 0.0f },
			Vector4 { 0.0f, 0.0f, 1.0f, 1.0f },
			Vector4 { 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 createFromQuaternion(const Quaternion& q)
	{
		Vector4 vec0;
		vec0[0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
		vec0[1] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
		vec0[2] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
		vec0[3] = 0.0f;

		Vector4 vec1;
		vec1[0] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
		vec1[1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
		vec1[2] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
		vec1[3] = 0.0f;

		Vector4 vec2;
		vec2[0] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
		vec2[1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
		vec2[2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
		vec2[3] = 0.0f;

		Vector4 vec3;
		vec3[0] = 0.0f;
		vec3[1] = 0.0f;
		vec3[2] = 0.0f;
		vec3[3] = 1.0f;

		Vector4 mat[4] { vec0, vec1, vec2, vec3 };

		return Matrix4(mat);
	}

	static Matrix4 createLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 zaxis = Vector3::normalize(target - eye);
		Vector3 xaxis = Vector3::normalize(Vector3::cross(up, zaxis));
		Vector3 yaxis = Vector3::normalize(Vector3::cross(zaxis, xaxis));
		Vector3 trans;
		trans.x = -Vector3::dot(xaxis, eye);
		trans.y = -Vector3::dot(yaxis, eye);
		trans.z = -Vector3::dot(zaxis, eye);

		Vector4 temp[4] =
		{
			Vector4 { xaxis.x, xaxis.y, xaxis.z, 0.0f },
			Vector4 { yaxis.x, yaxis.y, yaxis.z, 0.0f },
			Vector4 { zaxis.x, zaxis.y, zaxis.z, 0.0f },
			Vector4 { trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 createOrtho(float width, float height, float near, float far)
	{
		Vector4 temp[4] =
		{
			Vector4 { 2.0f / width, 0.0f, 0.0f, 0.0f },
			Vector4 { 0.0f, 2.0f / height, 0.0f, 0.0f },
			Vector4 { 0.0f, 0.0f, 2.0f / (near - far), 0.0f },
			Vector4 { 0.0f, 0.0f, (far + near) / (far - far), 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 createPerspectiveFOV(float fovY, float width, float height, float near, float far)
	{
		float yScale = Maths::cot(fovY / 2.0f);
		float xScale = yScale * height / width;
		Vector4 temp[4] =
		{
			Vector4 { xScale, 0.0f, 0.0f, 0.0f },
			Vector4 { 0.0f, yScale, 0.0f, 0.0f },
			Vector4 { 0.0f, 0.0f, near + far / (near - far), -1.0f },
			Vector4 { 0.0f, 0.0f,  2.0f * near * far / (near - far), 0.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 createPerspective(float left, float right, float bottom, float top, float near, float far)
	{
		Vector4 temp[4] =
		{
			Vector4 { 2 * near / (right - left), 0.0f, 0.0f, 0.0f },
			Vector4 { 0.0f, 2 * near / (top - bottom), 0.0f, 0.0f },
			Vector4 { (right + left) / (right - left), (top + bottom) / (top - bottom), (far + near) / (near - far), -1.0f },
			Vector4 { 0.0f, 0.0f, 2 * near * far / (near - far), 0.0f }
		};
		return Matrix4(temp);
	}

	static const Matrix4 identity;
};

#endif