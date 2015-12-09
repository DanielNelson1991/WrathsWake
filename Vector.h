#pragma once

class CVector3
{
public:
	CVector3(float x_, float y_, float z_);
	CVector3();
	~CVector3(void);
	void Normalise();
	float DotProduct(CVector3 * invector);
	CVector3 operator-(CVector3 op2);
	CVector3 operator+(CVector3 op2);
	CVector3 operator*(float mult);
	float GetLength();

	float x;
	float y;
	float z;
};
