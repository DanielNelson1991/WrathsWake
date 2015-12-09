#pragma once
#include "3dobject.h"

class CBullet :
	public C3dObject
{
public:
	CBullet(float x_,float y_,float z_,float w_,float h_,float d_, int textureID_);
	~CBullet(void);

	void Update(float dt_);
};
