#pragma once
#include "3dobject.h"

class CBoundingBox :
	public C3dObject
{
public:
	CBoundingBox(float x_, float y_, float z_, float w_, float h_);
	~CBoundingBox(void);
	void Update(float dt_);
	void Render();
	

	bool TestIfColliding(CBoundingBox * pbspherein);

	float m_fX;
	float m_fY;
	float m_fZ;
	float m_fW;
	float m_fH;
	float GetArea(){return m_fX*m_fY*m_fZ;}
};
