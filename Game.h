#pragma once
#include "3dObject.h"
#include "Sprite.h"
#include "AmmoCrate.h"
#include "Audio.h"

#define MAX3dObjectS 1500

class C3dObject;
class CLight;
class CCamera;
class CTerrain;
class CMaxFile;
class CWall;

class CGame
{
public:
	CGame(void);
	~CGame(void);
	void DoFrame();
	CCamera * GetCamera(){return m_pCamera;}
	CTerrain * GetTerrain(){return m_pTerrain;}
	void HandleMouseMove(float xrel_,float yrel_);
	void Begin();
	
	int GetNumObjectsLoaded(){return m_i3dObjectsLoaded ;}
	C3dObject * GetObjectByIndex(int i);
	void AddObject(C3dObject * pObject_);
	bool b_wireframeMode;
	bool b_toggleLighting;
	bool b_birdseyeMode;
	bool b_shotgunSelected;
	bool b_p90Selected;

	int m_ideath;
	int m_iwin;

	bool b_isMusicPlayingMainGame;
	int m_enemiesKilled;
	
	IXACT3Cue * p_CurrentAudioCue;

private:
	int	m_i3dObjectsLoaded;
	C3dObject * m_p3dObjects[MAX3dObjectS];

	CCamera * m_pCamera;
	CTerrain * m_pTerrain;
	CGame * m_pGame;
	CMaxFile * m_psubGun;
	CMaxFile * m_pshotGun;

	CMaxFile * m_pBuilding;
	CMaxFile * m_pBuilding2;
	CMaxFile * m_pBuilding3;
	CMaxFile * m_pBuilding4;
	CMaxFile * m_pBuilding5;
	CMaxFile * m_pBuilding6;
	CMaxFile * m_pBuilding7;
	CMaxFile * m_pBuilding8;
	CMaxFile * m_pBuilding9;
	CMaxFile * m_pBuilding10;
	CMaxFile * m_pBuilding11;
	CMaxFile * m_pBuilding12;
	CMaxFile * m_pBuilding13;
	CMaxFile * m_pBuilding14;
	CMaxFile * m_pBuilding15;
	CMaxFile * m_pBuilding16;
	CMaxFile * m_pBuilding17;
	CMaxFile * m_pBuilding18;
	CMaxFile * m_pBuilding19;
	CMaxFile * m_pBuilding20;
	CMaxFile * m_pBuilding21;
	CMaxFile * m_pBuilding22;
	CMaxFile * m_pBuilding23;
	CMaxFile * m_pRoad1;
	CMaxFile * m_pRoad2;
	CMaxFile * m_pRoad3;
	
	CMaxFile * m_pPortal;

	CMaxFile * m_pAmmoCrate;
	CAmmoCrate * m_pAmmoCrate2;

	CWall * m_pWall1;
	CWall * m_pWall2;
	CWall * m_pWall3;
	CWall * m_pWall4;
	

	CSprite * m_pHUDCrosshair;
	CSprite * m_pHUDHealth;
	CSprite * m_pHUDAmmo9;
	CSprite * m_pHUDAmmo8;
	CSprite * m_pHUDAmmo7;
	CSprite * m_pHUDAmmo6;
	CSprite * m_pHUDAmmo5;
	CSprite * m_pHUDAmmo4;
	CSprite * m_pHUDAmmo3;
	CSprite * m_pHUDAmmo2;
	CSprite * m_pHUDAmmo1;
	CSprite * m_pHUDAmmoReload;
	CSprite * m_pMENUStart;
	CSprite * m_pMENUInstructions;
	CSprite * m_pMENUWin;
	CSprite * m_pMENULose;

	enum eGameState
	{
		eGameStateMenu = 0,
		eGameStatePlay = 1,
		eGameStatePaused = 2,
		eGameStateWin =3,
		eGameStateLose=4,
		eGameStateInstructions=5


	};
	eGameState m_eGameState;
};
