#include "stdafx.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"
#include <cmath>

CBoundingBox::CBoundingBox(float x_, float y_, float z_, float w_, float h_)
{
	m_fX = x_;
	m_fY = y_;
	m_fZ = z_;
	m_fW = w_;
	m_fH = h_;
	m_pBSphere=0;
}

CBoundingBox::~CBoundingBox(void)
{
}

void 
CBoundingBox::Update(float dt_)
{

}

void
CBoundingBox::Render()
{
	glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE ); //wireframe mode
	glDisable(GL_CULL_FACE); //don't cull faces
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glPushMatrix();
	{
		glBegin(GL_POLYGON);
		glColor3f(   1.0,  1.0, 1.0 );
		glVertex3f(  0.5, -0.5, 0.5 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glVertex3f( -0.5,  0.5, 0.5 );
		glVertex3f( -0.5, -0.5, 0.5 );
		glEnd();
		 
		// Purple side - RIGHT
		glBegin(GL_POLYGON);
		glColor3f(  1.0,  0.0,  1.0 );
		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5,  0.5, -0.5 );
		glVertex3f( 0.5,  0.5,  0.5 );
		glVertex3f( 0.5, -0.5,  0.5 );
		glEnd();
		 
		// Green side - LEFT
		glBegin(GL_POLYGON);
		glColor3f(   0.0,  1.0,  0.0 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glEnd();
		 
		// Blue side - TOP
		glBegin(GL_POLYGON);
		glColor3f(   0.0,  0.0,  1.0 );
		glVertex3f(  0.5,  0.5,  0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glEnd();
		 
		// Red side - BOTTOM
		glBegin(GL_POLYGON);
		glColor3f(   1.0,  0.0,  0.0 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glEnd();
	}
	glPopMatrix();

	//put things back to normal
	glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL ); //wireframe mode
	glEnable(GL_CULL_FACE); //don't cull faces
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

bool
CBoundingBox::TestIfColliding(CBoundingBox * pBSphere)
{
	//calculate distance between centres
	float dx,dy,dz;
	dx=m_fX-pBSphere->Getx();
	dy=m_fY-pBSphere->Gety();
	dz=m_fZ-pBSphere->Getz();
/*
	// Unsure what to do here. */

	if (m_fYaw==0)
	{
	//check for distance between sphere centre-z and wall-z
		if (abs(m_fZ-pBSphere->Getz())<pBSphere->GetArea())
		{
			float wallmaxx=m_fX + 0.5*m_fW;
			float wallminx=m_fX - 0.5*m_fW;
			if ((pBSphere->Getx()-pBSphere->GetArea() < wallmaxx) && (pBSphere->Getx()+pBSphere->GetArea() > wallminx))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
else if (m_fYaw==90)
	{
	//check for distance sphere centre-x and wall-x
	
		if (abs(m_fX-pBSphere->Getx())<pBSphere->GetArea())
		{
		float wallmaxz=m_fZ + 0.5*m_fW;
		float wallminz=m_fZ - 0.5*m_fW;

			if ((pBSphere->Getz()-pBSphere->GetArea() < wallmaxz) && (pBSphere->Getz()+pBSphere->GetArea() > wallminz))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	

	//return true;

	
}
