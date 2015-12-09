#include "stdafx.h"
#include "EndGame.h"
#include "Game.h"
#include <typeinfo>
#include "GL/gl.h"

extern CGame gGame;

CEndGame::CEndGame(char * filepath_,float x_,float y_, float z_,float scale_, int textureID_):CMaxFile(filepath_,x_,y_,z_,scale_,textureID_)
{
	//CMaxFile::CMaxFile();
	//filepath[] = "assets/AmmoCrate.dat";
	//spinCrate();
	angle = 4;
}

CEndGame::~CEndGame(void)
{
}


//NOTE: Overridong the function will mess up the positioning on Y-axis as well as collisions
/*void
CAmmoCrate::Update(float dt_)
{
	int numberOfObjects = gGame.GetNumObjectsLoaded();
	/*
	for (int i=0; i<numberOfObjects; i++)
	{
		C3dObject * obj = gGame.GetObjectByIndex(i);
		
		//check to see if it's colliding with itself (ammo crate)
		if(obj == this)continue;
			if(!obj->GetEnableCollisions()) continue;
			
			if(obj->isColliding(this->m_pBSphere))
			{
				if (obj->RespondToCollision(this))
				{
					//allow to pass through
				}
				else
				{
					//hit something
					if(typeid(*obj) == typeid(CCamera))
					{
						char msg[] = "collision with player";
						OutputDebugString(msg);
						//this->bTaggedForDeletion=true;
					}

				}
			}
	}
	

}
*/




void
CEndGame::spinCrate()
{
	/*char msg[] = "spinning crate";
	OutputDebugString(msg);
	
	glPushMatrix();
		glRotatef(angle, 0.0, 1.0, 0.0);
		this;
	glPopMatrix();
	angle+=4;
	*/
}