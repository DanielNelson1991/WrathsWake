#pragma once
#include "3dobject.h"

//A Wall is like a 3dObject, but uses a simplified form of sphere-plane collision detection

class CWall :
	public C3dObject
{
public:
	CWall(float x_, float y_, float z_,float w_, float h_, float d_, int textureID_);
	~CWall(void);
	 bool isColliding(CBoundingSphere * pBSphere); //will use sphere-plane rather than sphere-sphere
	 bool RespondToCollision();
};
