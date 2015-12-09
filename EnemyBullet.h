#pragma once
#include "3dobject.h"

class CEnemyBullet :
	public C3dObject
{
public:
	CEnemyBullet(float x_,float y_,float z_,float w_,float h_,float d_, int textureID_);
	~CEnemyBullet(void);

	void Update(float dt_);
};
