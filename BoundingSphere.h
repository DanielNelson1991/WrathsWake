#pragma once

class CBoundingSphere
{
public:
	CBoundingSphere(float x_,float y_, float z_, float radius_);
	~CBoundingSphere(void);
	void SetPosition(float x_, float y_, float z_);
	void Render();

	bool TestIfColliding(CBoundingSphere * pbspherein);

	float Getx(){return m_fX;}
	float Gety(){return m_fY;}
	float Getz(){return m_fZ;}
	float GetRadius(){return m_fRadius;}
	

	float m_fX;
	float m_fY;
	float m_fZ;
	float m_fRadius;
};
