// ParticleSystem.h: interface for the CParticleSystem class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "3dObject.h"

class CParticle;
class CGame;

#define MAX_PARTICLES 100

class CParticleSystem : public C3dObject 
{
public:
	CParticleSystem(float x_,float y_,float z_,float w_,float h_,float d_, int textureID_);
	virtual ~CParticleSystem();
	void Render();
	void Update(float dt);

private:
	CParticle * m_pParticleArray[MAX_PARTICLES];

	void SpawnParticle(float x,float y,float z, float size, float vx,float vy, float vz, int textureID);
	int m_nParticlesLoaded;
};


