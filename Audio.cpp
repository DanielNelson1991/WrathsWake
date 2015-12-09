#include "stdafx.h"
#include "Audio.h"

#pragma comment(lib,"X3DAudio.lib")

CAudio::CAudio(void)
{
	Initialize();
}

CAudio::~CAudio(void)
{
	ShutDown();
}


void
CAudio::Initialize()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//initialize XACT
	HRESULT  hr;
	
	if ( FAILED ( hr = XACT3CreateEngine( 0, &m_pXACT3Engine ) ) ) 
	{
		return ;
	}

	XACT_RUNTIME_PARAMETERS EngineParameters = {0};
	
	if ( FAILED ( hr = m_pXACT3Engine->Initialize( &EngineParameters ) ) )
	{
		return ;
	}


	//http://msdn.microsoft.com/en-us/library/ee416190.aspx
	//TODO: get 3d audio working
	hr=XACT3DInitialize(m_pXACT3Engine,m_pXACT3DInstance);

	//read a wavebank from disk
	HANDLE hFile = CreateFile("assets/Wave Bank.xwb", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);  
	DWORD dwFileSize = GetFileSize(hFile , NULL);  
	DWORD dwBytesRead;
	m_pWaveBankData = new BYTE [dwFileSize];  
	ReadFile(hFile, m_pWaveBankData, dwFileSize, &dwBytesRead, NULL);  
	hr = m_pXACT3Engine->CreateInMemoryWaveBank(m_pWaveBankData, dwFileSize, 0, 0, &m_pWaveBank); 

	HANDLE hSBFile = CreateFile("assets/Sound Bank.xsb", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);  
	DWORD dwSBFileSize = GetFileSize(hSBFile , NULL);  
	m_pSoundBankData = new BYTE [dwSBFileSize];  
	ReadFile(hSBFile, m_pSoundBankData, dwSBFileSize, &dwBytesRead, NULL);
	hr = m_pXACT3Engine->CreateSoundBank(m_pSoundBankData, dwSBFileSize, 0, 0, &m_pSoundBank);  


	//now we have a wavebank, lets play wave #1
	//IXACT3Wave * ppWave;
	//m_pWaveBank->Play(0, NULL, 0, 1, &ppWave);
	//Play(0);

}

void
CAudio::ShutDown()
{

    
// Release XACT interfaces      
if( m_pSoundBank )
	{
		m_pSoundBank->Destroy();  
	}

if( m_pWaveBank )          
	{
	m_pWaveBank->Destroy();
	}

// Shut down XACT     
m_pXACT3Engine->ShutDown();        
		
// Release memory mapped files      
if( m_pSoundBankData )
	{
	UnmapViewOfFile( m_pSoundBankData );
	delete m_pSoundBankData;
	}




if( m_pWaveBankData )
	{
	UnmapViewOfFile( m_pWaveBankData ); 
	delete m_pWaveBankData;
	}

}

//returns a pointer to the playing cue
//which can be used to stop the sound
IXACT3Cue  *
CAudio::Play(int wavNumber)
{
	IXACT3Cue  * ppCue;
	m_pSoundBank->Play(wavNumber, NULL, 0, &ppCue);
	return ppCue;
}

//plays a sound using 3d audio
IXACT3Cue  * 
CAudio::Play3d( float x_, float y_, float z_,int wavNumber)
{
	/*X3DAUDIO_DSP_SETTINGS DSPSettings = {0};

    WAVEFORMATEXTENSIBLE format;
    m_pXACT3Engine->GetFinalMixFormat(&format);

    DSPSettings.SrcChannelCount = srcChannelCount;
    DSPSettings.DstChannelCount = format.Format.nChannels;    
    DSPSettings.pMatrixCoefficients = new FLOAT32[DSPSettings.SrcChannelCount * DSPSettings.DstChannelCount];*/



	IXACT3Cue  * ppCue;
	m_pSoundBank->Play(wavNumber, NULL, 0, &ppCue);
	return ppCue;
}

//stops a specified cue from playing
void
CAudio::StopCue(IXACT3Cue * pCue_)
{
	pCue_->Stop(XACT_FLAG_CUE_STOP_IMMEDIATE);
}

void
CAudio::Update()
{
	m_pXACT3Engine->DoWork();
}



CAudio * CAudio::Instance()
{
	if (0==_instance)
	{
		_instance=new CAudio();
		atexit(Destroy);
	}
	return _instance;
}

void
CAudio::Destroy()
{
	delete _instance;
}

CAudio * CAudio::_instance=0;