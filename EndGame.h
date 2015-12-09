#pragma once
#include "maxfile.h"

class CEndGame : public CMaxFile
{
	

public:
	CEndGame(char * filepath_,float x_,float y_, float z_,float scale_, int textureID_);
	~CEndGame(void);

private: 
	void spinCrate();

	//void Update(float dt_);

	float angle;
};
