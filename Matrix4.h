#pragma once
class Matrix4
{
public:

	float m[4][4];

	Matrix4();

	void IdentityMatrix4();

	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	Matrix4& operator*=(const Matrix4& m2);
	Matrix4& operator=(const Matrix4& m2);
};

