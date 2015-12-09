#include "stdafx.h"
#include "Camera.h"
#include <gl.h>
#include <glu.h>
#include <math.h>
#include <dinput.h>
#include "input.h"
#include "BoundingSphere.h"
#include "Game.h"
#include "Bullet.h"
#include "Light.h"
#include <stdio.h>
#include <typeinfo>
#include "Billboard.h"
#include "EnemyBillboard.h"
#include "EndGame.h"


extern CGame gGame;

#define DEG2RAD(x) 3.142*x/180

using namespace std;

CCamera::CCamera(void)
{
	m_fSpeed=10;
	m_fRotateYaw = 2.0f;
	SetClampToTerrain(true);
	SetClampOffset(3.0);
	m_bShowRay=false;

	m_iAmmo = 9;
	m_bFire = false; // DOn't fire if false
	
}

CCamera::CCamera(float x_, float y_,float z_):C3dObject(x_,y_,z_)
{
	m_fSpeed=10;
	m_fRotateYaw = 2.0f;
	SetClampToTerrain(true);
	SetClampOffset(3.0);
	m_bShowRay=false;
	m_pBSphere=new CBoundingSphere(x_, y_,z_,0.5);
	m_fBullets=9;
	m_iAmmo = 9;
	m_bFire = false; // DOn't fire if false

}

CCamera::~CCamera(void)
{
}

