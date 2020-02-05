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
  
  //funkcje kontroli g�o�no�ci
  void SetVolume(long aVol);
  float GetVolume();
	
	//funkcje poruszania si� po pliku
	__int64 GetCurrentPosition();
  void SetPositions(__int64* iCurrent, __int64* iPause, bool bAbsolutePositioning);
  
  // czy plik audio jest gotowy
  bool  isReady;
  // czy plik audio jest odtwarzany
  bool  isPlaying;
  // D�ugo�� pliku audio
  __int64 audioDuration;

private:
	//interfejsy Direct Show
  //IGraphBuilder buduje 
  IGraphBuilder*  audioBuild;
  //IMediaControl daje podstawow� kontrol�
	IMediaControl*  audioControl;
  //IBasicAudio obs�uguje g�o�no�� 
	IBasicAudio* audioVolume;
	ISimpleAudioVolume * audioVolumeNew;
  //IMediaSeeking obs�uguje poruszanie sie po pliku
  IMediaSeeking * audioMove;
};