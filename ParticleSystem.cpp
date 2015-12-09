// ParticleSystem.cpp: implementation of the CParticleSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include <math.h>
#include <gl.h>
#include "Game.h"
#include "Camera.h"
extern CGame gGame;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParticleSystem::CParticleSystem(float x_,float y_,float z_,float w_,float h_,float d_, int textureID_):
C3dObject(x_,y_,z_,w_,h_,d_,textureID_)
{
	m_bEnableCollisions=false;
	m_nParticlesLoaded=0;

	int mInitialParticles=50;

	for (int i=0;i<mInitialParticles;i++)
	{
		double size=0.01* (rand()%100);
		m_pParticleArray[m_nParticlesLoaded]=new CParticle(x_,y_,z_+0.02*i,size,size,1,textureID_);


		double randvx=0.01f*(rand()%100);
		double randvy=0.01f*(rand()%100);
		double randvz=0.01f*(rand()%100);

		double randspeed=0.03+0.03*(rand()%100);
		double randangle=rand()%360;


		//ensure spread of particles is perpendicular to camera direction
		float camx=gGame.GetCamera()->Getx();
		float camz=gGame.GetCamera()->Getz();

		float dx=camx-this->m_fX;
		float dz=camz-this->m_fZ;
		double thetaradians=atan2(dx,dz);

		double xspeed=randspeed*sin(randangle);
		double yspeed=randspeed*cos(randangle);

		float cosYaw,sinYaw;
		cosYaw=(float)cos(thetaradians);
		sinYaw=(float)sin(thetaradians);
		

		double vx=xspeed *cosYaw;
		double vy=yspeed;
		double vz=xspeed *sinYaw ;
			
		m_pParticleArray[m_nParticlesLoaded++]->SetVelocity(vx,vy,vz);
	}
}

CParticleSystem::~CParticleSystem()
{
	for (int i=0;i<m_nParticlesLoaded;i++)
	{
	delete m_pParticleArray[i];
	m_pParticleArray[i]=0;
	}
}

void
CParticleSystem::Update(float dt)
{

	//?spawn new particles?


	//check which particles need to be deleted
	for (int i=0;i<m_nParticlesLoaded;i++)
	{
		if (m_pParticleArray[i]->Getw()<0.01)
		{
		//remove small particle
		delete m_pParticleArray[i];
		m_pParticleArray[i]=0;
		//move last item into this slot
		m_pParticleArray[i]=m_pParticleArray[m_nParticlesLoaded-1];
		m_pParticleArray[m_nParticlesLoaded-1]=0;

		m_nParticlesLoaded--;
		}
	}

	for (int i=0;i<m_nParticlesLoaded;i++)
	{
	m_pParticleArray[i]->Update(dt);
	}

	if (m_nParticlesLoaded==0)
	{
		//no particles left so destroy particle system
		this->bTaggedForDeletion=true;
	}
}


void
CParticleSystem::Render()
{
	for (int i=0;i<m_nParticlesLoaded;i++)
	{
	m_pParticleArray[i]->Render();
	}
 
}

void
CParticleSystem::SpawnParticle(float x,float y,float z,float size, float vx,float vy, float vz, int textureID)
{
m_pParticleArray[m_nParticlesLoaded++]=new CParticle(x,y,z,size,size,1,textureID);
m_pParticleArray[m_nParticlesLoaded-1]->SetVelocity(vx,vy,vz);
}