#include "StdAfx.h"
#include "Input.h"
#include "Game.h"
#include "Terrain.h"
#include "3dObject.h"
#include "math.h"
#include "BoundingSphere.h"
#include <iostream>

extern CGame gGame;

C3dObject::C3dObject(void)
{
	m_fX=0.0f;
	m_fY=0.0f;
	m_fW=1.0f;
	m_fH=1.0f;
	m_fR=m_fG=m_fB=m_fA=1.0;
	
	m_fYaw=0;
	m_fPitch=0;
	m_fRoll=0;
	m_bClampToTerrain = true;
	m_bEnableCollisions = true;
	m_fClampOffset = 0;

	m_fVelocityx=0.0f;
	m_fVelocityy=0.0f;
	m_fVelocityz=0.0f;
	bUseGravity=false;
	bTaggedForDeletion=false;
	CalcBoundingSphere();
}

C3dObject::C3dObject(float x_, float y_, float z_,float w_, float h_, float d_, int textureID_)
{
	
	m_fX=x_;
	m_fY=y_;
	m_fZ=z_;
	m_fW=w_;
	m_fH=h_;
	m_fD=d_;
	m_fR=m_fG=m_fB=m_fA=1.0;
	m_iTextureID=textureID_;
	
	m_fYaw=0;
	m_fPitch=0;
	m_fRoll=0;
	m_bEnableCollisions = true;
	m_bClampToTerrain = true;
	m_fClampOffset = 0;

	m_fVelocityx=0.0f;
	m_fVelocityy=0.0f;
	m_fVelocityz=0.0f;
	bTaggedForDeletion=false;
	bUseGravity=false;
	CalcBoundingSphere();
}

C3dObject::~C3dObject(void)
{
}

void 
C3dObject::Render()
{
	glPushMatrix();

	glShadeModel(GL_SMOOTH);		// use smooth shading
	
	glEnable(GL_DEPTH_TEST);
	glTranslatef(m_fX,m_fY,m_fZ);		// move to proper position
	glRotatef(m_fYaw,0.0f,1.0f,0.0f);
	glScalef(m_fW,m_fH,m_fD);

	glEnable(GL_CULL_FACE);	// do not calculate inside of polys
	
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING); //switch on dynamic lighting
	glDisable(GL_BLEND);

	if (m_iTextureID)
	{
		//use texture
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, m_iTextureID); 
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	}
	else
	{
		//zero for texture ID means don't use texture
		glDisable(GL_TEXTURE_2D);
	}
	
	//material properties
	GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat grey[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_AMBIENT, grey);

	glEnable(GL_NORMALIZE);

	// Display a quad size 1 by 1, centred at origin
	glBegin(GL_POLYGON);
				glNormal3f(0.0f, 1.0f, 0.0f);	// top face
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(0.5f, 0.0f);
				glVertex3f(0.5f, 0.5f, -0.5f);
				glTexCoord2f(0.5f, 0.5f);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(-0.5f, 0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(0.0f, 0.0f, 1.0f);	// front face
				glTexCoord2f(0.5f, 0.5f);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(-0.5f, 0.5f, 0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, 0.5f);
				glTexCoord2f(0.5f, 0.0f);
				glVertex3f(0.5f, -0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(1.0f, 0.0f, 0.0f);	// right face
				glTexCoord2f(0.5f, 1.0f);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(0.5f, 0.5f);
				glVertex3f(0.5f, -0.5f, 0.5f);
				glTexCoord2f(1.0f, 0.5f);
				glVertex3f(0.5f, -0.5f, -0.5f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(0.5f, 0.5f, -0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(-1.0f, 0.0f, 0.0f);	// left face
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-0.5f, 0.5f, 0.5f);	
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(0.0f, -1.0f, 0.0f);	// bottom face
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, 0.5f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(0.5f, -0.5f, 0.5f);	
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(0.0f, 0.0f, -1.0f);	// back face
				glTexCoord2f(0.5f, 0.0f);
				glVertex3f(0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(0.5f, 0.5);
				glVertex3f(0.5f, 0.5f, -0.5f);	
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

		if(m_pBSphere)
		{
			m_pBSphere->Render();
		}
}

void
C3dObject::Update(float dt_)
{
	ApplyClampToTerrain();
}

void
C3dObject::SetPosition(float x_,float y_,float z_)
{
	m_fX=x_;
	m_fY=y_;
	m_fZ=z_;
}

void
C3dObject::SetVelocity(float vx,float vy,float vz)
{
	m_fX=vx;
	m_fY=vy;
	m_fZ=vz;
}

void
C3dObject::IncrementYaw(float dyaw_)
{
	m_fYaw+=dyaw_;
	if (m_fYaw > 360)
	{
		m_fYaw=0.0;
	}
	if (m_fYaw <0)
	{
		m_fYaw=360.0;
	}
}

void
C3dObject::IncrementPitch(float dpitch_)
{
	m_fPitch+=dpitch_;
	if (m_fPitch > 360)
	{
		m_fPitch=0.0;
	}
	if (m_fPitch <0)
	{
		m_fPitch=360.0;
	}
}

void 
C3dObject::ApplyClampToTerrain()
{
	if(m_bClampToTerrain)
	{
		// Query Terrain to find how high it is at current objects location
		float newy=gGame.GetTerrain()->GetHeightAtPoint(m_fX, m_fZ);
		
		//set objects y-value to be on the terrain, but possibly adjusted by a bit to compensate for the shape of the object
		float deltaY=newy+m_fClampOffset-m_fY;
		m_fY+=deltaY;
		if (m_pBSphere)
		{
			m_pBSphere->m_fY+=deltaY;
		}
	}

}

void
C3dObject::CalcBoundingSphere()
{
	//calc radius
	float radsquared=(m_fW*m_fW + m_fH*m_fH+ m_fD * m_fD)/4.0;
	float rad=sqrt(radsquared); //need to #include <math.h>

	//generate bsphere
	m_pBSphere=new CBoundingSphere(m_fX,m_fY,m_fZ,rad);
}

bool 
C3dObject::RespondToCollision(C3dObject * hitObject)
{
	//default behavior is to return a 0 meaning 
	//no object allowed to pass through
	return 0;
}

void 
C3dObject::HitByBullet()
{

}



bool
C3dObject::isColliding(CBoundingSphere * bsphere_)
{
	//check for collision between two bspheres
	//this may be overidden in sub classes
	if (this->GetBoundingSphere()->TestIfColliding(bsphere_))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}