void
CCamera::Update(float dt_)
{
	//C3dObject * pLight=new CLight(m_fX,m_fY,m_fZ);
	//gGame.AddObject(pLight);



	float oldx=m_fX,oldy=m_fY,oldz=m_fZ;

	float cosYaw,sinYaw,sinPitch;
	cosYaw=(float)cos(DEG2RAD(m_fYaw));
	sinYaw=(float)sin(DEG2RAD(m_fYaw));
	sinPitch=(float)sin(DEG2RAD(m_fPitch));
	
	//OutputDebugString(op);

	if (CInput::Instance()-> GetIfKeyDown(DIK_W))
	{	
		// Move fowards
		m_fX+= sinYaw*m_fSpeed *dt_;
		m_fZ+=-cosYaw*m_fSpeed*dt_;
	}
	if (CInput::Instance()-> GetIfKeyDown(DIK_S))
	{	
		// Move backwards
		m_fX+=-sinYaw*m_fSpeed*dt_;
		m_fZ+=cosYaw*m_fSpeed*dt_;
	}
	if (CInput::Instance()->GetIfKeyDown(DIK_A))
	{
		// strafe left
		m_fX -= cosYaw*m_fSpeed*dt_;
		m_fZ -= sinYaw*m_fSpeed*dt_;
	}
	if (CInput::Instance()->GetIfKeyDown(DIK_D))
	{	
		// Strafe right
		m_fX += cosYaw*m_fSpeed*dt_;
		m_fZ += sinYaw*m_fSpeed*dt_;
	}
	
	// Save file (currently saves player's coordinates)
	if (CInput::Instance()->GetIfKeyDownEvent(DIK_F8))
	{
		char msg[] = "game saved";
		OutputDebugString(msg);
		
		//std::vector<CCamera *>::iterator m_CameraPosItr
		ofstream fout;
		fout.open("savefile.txt");
		if (!fout.fail())
		{
			fout<<m_fX<<endl;
			fout<<m_fY<<endl;
			fout<<m_fZ<<endl;

			LPCTSTR Caption = "Success!";
			MessageBox(NULL, "Game Saved", Caption, NULL);
		}
	}

	// Load Save file
	if (CInput::Instance()->GetIfKeyDownEvent(DIK_F9))
	{
		char msg[] = "temp load game";
		OutputDebugString(msg);
		
		ifstream savefile;
		savefile.open("savefile.txt");

		if (!savefile.fail())
		{
			while(savefile.good())
			{
				float xPos;
				float yPos;
				float zPos;

				savefile >> xPos; //>> std::endl;
				savefile >> yPos; //>> std::endl;
				savefile >> zPos;

				m_fX = xPos;
				m_fY = yPos;
				m_fZ = zPos;
			}
		}
		else
		{
			MessageBox(NULL, "Save file not found.\n Try saving again", NULL, NULL);
		}

	}

	this->m_pBSphere->SetPosition(this->Getx(), this->Gety(), this->Getz());

	float gunXoffset,gunYoffset,gunZoffset;
	float gundx=0.05f;
	float gundy=0.02f;
	float gundz=0.00f;
	gunXoffset=gundx*cosYaw;
	gunYoffset=- gundy;
	gunZoffset=gundx*sinYaw;

	if (m_bFire == true)
	{	
		if (m_iAmmo > 0)
			{
			float m_fBulletSpeed=50.0f;
			m_fBullets = m_fBullets - 1;
			
			//put a billboard in gun location
			C3dObject * bb=new CBillboard(m_fX+gunXoffset, m_fY+gunYoffset, m_fZ+gunZoffset,1.0,1.0,1.0,13,true,1,1,50,true);
			gGame.AddObject(bb);
			bb->SetClampToTerrain(false);
			((CBillboard *)bb)->bDeleteEndAnimation=true;

			if (CInput::Instance()->GetIfKeyDown(DIK_LSHIFT))
			{
				//shift key
				//alternative method with ray
				CreateRay(m_fX+gunXoffset,m_fY+gunYoffset,m_fZ+gunZoffset,sinYaw * m_fBulletSpeed,sinPitch * m_fBulletSpeed,-cosYaw * m_fBulletSpeed);
			}
			else
			{
				//no shift key - fire a bullet object
				float gunx=m_fX+gunXoffset;
				float guny=m_fY+gunYoffset;
				float gunz=m_fZ+gunZoffset;	
				C3dObject * bullet=new CBullet(gunx,guny,gunz,0.01,0.01,0.01,0);
				gGame.AddObject(bullet);
				bullet->bUseGravity=false;
				
				bullet->m_fVelocityx=sinYaw * m_fBulletSpeed;
				bullet->m_fVelocityy=sinPitch * m_fBulletSpeed;
				bullet->m_fVelocityz=-cosYaw * m_fBulletSpeed;

				m_iAmmo -= 1;
				m_bFire = false; // set off
			}
		
		}
		if(gGame.b_shotgunSelected == true && m_iAmmo > 0)
		{
			gGame.p_CurrentAudioCue = CAudio::Instance()->Play(4);
		}
		else if(gGame.b_p90Selected == true && m_iAmmo > 0)
		{
			gGame.p_CurrentAudioCue = CAudio::Instance()->Play(3);
		}
	}

	int numobjects=gGame.GetNumObjectsLoaded(); //make sure to do extern CGame gGame at the top of the file to get this to work
	
	//now loop through all those objects
	for (int i=0;i<numobjects;i++)
		{
		C3dObject * obj=gGame.GetObjectByIndex(i);
		//now check to see whether it is the same as ourself (the camera)
		//if it is then skip to next item
		if (obj==this) continue;
			if (!obj->GetEnableCollisions())continue;

			if (obj->isColliding(this->m_pBSphere)) //this->GetBoundingSphere()->TestIfColliding(obj-> GetBoundingSphere()))
				{
				//a collision occured - do something!
				//this goes inside the ‘a collision occurred’ if statement from before
					if (obj->RespondToCollision(this))
						{
						//we are allowd to pass through the colliding object
						}
						else
						{
							if (typeid(*obj) == typeid(CAmmoCrate))
							{
								char msg[] = "Collision with the ammo crate";
								OutputDebugString(msg);
								if (m_iAmmo != 10)
								{
									m_iAmmo = 10;
									m_fBullets=9;
								}
							}
							if (typeid(*obj) == typeid(CEnemyBillboard))
							{
								gGame.m_ideath++;
								char msg[] = "Game Over. Enemy has collided with the Player";
								OutputDebugString(msg);
							}
							if (typeid(*obj) == typeid(CEndGame))
							{	
								gGame.m_iwin++;
								char msg[] = "Game Win. Player has collided with the portal";
								OutputDebugString(msg);
								
							}
						//return value false so move camera back to start
						this->SetPosition(oldx,oldy,oldz);
						}

				}

		}

	ApplyClampToTerrain();

	//update lookat based on yaw and pitch
	float lookAtx=m_fX+sinYaw;
	float lookAty=m_fY+sinPitch;
	float lookAtz=m_fZ-cosYaw;

	gluLookAt(m_fX,m_fY,m_fZ,lookAtx,lookAty,lookAtz,0,1,0);

	//update position of bsphere
	this->m_pBSphere->SetPosition(this->Getx(), this->Gety(), this->Getz());
}

void
CCamera::Render()
{
	if(m_pBSphere)
	{
		m_pBSphere->Render();
	}
	if (m_bShowRay)
	{
		float scaleFactor=10;

		glDisable(GL_LIGHTING);
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		glLineWidth(5.0f);
		glDisable(GL_TEXTURE_2D);

		glBegin(GL_LINES);
			glVertex3f(m_vRayStart.x,m_vRayStart.y,m_vRayStart.z);
			glVertex3f(m_vRayStart.x+scaleFactor*m_vRayDirection.x,m_vRayStart.y+scaleFactor*m_vRayDirection.y,m_vRayStart.z+scaleFactor*m_vRayDirection.z);
		glEnd();

		m_bShowRay=false;

		CheckRayForCollision();
	}

	if (gGame.b_wireframeMode == false)
	{
		char msg[] = "Wireframe mode off\n";
		OutputDebugString(msg);
	}
	else if (gGame.b_wireframeMode == true)
	{
		glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE); //for wireframe
		glDisable(GL_TEXTURE_2D);
	}

	if (gGame.b_toggleLighting == false)
	{
		glDisable(GL_LIGHTING);
	}
	else if (gGame.b_toggleLighting == true)
	{
		glEnable(GL_LIGHTING);
	}
}

