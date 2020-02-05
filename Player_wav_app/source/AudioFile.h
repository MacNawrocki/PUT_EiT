#include <Windows.h>
#include <mmsystem.h>
#include <strmif.h>
#include <control.h>
#include <Audioclient.h>
#include <dshow.h>
#include <mmdeviceapi.h>

class AudioFile
{
public:
  AudioFile();
	~AudioFile();
  void Cleanup();
  
  //funkcja Budowy
	void Load(LPCWSTR audioFileName);
  
  //funkcje Kontroli
  void Play();
  void Pause();
	void Stop();
  
  //funkcje kontroli g³oœnoœci
  void SetVolume(long aVol);
  float GetVolume();
	
	//funkcje poruszania siê po pliku
	__int64 GetCurrentPosition();
  void SetPositions(__int64* iCurrent, __int64* iPause, bool bAbsolutePositioning);
  
  // czy plik audio jest gotowy
  bool  isReady;
  // czy plik audio jest odtwarzany
  bool  isPlaying;
  // D³ugoœæ pliku audio
  __int64 audioDuration;

private:
	//interfejsy Direct Show
  //IGraphBuilder buduje 
  IGraphBuilder*  audioBuild;
  //IMediaControl daje podstawow¹ kontrolê
	IMediaControl*  audioControl;
  //IBasicAudio obs³uguje g³oœnoœæ 
	IBasicAudio* audioVolume;
	ISimpleAudioVolume * audioVolumeNew;
  //IMediaSeeking obs³uguje poruszanie sie po pliku
  IMediaSeeking * audioMove;
};