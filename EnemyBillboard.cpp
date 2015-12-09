#include "stdafx.h"
#include "EnemyBillboard.h"
#include "stdafx.h"
#include "gl.h"
//#include "Player.h"
#include "Camera.h"
#include "Game.h"
#include "math.h"
#include <dinput.h>
#include "input.h"
#include "Timer.h"
#include <algorithm>
#include "BoundingSphere.h"
#include "EnemyBullet.h"
#include <typeinfo>

extern CGame gGame;

CEnemyBillboard::CEnemyBillboard(float x_,float y_,float z_,float w_,float h_,float d_, int textureID_, bool bUseSpriteSheet_, int cols_, int rows_, int fps_, bool additive_)
:CBillboard(x_,y_,z_,w_,h_,d_,textureID_,bUseSpriteSheet_,cols_,rows_,fps_,additive_)
{
	m_fX=0.0f;
	m_fY=0.0f;
	m_fZ=0.0f;
	m_fW=0.0f;
	m_fH=0.0f;
	m_fD=0.0f;

	m_fX=x_;
	m_fY=y_;
	m_fZ=z_;
	m_fW=w_;
	m_fH=h_;
	m_fD=d_;

	bUseSpriteSheet=bUseSpriteSheet_;
	m_nFPS=fps_;
	m_nCols=cols_; //default setting
	m_nRows=rows_;
	m_nFrames=m_nRows*m_nCols;
	m_dTimeToAdvanceAnimation=CTimer::Instance()->GetTime();
	bAdditiveBlending=additive_;

	if (bUseSpriteSheet)
	{
		SetAnimFrame(0);
	}
	else
	{
		m_fULeft=0.01;
		m_fURight=0.99f;
		m_fVTop=0.99f;
		m_fVBottom=0.01f;
	}

	SetClampToTerrain(true);
	SetClampOffset(0.7*m_fH);
	m_bEnableCollisions=true;

	//add self to vector
	s_vSortedTransparentVec.push_back(this);
	s_iBillboardsLoaded++;
	//debug
	char op[64];
	sprintf(op,"\n**there are now %d billboards**\n",s_vSortedTransparentVec.size());
	OutputDebugString(op);

	CalcBoundingSphere();
}

CEnemyBillboard::~CEnemyBillboard(void)
{
	//remove self from static vector and decrement counter
	std::vector<C3dObject *>::iterator it;
	it=std::find(s_vSortedTransparentVec.begin(), s_vSortedTransparentVec.end(), this);
	//erase that part of vector
	s_vSortedTransparentVec.erase(it);
	s_iBillboardsLoaded--;
}

void
CEnemyBillboard::Render()
{
	//call static method
	//if I am the first billboard in the list then request rendering of all others
	if (s_vSortedTransparentVec[s_iBillboardsLoaded-1]==this)
	{
		RenderSorted();
	}
}

void
CEnemyBillboard::PostRender()
{
	glPushMatrix();
	glFrontFace(GL_CCW);
	glTranslatef(m_fX,m_fY,m_fZ);

	//yaw or heading is rotation about y axis
	glRotatef(m_fYaw,0.0f,1.0f,0.0f);
	glScalef(m_fW,m_fH,m_fD);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_iTextureID);
	glEnable(GL_DEPTH_TEST);

	//we won't use lighting for the billboards
	glEnable (GL_BLEND);
	glDisable (GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, m_iTextureID);

	if (bAdditiveBlending)
	{
		glBlendFunc( GL_SRC_ALPHA, GL_ONE);
	}
	else
	{
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}
	

		glBegin(GL_POLYGON);
			glNormal3f(0.0f, 0.0f, 1.0f);	// a single face
			glTexCoord2f(m_fURight, m_fVTop);
			glVertex3f(0.5f, 0.5f, 0.0f);	
			glTexCoord2f(m_fULeft, m_fVTop);
			glVertex3f(-0.5f, 0.5f, 0.0f);
			glTexCoord2f(m_fULeft, m_fVBottom);
			glVertex3f(-0.5f, -0.5f, 0.0f);
			glTexCoord2f(m_fURight, m_fVBottom);
			glVertex3f(0.5f, -0.5f, 0.0f);
		glEnd();
		
	glPopMatrix();

	if (gGame.b_wireframeMode == false)
	{
		//char msg[] = "Wireframe mode off\n";
		//OutputDebugString(msg);
	}
	else if (gGame.b_wireframeMode == true)
	{
		//char msg[] = "Wireframe mode pl0xz\n";
		//OutputDebugString(msg);
		glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE); //for wireframe
		glDisable(GL_TEXTURE_2D);

		m_pBSphere->Render();
	}

	if (gGame.b_toggleLighting == false)
	{
		//char msg[] = "Wireframe mode off\n";
		//OutputDebugString(msg);
		glDisable(GL_LIGHTING);
	}
	else if (gGame.b_toggleLighting == true)
	{
		//char msg[] = "Wireframe mode pl0xz\n";
		//OutputDebugString(msg);
		glEnable(GL_LIGHTING);
	}
}

