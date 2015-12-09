#pragma once

#include "3dObject.h"
#include "Vector.h"
#include "Game.h"
#include <algorithm>// not used atm
#include <fstream> // used for save file

class CCamera : public C3dObject
{
public:
	CCamera(void);
	CCamera(float x_,float y_,float z_);
	~CCamera(void);
	void Update(float dt);
	void Render();
	void SetSpeed(float speed_){m_fSpeed=speed_;} 
	void CreateRay(float x_,float y_,float z_,float dirx_,float diry_,float dirz_);

	bool m_bClampToTerrain;
	float m_fClampOffset;
	float m_fBullets;

	int m_iAmmo;
	bool m_bFire;


private:

	float m_fSpeed; //forward motion
	float m_fRotateYaw;
	void CheckRayForCollision();
	CVector3 m_vRayStart;
	CVector3 m_vRayDirection;
	bool m_bShowRay;
};
