// Particle.h: interface for the CParticle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTICLE_H__32159C77_FF11_4EBB_B17A_E68E3E7825D4__INCLUDED_)
#define AFX_PARTICLE_H__32159C77_FF11_4EBB_B17A_E68E3E7825D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Billboard.h"

class CGame;

class CParticle : public CBillboard  
{
public:
	CParticle(float x,float y,float z,float w,float h,float d, int textureID, bool bAdditive=true);

	virtual ~CParticle();
	void Update(float dt);


private:


};

#endif // !defined(AFX_PARTICLE_H__32159C77_FF11_4EBB_B17A_E68E3E7825D4__INCLUDED_)
