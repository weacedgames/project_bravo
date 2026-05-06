#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <thread>

#include "audio_file.h"


#pragma comment(lib, "winmm.lib")

// A voice in audio game is like a channel, one snippet of audio wav is a single voice
// You can goto Halo 2 and 3 Documentaries and hear the auido engineer mention how to audio engine works with voices 
// Bottom line we are creating a struct fot that voice

struct Voice
{
    std::vector<float> audioData;
    bool active = false;
    size_t cursor = 0;
    float strength = 1.0f;
};

class Audio
{
public:
    IMMDeviceEnumerator* m_pEnumerator = nullptr;
    IMMDevice* m_pDevice = nullptr;
    IAudioClient* m_pAudioClient = nullptr;
    WAVEFORMATEX* m_pwfx = nullptr;
    IAudioRenderClient* m_pRenderClient = nullptr;
    UINT32 bufferFrameCount = 0;

public:

    Voice voice_1;
    Voice voice_2;

public:
    Audio(std::vector<float> channel_1_audioData, std::vector<float> channel_2_audioData);
    ~Audio();
    HRESULT initialize();
    void play(std::vector<float> audioData);
    void start();
};

#endif