#pragma once
#include "billboard.h"
#include "3dObject.h"
#include <vector>

class CEnemyBillboardFire : public CBillboard
{
protected:
	float m_fX;	//the position of the centre of the 3dObject
	float m_fY;
	float m_fZ;
	float m_fW;
	float m_fH;
	float m_fD;

public:
	CEnemyBillboardFire(float x_,float y_,float z_,float w_,float h_,float d_, int textureID_, bool bUseSpriteSheet_=false, int cols_=2,int rows_=2,int fps=0, bool additive_=false);
	~CEnemyBillboardFire(void);

	void Update(float dt_);
	void Render();
	void PostRender();

	void SetAnimFrame(int frame_); //display particular frame of animation
	void CalcBoundingSphere(); 
};