void
CCamera::CreateRay(float x_,float y_,float z_,float dirx_,float diry_,float dirz_)
{
	m_vRayStart.x=x_;
	m_vRayStart.y=y_;
	m_vRayStart.z=z_;
	//need to make sure direction is normalized
	m_vRayDirection.x=dirx_;
	m_vRayDirection.y=diry_;
	m_vRayDirection.z=dirz_;
	m_vRayDirection.Normalise();
	m_bShowRay=true;
}

void
CCamera::Jump(float y_, float velocity_, float gravity_, float time_)
{
	m_fY = y_;
	velocity_ = 10;
	gravity_ = 9.92;
	time_ = 2;
}

void
CCamera::CheckRayForCollision()
{	
int numobjects=gGame.GetNumObjectsLoaded();
	for (int i=0;i<numobjects;i++)
	{
	C3dObject * obj=gGame.GetObjectByIndex(i);
	char debugtxt[256];

	if (obj==this)
	{
		sprintf(debugtxt,"%d,no need to consider self %s\n",i,typeid(*obj).name());
		OutputDebugString(debugtxt);
		continue;
	}
	if (!obj->GetEnableCollisions())
	{
		sprintf(debugtxt,"%d,no need to consider item with collisions disabled %s\n",i,typeid(*obj).name());
		OutputDebugString(debugtxt);
		continue;
	}
	if (obj->GetBoundingSphere()==0)
	{
		sprintf(debugtxt,"%d,no need to consider %s which has not boundingsphere\n",i,typeid(*obj).name());
		OutputDebugString(debugtxt);
		continue;
	}

	if (typeid(*obj)== typeid(CBullet))
	{
		sprintf(debugtxt,"%d,no need to consider bullet %s\n",i,typeid(*obj).name());
		OutputDebugString(debugtxt);
		continue;
	}

	if (typeid(*obj)== typeid(CBillboard))
	{
		sprintf(debugtxt,"%d,no need to consider billboard %s\n",i,typeid(*obj).name());
		OutputDebugString(debugtxt);
		continue;
	}
	//does ray intersect bounding sphere?
	CBoundingSphere * sph;
	sph=obj->GetBoundingSphere();
	float sphx,sphy,sphz,sphrad;
	sphx=sph->Getx();
	sphy=sph->Gety();
	sphz=sph->Getz();
	sphrad=sph->GetRadius();
	CVector3 vBoundingSphereCentre(sphx,sphy,sphz);
	//compute vector from beginning of ray to centre of sphere
	CVector3 vRayStartToSphereCentre = vBoundingSphereCentre-m_vRayStart;
	//get dot product of this vector with ray direction
	float dotp=vRayStartToSphereCentre.DotProduct(&m_vRayDirection);

		if (dotp<0)
		{
			//no collision, sphere behind ray
			sprintf(debugtxt,"%d,no collision with %s. dotprod:%2.2f\n",i,typeid(*obj).name(),dotp);
		}
		else
		{
			//sphere centre projects onto line
			//calc projected point of centre of sphere on line
			CVector3 vCentreProjOnLine = m_vRayStart + m_vRayDirection * dotp;
			//calc distance from centre to projected point
			CVector3 vCentreToProjectedPoint=vCentreProjOnLine-vBoundingSphereCentre;
			float dist=vCentreToProjectedPoint.GetLength();
			if (dist > sphrad)
			{
				//no collision
				sprintf(debugtxt,"%d,no collision with %s. distance to centre:%2.2f, radius:2.2f\n",i,typeid(*obj).name(),dist,sphrad);
				
			}
			else
			{
				//there is a collision with obj
				sprintf(debugtxt,"%d, collision with %s. distance to centre:%2.2f, radius:2.2f\n",i,typeid(*obj).name(),dist,sphrad);
				//calc intersection point
				float dCentreToProjectedCentre =(vCentreProjOnLine-vBoundingSphereCentre).GetLength();
				float dist=sqrt(sphrad*sphrad  - dCentreToProjectedCentre*dCentreToProjectedCentre);
				float distInt1=(vCentreProjOnLine-m_vRayStart).GetLength()-dist;
				
				CVector3 vIntsec=m_vRayStart + m_vRayDirection * distInt1;
				//draw a billboard at point of impac
				C3dObject * bb=new CBillboard(vIntsec.x, vIntsec.y, vIntsec.z,1,1,1,13,true,4,5,50,true);
				gGame.AddObject(bb);
				bb->SetClampToTerrain(false);
				((CBillboard *)bb)->bDeleteEndAnimation=true; //delete billboard when it finished playing animation
				obj->HitByBullet();
				//bb->bTaggedForDeletion=true;
				//obj->HitByBullet();//vIntsec.x,vIntsec.y,vIntsec.z);
			}
			

		}
		OutputDebugString(debugtxt);
	}
		
}