void
CEnemyBillboard::Update(float dt_)
{
	//rotate to face camera
	//get camera pos
	
	float camx=gGame.GetCamera()->Getx();
	float camz=gGame.GetCamera()->Getz();

	float dx=camx-this->m_fX;
	float dz=camz-this->m_fZ;

	double thetaradians=atan2(dx,dz);
	double thetadegrees=180*thetaradians/3.142;
	this->SetYaw(thetadegrees);

	if (m_nFPS)
	{
		if (CTimer::Instance()->GetTime() > m_dTimeToAdvanceAnimation)
		{
		//it is time to advance animation
		m_nCurrentFrame++;
		SetAnimFrame(m_nCurrentFrame);
		//calc time for next change
		m_dTimeToAdvanceAnimation=CTimer::Instance()->GetTime() + 1.0f/(float)m_nFPS;
		}

	}
	ApplyClampToTerrain();

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
					//this goes inside the ‘a collision occurred’ if statement from before
					if (obj->RespondToCollision(this))
					{
						//we are allowed to pass through the colliding object
					}
					else
					{
					//we hit something		
					if (typeid(*obj) == typeid(CCamera))
					{
						gGame.m_iwin++;
						char msg[] = "enemy is colliding with pplayer ";
						OutputDebugString(msg);
					}
					
				}
			}
	}

	float camX,camY,camZ;
	camX=gGame.GetCamera()->Getx();
	camY=gGame.GetCamera()->Gety();
	camZ=gGame.GetCamera()->Getz();
	m_fDistanceFromViewpoint=sqrt( (m_fX-camX)*(m_fX-camX) + (m_fY-camY)*(m_fY-camY) + (m_fZ-camZ)*(m_fZ-camZ) );

	float xDistance = abs(camX-m_fX);
	float yDistance = abs(camY-m_fY);
	float zDistance = abs(camZ-m_fZ);

	float hyp = sqrt(xDistance*xDistance + yDistance*yDistance + zDistance*zDistance);
	xDistance /= hyp;
	yDistance /= hyp;
	zDistance /= hyp;

	m_fX += dx*xDistance*0.001;
	m_fZ += dz*zDistance*0.001;

	CalcBoundingSphere();
}

void
CEnemyBillboard::SetAnimFrame(int frame_)
{
	m_nCurrentFrame=frame_;
	if (m_nCurrentFrame> (m_nFrames-1))
	{
	if (bDeleteEndAnimation) 
		{
			//this->bTaggedForDeletion=true;
		}
		else
		{
			m_nCurrentFrame=0;
		}
	}
	
	//calc row
	int row = m_nCurrentFrame/m_nCols;
	int col = m_nCurrentFrame % m_nCols;

	float rowWidth=1.0f/(float)m_nCols;
	float colHeight=1.0f/(float)m_nRows;

	m_fULeft=row * rowWidth + 0.01;
	m_fURight=(row +1)* rowWidth -0.01;
	m_fVTop= (col+1) * colHeight -0.01;
	m_fVBottom= col * colHeight + 0.01;
}

void
CEnemyBillboard::CalcBoundingSphere()
{
	float radsquared=(m_fW*m_fW + m_fH*m_fH)/4.0;
	float rad=sqrt(radsquared);

	//generate bsphere
	m_pBSphere=new CBoundingSphere(m_fX,m_fY,m_fZ,rad);
}