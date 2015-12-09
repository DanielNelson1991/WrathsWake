#include "stdafx.h"
#include "BoundingSphere.h"
#include <gl.h>
#include <glu.h>
#include <math.h>

extern bool b_wireframeMode;

CBoundingSphere::CBoundingSphere(float x_,float y_, float z_, float radius_)
{
	m_fX=x_;
	m_fY=y_;
	m_fZ=z_;
	m_fRadius=radius_;

}

CBoundingSphere::~CBoundingSphere(void)
{
}

void
CBoundingSphere::SetPosition(float x_, float y_, float z_)
{
	m_fX=x_;
	m_fY=y_;
	m_fZ=z_;
}

void
CBoundingSphere::Render()
{
	if (!b_wireframeMode) return;

	glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE ); //wireframe mode
	glDisable(GL_CULL_FACE); //don't cull faces
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glPushMatrix();
	{
		glTranslatef(m_fX,m_fY,m_fZ);		
		GLUquadric* newQuad= gluNewQuadric(); 
		gluQuadricTexture(newQuad,1);
		gluSphere ( newQuad , m_fRadius, 32, 32) ;
	}
	glPopMatrix();

	//put things back to normal
	glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL ); //wireframe mode
	glEnable(GL_CULL_FACE); //don't cull faces
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

bool
CBoundingSphere::TestIfColliding(CBoundingSphere * pbspherein)
{
//calculate distance between centres
	float dx,dy,dz;
	dx=m_fX-pbspherein->Getx();
	dy=m_fY-pbspherein->Gety();
	dz=m_fZ-pbspherein->Getz();

	//use pythag
	double separation;
	separation=sqrt(dx*dx+dy*dy+dz*dz);
	//sum of radii
	double sumradii=m_fRadius+pbspherein->GetRadius();

	return (separation<sumradii);
}