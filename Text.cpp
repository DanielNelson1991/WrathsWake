// Text.cpp: implementation of the CText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Text.h"
#include <glut.h>
#include <gl.h>
#include <glu.h>

extern HDC g_hDC;
extern HGLRC g_hRC;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CText::CText()
{

}

CText::~CText()
{

}

//---------------------------------------------------------------------
//RenderBitmapString function takes two floats as the location of a string of 
//text which is rendered using a bitmap font.
//size of screen area scaled to 640 by 480 with origin at bottom left
//---------------------------------------------------------------------
void
CText::RenderBitmapString(float x_, float y_, char *string) 
{  

	//set orthographic projection mode

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the 
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, 640, 0, 480);

	glMatrixMode(GL_MODELVIEW);
	//end set ortho mode

	glPushMatrix();
	glLoadIdentity();
	
	glDisable(GL_TEXTURE);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);


	glColor4f(1.0,1.0,1.0,1.0);

	char *c;
	glRasterPos2f(x_, y_);

	for (c=string; *c != '\0'; c++) 
		{
		glutBitmapCharacter((void *)GLUT_BITMAP_HELVETICA_18, *c);

		}	
	

 	glPopMatrix();

	//reset perspective
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//end reset perspective


}

//---------------------------------------------------------------------
//Render2DImage function takes four floats as the location of a bitmap 
//image which is rendered at x,y and has size (w,h). textureID relates
//to texture image which should be loaded in advance
//---------------------------------------------------------------------
void
CText::Render2DImage(float x_,float y_, float w_,float h_,float textureID_)
{
	//set ortho 
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the 
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, 640, 0, 480);
	
	glMatrixMode(GL_MODELVIEW);
	//end set ortho mode
	glPushMatrix();
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


		glBindTexture(GL_TEXTURE_2D,textureID_);
		glDisable(GL_LIGHTING);
		glColor4f(1.0,1.0,1.0,1.0);
		//do 2d drawing here
		//just like when we drew our 2d sprite
		glTranslatef(x_,y_,0);		
		glScalef(w_,h_,1);

			glBegin(GL_POLYGON);
					
					glTexCoord2f(0.99f, 0.99f);
					glVertex2f(0.5f, 0.5f);	
					glTexCoord2f(0.01f, 0.99f);
					glVertex2f(-0.5f, 0.5f);
					glTexCoord2f(0.01f, 0.01f);
					glVertex2f(-0.5f, -0.5f);
					glTexCoord2f(0.99f, 0.01f);
					glVertex2f(0.5f, -0.5f);
				glEnd();
 	glPopMatrix();


	//reset perspective
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//end reset perspective
}
