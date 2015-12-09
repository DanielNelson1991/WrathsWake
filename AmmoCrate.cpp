#include "stdafx.h"
#include "AmmoCrate.h"
#include "Game.h"
#include <typeinfo>
#include "GL/gl.h"

extern CGame gGame;

CAmmoCrate::CAmmoCrate(char * filepath_,float x_,float y_, float z_,float scale_, int textureID_):CMaxFile(filepath_,x_,y_,z_,scale_,textureID_)
{


}

CAmmoCrate::~CAmmoCrate(void)
{
}

