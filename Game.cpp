#include "StdAfx.h"
#include ".\game.h"
#include <gl.h>
#include <glu.h>
#include <math.h>
#include "Light.h"
#include "Input.h"
#include "Timer.h"
#include "Camera.h"
#include "EnemyBillboard.h"
#include "EnemyBillboardFire.h"
#include "SkyBox.h"
#include "Maxfile.h"
#include "Terrain.h"
#include "ParticleSystem.h"
#include "Wall.h"
#include <stdlib.h>
#include "EndGame.h"
#include "Audio.h"
#include <iostream>
#include <stdlib.h>
#include "Text.h"
#include <sstream>
#include <string.h>
using namespace std;

extern CCamera gCamera;

//game constructor loads 3dObjects into array
CGame::CGame(void)
{	
	CGame::Begin();
}

void
CGame::Begin()
{
	m_i3dObjectsLoaded=0;
	//load 3dObjects
	//skybox first
	m_p3dObjects[m_i3dObjectsLoaded++]=new CSkyBox(0,0,0,1000,1000,1000,10);

	//setup camera
	m_pCamera=new CCamera(0,1,6);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pCamera;

	//m_p3dObjects[m_i3dObjectsLoaded++]=new C3dObject(1,2,-3,1,1,1,2);
	
	//setup the terrain
	m_pTerrain=new CTerrain(0, 0, 0, 1000, 20, 1000, 44);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pTerrain;

	m_eGameState = CGame::eGameStateMenu;

	
	b_isMusicPlayingMainGame = false;
	b_shotgunSelected = true;

	p_CurrentAudioCue = CAudio::Instance()->Play(1);

	
	m_enemiesKilled = 0;
	
	// Le buildings
	m_pBuilding = new CMaxFile("assets/buildingTest.dat", 1, 2, 0, 1, 21);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding;
	m_pBuilding->SetEnableCollisions(false);
	m_pBuilding->SetClampToTerrain(true);
	m_pBuilding->SetClampOffset(74);

	m_pWall1 = new CWall(162, 0, 119, 73, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall1;
	m_pWall1->SetClampToTerrain(true);
	
	m_pWall2 = new CWall(162, 0, 188, 73, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall2;
	m_pWall2->SetClampToTerrain(true);

	m_pWall3 = new CWall(198, 0, 153.5, 70, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall3;
	m_pWall3->SetClampToTerrain(true);
	m_pWall3->SetYaw(90);

	m_pWall3 = new CWall(125.8, 0, 153.5, 70, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall3;
	m_pWall3->SetClampToTerrain(true);
	m_pWall3->SetYaw(90);

	m_pBuilding2 = new CMaxFile("assets/building2.dat", 1, 2, 0, 1, 22);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding2;
	m_pBuilding2->SetEnableCollisions(false);
	m_pBuilding2->SetClampToTerrain(true);
	m_pBuilding2->SetClampOffset(100);

	m_pWall4 = new CWall(190, 0, 27, 46, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(190, 0, 106.5, 46, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(168, 0, 66.5, 80, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(213, 0, 66.5, 80, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding3 = new CMaxFile("assets/building3.dat", 1, 2, 0, 1, 23);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding3;
	m_pBuilding3->SetEnableCollisions(false);
	m_pBuilding3->SetClampToTerrain(true);
	m_pBuilding3->SetClampOffset(100);

	m_pWall4 = new CWall(133.25, 0, 39.5, 46, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(133.25, 0, 107, 46, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(156, 0, 73, 68, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(111, 0, 73, 68, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding3 = new CMaxFile("assets/building4.dat", 1, 2, 0, 1,24);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding3;
	m_pBuilding3->SetEnableCollisions(false);
	m_pBuilding3->SetClampToTerrain(true);
	m_pBuilding3->SetClampOffset(51);

	m_pWall4 = new CWall(62, 0, 74.5, 70, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(62, 0, 40.25, 70, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(27, 0, 57, 35, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(97, 0, 57, 35, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding4 = new CMaxFile("assets/building5.dat", 1, 2, 0, 1,24);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding4;
	m_pBuilding4->SetEnableCollisions(false);
	m_pBuilding4->SetClampToTerrain(true);
	m_pBuilding4->SetClampOffset(51);

	m_pWall4 = new CWall(62, 0, 117, 70, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(62, 0, 82, 70, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(97, 0, 99, 35, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(27, 0, 99, 35, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	///////////THIS BUILDING CAN GO FUCK ITSELF.////////////////
	m_pBuilding5 = new CMaxFile("assets/building6.dat", 1, 2, 0, 1,25);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding5;
	m_pBuilding5->SetEnableCollisions(true);
	m_pBuilding5->SetClampToTerrain(true);
	m_pBuilding5->SetClampOffset(89);

	m_pBuilding6 = new CMaxFile("assets/building7.dat", 1, 2, 0, 1,26);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding6;
	m_pBuilding6->SetEnableCollisions(true);
	m_pBuilding6->SetClampToTerrain(true);
	m_pBuilding6->SetClampOffset(105);

	m_pBuilding7 = new CMaxFile("assets/building8.dat", 1, 2, 0, 1,27);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding7;
	m_pBuilding7->SetEnableCollisions(true);
	m_pBuilding7->SetClampToTerrain(true);
	m_pBuilding7->SetClampOffset(144);

	m_pBuilding7 = new CMaxFile("assets/building9.dat", 1, 2, 0, 1, 28);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding7;
	m_pBuilding7->SetEnableCollisions(true);
	m_pBuilding7->SetClampToTerrain(true);
	m_pBuilding7->SetClampOffset(105);
	
	m_pWall4 = new CWall(63, 0, 27, 69, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(63, 0, -40, 69, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	
	m_pWall4 = new CWall(28, 0, -6.5, 62, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(97, 0, -6.5, 62, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);
	
	//PUTT TREE AROUND
	
	m_pBuilding8 = new CMaxFile("assets/building10.dat", 1, 2, 0, 1,29);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding8;
	m_pBuilding8->SetEnableCollisions(true);
	m_pBuilding8->SetClampToTerrain(true);
	m_pBuilding8->SetClampOffset(57);

	m_pBuilding9 = new CMaxFile("assets/building11.dat", 1, 2, 0, 1,30);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding9;
	m_pBuilding9->SetEnableCollisions(true);
	m_pBuilding9->SetClampToTerrain(true);
	m_pBuilding9->SetClampOffset(45);

	m_pWall4 = new CWall(-64, 0, 127, 92, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-64, 0, 190, 92, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-18.5, 0, 158.5, 64, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(-110, 0, 158.5, 64, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding10 = new CMaxFile("assets/building12.dat", 1, 2, 0, 1, 31);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding10;
	m_pBuilding10->SetEnableCollisions(true);
	m_pBuilding10->SetClampToTerrain(true);
	m_pBuilding10->SetClampOffset(119);

	m_pWall4 = new CWall(-64, 0, 115, 92, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-64, 0, 46, 92, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-18.5, 0, 81.5, 69.5, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(-110, 0, 81.5, 69.5, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);


	m_pBuilding11 = new CMaxFile("assets/building13.dat", 1, 2, 0, 1,31);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding11;
	m_pBuilding11->SetEnableCollisions(false);
	m_pBuilding11->SetClampToTerrain(true);
	m_pBuilding11->SetClampOffset(95);

	m_pWall4 = new CWall(-87, 0, 33, 44.5, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-87, 0, -33, 44.5, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-65, 0, -0.5, 63, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(-108, 0, -0.5, 63, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding12 = new CMaxFile("assets/building14.dat", 1, 2, 0, 1,32);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding12;
	m_pBuilding12->SetEnableCollisions(false);
	m_pBuilding12->SetClampToTerrain(true);
	m_pBuilding12->SetClampOffset(113);

	m_pWall4 = new CWall(-85, 0, -46, 40, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-85, 0, -137.5, 40, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-65, 0, -91, 90, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(-104.5, 0, -91, 90, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding13 = new CMaxFile("assets/building15.dat", 1, 2, 0, 1,33);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding13;
	m_pBuilding13->SetEnableCollisions(false);
	m_pBuilding13->SetClampToTerrain(true);
	m_pBuilding13->SetClampOffset(117);

	m_pWall4 = new CWall(-36, 0, -64, 30, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-36, 0, 32, 30, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-22, 0, -16, 96, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(-51.5, 0, -16, 96, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding14 = new CMaxFile("assets/building16.dat", 1, 2, 0, 1,34);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding14;
	m_pBuilding14->SetEnableCollisions(false);
	m_pBuilding14->SetClampToTerrain(true);
	m_pBuilding14->SetClampOffset(75);

	m_pWall4 = new CWall(-36, 0, -73.5, 35, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-36, 0, -144, 35, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-18, 0, -108, 70, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(-54, 0, -108, 70, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding15 = new CMaxFile("assets/building17.dat", 1, 2, 0, 1,35);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding15;
	m_pBuilding15->SetEnableCollisions(false);
	m_pBuilding15->SetClampToTerrain(true);
	m_pBuilding15->SetClampOffset(25);

	m_pWall4 = new CWall(-68, 0, -154, 64, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-68, 0, -200, 64, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(-35.5, 0, -177, 46, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(-99, 0, -177, 46, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding16 = new CMaxFile("assets/building19.dat", 1, 2, 0, 1,32);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding16;
	m_pBuilding16->SetEnableCollisions(false);
	m_pBuilding16->SetClampToTerrain(true);
	m_pBuilding16->SetClampOffset(113);

	m_pWall4 = new CWall(55, 0, -200.5, 90, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(55, 0, -161.5, 90, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(100, 0, -181, 40, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(10, 0, -181, 40, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding17 = new CMaxFile("assets/building21.dat", 1, 2, 0, 1,37);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding17;
	m_pBuilding17->SetEnableCollisions(false);
	m_pBuilding17->SetClampToTerrain(true);
	m_pBuilding17->SetClampOffset(150);

	m_pWall4 = new CWall(135, 0, -159, 45, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(135, 0, -201, 45, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(111.5, 0, -180, 43, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(157, 0, -180, 43, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding18 = new CMaxFile("assets/building22.dat", 1, 2, 0, 1,40);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding18;
	m_pBuilding18->SetEnableCollisions(false);
	m_pBuilding18->SetClampToTerrain(true);
	m_pBuilding18->SetClampOffset(115);

	m_pWall4 = new CWall(75, 0, -144, 45, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(75, 0, -50, 45, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(97, 0, -97, 95, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(51, 0, -97, 95, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);


	m_pBuilding19 = new CMaxFile("assets/building23.dat", 1, 2, 0, 1,41);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding19;
	m_pBuilding19->SetEnableCollisions(false);
	m_pBuilding19->SetClampToTerrain(true);
	m_pBuilding19->SetClampOffset(25);

	m_pWall4 = new CWall(133, 0, -52, 45, 11, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(133, 0, -146, 45, 11, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(110, 0, -99, 90, 11, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(156, 0, -99, 90, 11, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding20 = new CMaxFile("assets/building24.dat", 1, 2, 0, 1,42);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding20;
	m_pBuilding20->SetEnableCollisions(false);
	m_pBuilding20->SetClampToTerrain(true);
	m_pBuilding20->SetClampOffset(100);

	m_pWall4 = new CWall(190, 0, -202, 44, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(190, 0, -159, 44, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(168.5, 0, -180, 43, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(215, 0, -180, 43, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);


	m_pBuilding21 = new CMaxFile("assets/building25.dat", 1, 2, 0, 1,42);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding21;
	m_pBuilding21->SetEnableCollisions(false);
	m_pBuilding21->SetClampToTerrain(true);
	m_pBuilding21->SetClampOffset(100);

	m_pWall4 = new CWall(191, 0, -102, 44, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(191, 0, -148, 44, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(170, 0, -125, 44, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);
	
	m_pWall4 = new CWall(213, 0, -125, 44, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pBuilding21 = new CMaxFile("assets/building26.dat", 1, 2, 0, 1,43);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding21;
	m_pBuilding21->SetEnableCollisions(false);
	m_pBuilding21->SetClampToTerrain(true);
	m_pBuilding21->SetClampOffset(125);

	m_pWall4 = new CWall(191, 0, -95, 44, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(191, 0, -52, 44, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);

	m_pWall4 = new CWall(168, 0, -73, 43, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);

	m_pWall4 = new CWall(214.5, 0, -73, 43, 10, 1, 1);
	//float x_, float y_, float z_,float w_, float h_, float d_, int textureID_
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pWall4;
	m_pWall4->SetClampToTerrain(true);
	m_pWall4->SetYaw(90);
	
	//PLACE TREES AROUND THIS ONEvvvv///

	m_pBuilding22 = new CMaxFile("assets/building27.dat", 1, 2, 0, 1,43);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pBuilding22;
	m_pBuilding22->SetEnableCollisions(false);
	m_pBuilding22->SetClampToTerrain(true);
	m_pBuilding22->SetClampOffset(1);

	m_pRoad2 = new CMaxFile("assets/road2.dat", 1, 2, 0, 1,44);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pRoad2;
	m_pRoad2->SetEnableCollisions(false);
	m_pRoad2->SetClampToTerrain(true);
	m_pRoad2->SetClampOffset(0.1);

	m_pRoad1 = new CMaxFile("assets/road1.dat", 1, 2, 0, 1,44);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pRoad1;
	m_pRoad1->SetEnableCollisions(false);
	m_pRoad1->SetClampToTerrain(true);
	m_pRoad1->SetClampOffset(0.001);

	m_pRoad1 = new CMaxFile("assets/paths.dat", 1, 2, 0, 1,17);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pRoad1;
	m_pRoad1->SetEnableCollisions(false);
	m_pRoad1->SetClampToTerrain(true);
	m_pRoad1->SetClampOffset(0.01);

	/*m_pPortal = new CEndGame("assets/endPortalModel.dat", 1, 2, 0, 1,61);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pPortal;
	m_pPortal->SetEnableCollisions(true);
	m_pPortal->SetClampToTerrain(true);
	m_pPortal->SetClampOffset(1);*/

	/*m_pRoad2 = new CMaxFile("assets/roadBlock.dat", 1, 2, 0, 1,17);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pRoad2;
	m_pRoad2->SetEnableCollisions(false);
	m_pRoad2->SetClampToTerrain(true);
	m_pRoad2->SetClampOffset(1.5);

	m_pRoad3 = new CMaxFile("assets/roadBlock2.dat", 1, 2, 0, 1,17);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pRoad3;
	m_pRoad3->SetEnableCollisions(false);
	m_pRoad3->SetClampToTerrain(true);
	m_pRoad3->SetClampOffset(1.5);*/

	m_pshotGun=new CMaxFile("assets/Shotgun.dat",2,0,0.5,3,39);
	m_pshotGun->SetClampToTerrain(true);
	m_pshotGun->SetEnableCollisions(false);
	m_pshotGun->SetYaw(0);

	m_psubGun = new CMaxFile("assets/minigun.dat",2, 0, 0.5,3,38);
	m_psubGun->SetClampToTerrain(true);
	m_psubGun->SetEnableCollisions(false);
	m_psubGun->SetYaw(90);

	//hud graphics
	m_pHUDCrosshair=new CSprite(0,0,1,1,18);
	m_pHUDHealth=new CSprite(-6,-4,2,2,20);
	m_pHUDAmmo9=new CSprite(6,-4,2,2,45);
	m_pHUDAmmo8=new CSprite(6,-4,2,2,50);
	m_pHUDAmmo7=new CSprite(6,-4,2,2,51);
	m_pHUDAmmo6=new CSprite(6,-4,2,2,52);
	m_pHUDAmmo5=new CSprite(6,-4,2,2,53);
	m_pHUDAmmo4=new CSprite(6,-4,2,2,54);
	m_pHUDAmmo3=new CSprite(6,-4,2,2,55);
	m_pHUDAmmo2=new CSprite(6,-4,2,2,56);
	m_pHUDAmmo1=new CSprite(6,-4,2,2,57);
	m_pHUDAmmoReload=new CSprite(6,-4,2,2,58);
	m_pMENUStart = new CSprite(0,0,15,11,47);
	m_pMENUInstructions = new CSprite(0,0,15,11,46);
	m_pMENUWin = new CSprite(0,0,15,11,59);
	m_pMENULose = new CSprite(0,0,15,11,60);

	for (int i = 0; i < 5; i++)
	{

		//AmmoCrate class that inherits from maxfile
		m_pAmmoCrate2 = new CAmmoCrate("assets/AmmoCrate.dat", -10, 0, i * 5, 0.03, 48);
		m_pAmmoCrate2->SetClampOffset(1);
		m_pAmmoCrate2->SetClampToTerrain(true);
		m_pAmmoCrate2->SetEnableCollisions(true);
		m_p3dObjects[m_i3dObjectsLoaded++] = m_pAmmoCrate2;

	}

	m_pPortal = new CEndGame("assets/endPortalModel.dat", 200,0,-225,1,61);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pPortal;
	m_pPortal->SetEnableCollisions(true);
	m_pPortal->SetClampToTerrain(true);
	m_pPortal->SetClampOffset(2);
	

	for (int i=0;i<50;i++)
	{
		float size=3+0.3*(rand()%10);
		m_p3dObjects[m_i3dObjectsLoaded++]=new CEnemyBillboard(-40+rand()%350,2,-40+rand()%350,size,size,1,11,true,2,2,5,false);
	}
	for (int i=0;i<2;i++)
	{
		float size=3+0.3*(rand()%10);
		m_p3dObjects[m_i3dObjectsLoaded++]=new CEnemyBillboardFire(-40+rand()%350,2,-40+rand()%350,size,size,1,11,true,2,2,5,false);
	}
	m_ideath = 0;
}

//destructor destroys all loaded 3dObjects
CGame::~CGame(void)
{
	for (int i=0;i<m_i3dObjectsLoaded;i++)
	{
		delete m_p3dObjects[i];
		m_p3dObjects[i]=0;
	}
}

//doframe method iterates through all 3dObjects and 
//updates and renders them

void
CGame::DoFrame()
{
	//setup the light
	//m_p3dObjects[m_i3dObjectsLoaded++]=new CLight(m_fX,m_fY,m_fZ);

	//refresh input
	CInput::Instance()->GetInput();
	float dt=CTimer::Instance()->Getdt();

	if (m_eGameState == eGameStateMenu) // if the game state is menu then sdo the following
	{ 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-7, 7, -5, 5);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		m_pMENUStart->render(); //shows the specific background
		 if (CInput::Instance()-> GetIfKeyDown(DIK_P)) // if it is in menu state and the space is pressed then do the following
		{
			m_eGameState = CGame::eGameStatePlay; // Go to the play game state
		}
		 if  (CInput::Instance()-> GetIfKeyDown(DIK_I)) // if it is in menu state and the space is pressed then do the following
		{
			m_eGameState = CGame::eGameStateInstructions; // Go to the instructions panel
		}
		 if  (CInput::Instance()-> GetIfKeyDown(DIK_E)) // if it is in menu state and the space is pressed then do the following
		{
			exit(0); // Exit the game
		}
	}

	if (m_eGameState == eGameStateInstructions)
	{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			m_pMENUInstructions->render(); //shows the specific background
			if (CInput::Instance()-> GetIfKeyDown(DIK_P)) // if it is in menu state and the space is pressed then do the following
			{
				m_eGameState = CGame::eGameStatePlay; // go to the game state play
			}
			if  (CInput::Instance()-> GetIfKeyDown(DIK_M)) // if it is in menu state and the space is pressed then do the following
			{
				m_eGameState = CGame::eGameStateMenu; // go to the game state play
			}
		}
		
		if (m_eGameState == eGameStatePlay) // if the game state is play then do the following
		{

			stringstream strs;
			strs << m_enemiesKilled;
			string temp_str = strs.str();
			char* char_type = (char*) temp_str.c_str();
			
			// Output text to screen
			CText::RenderBitmapString(500, 450, "Enemies Killed:");
			CText::RenderBitmapString(580,450, char_type);
			
			if(b_isMusicPlayingMainGame == false)
			{
				CAudio::Instance()->StopCue(p_CurrentAudioCue);
				p_CurrentAudioCue = CAudio::Instance()->Play(2);
				p_CurrentAudioCue = CAudio::Instance()->Play(0);
				b_isMusicPlayingMainGame = true;
			}

		if (CInput::Instance()-> GetIfKeyDownEvent(DIK_1))
		{
			b_shotgunSelected = true;
			b_p90Selected = false;
		}
		else if(CInput::Instance()-> GetIfKeyDownEvent(DIK_2))
		{
			b_shotgunSelected = false;
			b_p90Selected = true;
		}

		//update all 3dObjects
		for (int i=0;i<m_i3dObjectsLoaded;i++)
		{
			m_p3dObjects[i]->Update(dt);
		}

		//render all 3dObjects
		for (int i=0;i<m_i3dObjectsLoaded;i++)
		{
			m_p3dObjects[i]->Render();
		}

		//render gun last
		glClear(GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glLoadIdentity();
			gluLookAt(0,3,5,0,3,0,0,1,0);
			// All gun render's are placed in this glIdentity 
			if(b_shotgunSelected == true)
			{
				m_pshotGun->Render();
			}
			else if(b_p90Selected == true)
			{	
				m_psubGun->Render();		
			}
		glPopMatrix();

		//sets the glu to orthagraphic
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-7, 7, -5, 5);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		//render the HUD graphics
		m_pHUDCrosshair->render();
		m_pHUDHealth->render();
		
		//set it back to perspective
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,1.33,0.1f,1000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//easy enough from here to do stuff like ammo decreasing etc but didn't want to as i don't know specfics 
		//this relates to the main game loop
		// get input
		// update all objects
		// render the scene

		//check for deletions
		for (int i=0;i<m_i3dObjectsLoaded;i++)
		{
			if (m_p3dObjects[i]->bTaggedForDeletion)
			{	
				//delete item at current position
				delete m_p3dObjects[i];
				//move last item into current position
				m_p3dObjects[i]=m_p3dObjects[m_i3dObjectsLoaded-1];
				//set last item to 0
				m_p3dObjects[m_i3dObjectsLoaded]=0;
				//reduce count
				m_i3dObjectsLoaded--;
			}
		}

		// Fog (may need to change and place it in render)
		if (!b_wireframeMode)
		{
			int fogMode = GL_EXP;
			float fogDensity = 0.005; // for density
			float fogStart = 0.0; // Fog start z value.
			float fogEnd = 100.0; // Fog end z value.
			float fogColor[4] = {0.5, 0.5, 0.5, 1.0}; // grey {0.5, 0.5, 0.5, 1.0};

			glEnable(GL_FOG);
			glHint(GL_FOG_HINT, GL_NICEST);
			glFogfv(GL_FOG_COLOR, fogColor);
			glFogi(GL_FOG_MODE, fogMode);
			glFogf(GL_FOG_START, fogStart);
			glFogf(GL_FOG_END, fogEnd);
			glFogf(GL_FOG_DENSITY, fogDensity);
		}
		else
		{
			glDisable(GL_FOG);
		}

 		if (m_pCamera->m_fBullets==9)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pHUDAmmo9->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
		
		if (m_pCamera->m_fBullets==8)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pHUDAmmo8->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		if (m_pCamera->m_fBullets==7)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pHUDAmmo7->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		if (m_pCamera->m_fBullets==6)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pHUDAmmo6->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		if (m_pCamera->m_fBullets==5)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pHUDAmmo5->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		if (m_pCamera->m_fBullets==4)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pHUDAmmo4->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		if (m_pCamera->m_fBullets==3)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pHUDAmmo3->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		if (m_pCamera->m_fBullets==2)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pHUDAmmo2->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		if (m_pCamera->m_fBullets==1)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pHUDAmmo1->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		if (m_pCamera->m_fBullets<=1)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pHUDAmmoReload->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		if(m_ideath == 1)
		{
			CAudio::Instance()->StopCue(p_CurrentAudioCue);
			m_eGameState = CGame::eGameStateLose;

		}

		if(m_iwin == 1)
		{
			CAudio::Instance()->StopCue(p_CurrentAudioCue);
			m_eGameState = CGame::eGameStateWin;

		}


	}

	if (m_eGameState == eGameStateLose) // if the game state is play then do the following
	{

		stringstream strs;
		strs << m_enemiesKilled;
		string temp_str = strs.str();
		char* char_type = (char*)temp_str.c_str();

		// Output text to screen
		CText::RenderBitmapString(500, 450, "Enemies Killed:");
		CText::RenderBitmapString(580, 450, char_type);

		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pMENULose->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			CAudio::Instance()->StopCue(p_CurrentAudioCue);




			if (CInput::Instance()->GetIfKeyDown(DIK_R))
			{
				m_enemiesKilled = 0;
				m_i3dObjectsLoaded = 0;
				m_iwin = 0;
				m_ideath = 0;
				m_eGameState = CGame::eGameStateMenu;

				CAudio::Instance()->StopCue(p_CurrentAudioCue);
				p_CurrentAudioCue = CAudio::Instance()->Play(1);
				
			}
	}
	if (m_eGameState == eGameStateWin) // if the game state is play then do the following
	{
		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-7, 7, -5, 5);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m_pMENUWin->render(); //shows the specific background

			//set it back to perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,1.33,0.1f,1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			if  (CInput::Instance()-> GetIfKeyDown(DIK_R)) // if it is in menu state and the space is pressed then do the following
			{	
				//m_iwin=0;
				//for (int i = 0; i< sizeof(m_p3dObjects); i++)
				//{
				//	m_p3dObjects[i] = 0; // delete contents of array before loading game
				//	char msg[] = "jksdhs";
				//	OutputDebugString(msg);
				//}
				CGame::Begin();// go to the game state play
			}
	}
}

void
CGame::HandleMouseMove(float xrel_,float yrel_)
{
	//yaw camera according to distance from centre
	// look Left and right
	m_pCamera->IncrementYaw(30*(xrel_-0.5));

	// look up and down
	m_pCamera->IncrementPitch(-30*(yrel_-0.5));
}

C3dObject *
CGame::GetObjectByIndex(int i)
{
	return m_p3dObjects[i];
}

void
CGame::AddObject( C3dObject * object_)
{
	m_p3dObjects[m_i3dObjectsLoaded++]= object_;
}