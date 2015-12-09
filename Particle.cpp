// Particle.cpp: implementation of the CParticle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Particle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParticle::CParticle(float x,float y,float z,float w,float h,float d, int textureID, bool bAdditive):
CBillboard(x,y,z,w,h,d,textureID,false,1,1,0,bAdditive)
{
	
	m_bEnableCollisions=false;
	SetClampToTerrain(false);
	
}

CParticle::~CParticle()
{

}

void
CParticle::Update(float dt)
{
	CBillboard::Update(dt); //to apply velocity

	this->m_fW*=0.9;
	this->m_fH*=0.9;

}

