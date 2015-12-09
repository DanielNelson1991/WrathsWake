#include "stdafx.h"
#include "Wall.h"
#include "BoundingSphere.h"
#include <cmath>

CWall::CWall(float x_, float y_, float z_,float w_, float h_, float d_, int textureID_):
C3dObject(x_,y_,z_,w_,h_,d_,textureID_)
{
	m_bEnableCollisions=1;
	m_pBSphere=0;
	m_bClampToTerrain=true;
	m_pBSphere=0;
	m_fY=y_;
}

CWall::~CWall(void)
{
}

bool
CWall::RespondToCollision()
{
return 0;
}

bool
CWall::isColliding(CBoundingSphere *pBSphere)
{
if (m_fYaw==0)
	{
	//check for distance between sphere centre-z and wall-z
		if (abs(m_fZ-pBSphere->Getz())<pBSphere->GetRadius())
		{
			float wallmaxx=m_fX + 0.5*m_fW;
			float wallminx=m_fX - 0.5*m_fW;
			if ((pBSphere->Getx()-pBSphere->GetRadius() < wallmaxx) && (pBSphere->Getx()+pBSphere->GetRadius() > wallminx))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
else if (m_fYaw==90)
	{
	//check for distance sphere centre-x and wall-x
	
		if (abs(m_fX-pBSphere->Getx())<pBSphere->GetRadius())
		{
		float wallmaxz=m_fZ + 0.5*m_fW;
		float wallminz=m_fZ - 0.5*m_fW;

			if ((pBSphere->Getz()-pBSphere->GetRadius() < wallmaxz) && (pBSphere->Getz()+pBSphere->GetRadius() > wallminz))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}

return 0;

}