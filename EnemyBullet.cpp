#include "stdafx.h"
#include "EnemyBullet.h"
#include "Game.h"
#include "BoundingSphere.h"
#include "Maxfile.h"
#include "Billboard.h"
#include <typeinfo>

extern CGame gGame;

CEnemyBullet::CEnemyBullet(float x_,float y_,float z_,float w_,float h_,float d_, int textureID_):C3dObject(x_,y_,z_,w_,h_,d_,textureID_)
{

}

CEnemyBullet::~CEnemyBullet(void)
{

}

void 
CEnemyBullet::Update(float dt_)
{
	if (bUseGravity)
	{
		m_fVelocityy-=0.1*dt_;
	}

	m_fX+=dt_*m_fVelocityx;
	m_fY+=dt_*m_fVelocityy;
	m_fZ+=dt_*m_fVelocityz;



	//update bsphere
	m_pBSphere->SetPosition(m_fX, m_fY, m_fZ);

	//check for collision
	int numobjects=gGame.GetNumObjectsLoaded(); //make sure to do extern CGame gGame at the top of the file to get this to work
	
	//now loop through all those objects
	for (int i=0;i<numobjects;i++)
		{
		C3dObject * obj=gGame.GetObjectByIndex(i);
		//now check to see whether it is the same as ourself (the camera)
		//if it is then skip to next item
		if (obj==this) continue;
			if (!obj->GetEnableCollisions())continue;

			if (obj->isColliding(this->m_pBSphere))
			//if (this->GetBoundingSphere()->TestIfColliding(obj-> GetBoundingSphere()))
				{
					//a collision occured - do something!
					//this goes inside the �a collision occurred� if statement from before
					if (obj->RespondToCollision(this))
						{
						//we are allowed to pass through the colliding object
						}
						else
						{
						//we hit something
							if (typeid(*obj) == typeid(CMaxFile))
							{
							this->bTaggedForDeletion=true;
							obj->HitByBullet();
							}
							else if(typeid(*obj) == typeid(CCamera))
							{
							this->bTaggedForDeletion=true;
							char test[] = "worked";
							OutputDebugString(test);
							//obj->bTaggedForDeletion=true;
							}
						}

				}

		}
}