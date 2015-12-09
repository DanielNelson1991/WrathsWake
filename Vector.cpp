#include "stdafx.h"
#include "Vector.h"
#include <math.h>

CVector3::CVector3(float x_,float y_, float z_)
{
	x=x_;
	y=y_;
	z=z_;
}

CVector3::CVector3()
{

}

CVector3::~CVector3(void)
{
}


void
CVector3::Normalise()
{
float length=this->GetLength();
x/=length;
y/=length;
z/=length;
}

float
CVector3::DotProduct(CVector3 * invector)
{
return this->x * invector->x + this->y*invector->y + this->z*invector->z;
}

CVector3 
CVector3::operator-(CVector3 op2) 
{ 
  CVector3 temp; 
 
  temp.x = x - op2.x; 
  temp.y = y - op2.y; 
  temp.z = z - op2.z; 
  return temp; 
}

CVector3 
CVector3::operator+(CVector3 op2) 
{ 
  CVector3 temp; 
 
  temp.x = x + op2.x; 
  temp.y = y + op2.y; 
  temp.z = z + op2.z; 
  return temp; 
}

CVector3 
CVector3::operator*(float mult) 
{ 
  CVector3 temp; 
 
  temp.x = x *mult;
  temp.y = y *mult;
  temp.z = z *mult;
  return temp; 
}

float
CVector3::GetLength()
{
return sqrt(x*x+y*y+z*z);
}
