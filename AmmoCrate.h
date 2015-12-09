#pragma once
#include "3dObject.h"
#include "maxfile.h"

class CAmmoCrate : public CMaxFile
{
	

public:
	CAmmoCrate(char * filepath_,float x_,float y_, float z_,float scale_, int textureID_);
	~CAmmoCrate(void);

private: 

};
