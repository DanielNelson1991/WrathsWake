#pragma once
#include "xact3.h"
#include "Xact3d3.h"

class CAudio
{
public:
	CAudio(void);
	~CAudio(void);

	static CAudio * Instance();
	static void Destroy();
	void Update();
	IXACT3Cue  * Play(int wavNumber=0);
	IXACT3Cue  * Play3d( float x_=0.0f, float y_=0.0f, float z_=0.0f,int wavNumber=0);
	void StopCue(IXACT3Cue  * cue);
	void SetListenerPosition(float x_,float y_, float z_);

private:
	void Initialize();
	void ShutDown();

	IXACT3WaveBank * m_pWaveBank;
	IXACT3SoundBank * m_pSoundBank;

	VOID* m_pSoundBankData;
	VOID* m_pWaveBankData;

	static CAudio * _instance;
	IXACT3Engine * m_pXACT3Engine;
	X3DAUDIO_HANDLE  m_pXACT3DInstance;
};
