#include "AudioFile.h"
#include <wmsdkidl.h>
#include <uuids.h>
#include <Unknwn.h>
#include <dshow.h>
#include <mmdeviceapi.h>

AudioFile::AudioFile()
{
  audioBuild = NULL;
  audioControl = NULL;
  audioVolume = NULL;
  audioMove = NULL;
  isReady = false;
  isPlaying = false;
  audioDuration = 0;
}

AudioFile::~AudioFile()
{
	Cleanup();
}

void AudioFile::Cleanup()
{
	if(audioBuild)
	{
    audioBuild->Release();
    audioBuild = NULL;
	}

  if (audioControl)
  {
    audioControl->Stop();
    audioControl->Release();
    audioControl = NULL;
  }

	if(audioVolume)
	{
    audioVolume->Release();
    audioVolume = NULL;
	}

	if(audioMove)
	{
    audioMove->Release();
    audioMove = NULL;
	}
  audioDuration = 0;
  isReady = false;
  isPlaying = false;
}

void AudioFile::Load(LPCWSTR audioFileName)
{
	Cleanup();
  isReady = false;
  if (SUCCEEDED(CoCreateInstance( CLSID_FilterGraph,
	NULL,
	CLSCTX_INPROC_SERVER,
	IID_IGraphBuilder,
	(void **)&this->audioBuild)))
	{
    audioBuild->QueryInterface(IID_IMediaControl, (void **)&audioControl);
    audioBuild->QueryInterface(IID_IBasicAudio, (void**)&audioVolume);
    audioBuild->QueryInterface(IID_IMediaSeeking, (void**)&audioMove);
	//audioBuild->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&audioVolumeNew);
	//CoInitialize(NULL);
	//IMMDeviceEnumerator* pMmDeviceEnumerator;
	//HRESULT hx = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pMmDeviceEnumerator));
	//IMMDevice* pMmDevice;
	//pMmDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pMmDevice);
	//IAudioClient* pAudioClient;
	//pMmDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (VOID**)&pAudioClient);
	//ISimpleAudioVolume* pSimpleAudioVolume;
	//pAudioClient->GetService(__uuidof(ISimpleAudioVolume), (VOID**)&pSimpleAudioVolume);
	//pSimpleAudioVolume->SetMasterVolume(0.50f, NULL);
	//pAudioClient->Start();
	HRESULT hr = audioBuild->RenderFile(audioFileName, NULL);
		if (SUCCEEDED(hr))
		  {
      isReady = true;
			if(audioMove)
			 {
       audioMove->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
       audioMove->GetDuration(&audioDuration);
       audioDuration = audioDuration/100;
       }
		  }
	}
}

void AudioFile::Play()
{
	if (isReady&&audioControl)
	{
		audioControl->Run();
    isPlaying = true;
	}
}

void AudioFile::Pause()
{
	if (isReady&&audioControl)
	{
		audioControl->Pause();
    isPlaying = false;
	}
}

void AudioFile::Stop()
{
	if (isReady&&audioControl)
	{
		HRESULT hr = audioControl->Stop();
	}
}

void AudioFile::SetVolume(long aVol)
{
	if (isReady&&audioVolume)
	{
		audioVolume->put_Volume(aVol);
	}
}

float AudioFile::GetVolume()
{
	if (isReady&&audioVolume)
	{
		long aVol = 500;
		HRESULT hr = audioVolume->get_Volume(&aVol);
		if(SUCCEEDED(hr)) return aVol;
	}
//	if (isReady)
//	{
//		float aVol = 500;
//		HRESULT hr = audioVolumeNew->GetMasterVolume(&aVol);
//		if (SUCCEEDED(hr)) return aVol;
//		else return 666;
//	}
	return 10;
}

__int64 AudioFile::GetCurrentPosition()
{
	if (isReady&&audioMove)
	{
		__int64 aCurPos = 0;
		HRESULT hr = audioMove->GetCurrentPosition(&aCurPos);
		if(SUCCEEDED(hr)) return aCurPos / 100;
	}
	return 0;
}

void AudioFile::SetPositions(__int64* aCurrentPos, __int64* aStopPos, bool bAbsolutePositioning)
{
	if (isReady&&audioMove)
	{
		DWORD aFlags = 0;
		if(bAbsolutePositioning)
      aFlags = AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame;
		else
      aFlags = AM_SEEKING_RelativePositioning | AM_SEEKING_SeekToKeyFrame;
		audioMove->SetPositions(aCurrentPos, aFlags, aStopPos, aFlags);
	}
}                           