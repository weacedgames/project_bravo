#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <audioclient.h>
#include <mmdeviceapi.h>

#include "audio_file.h"


#pragma comment(lib, "winmm.lib")


class Audio : public std::enable_shared_from_this<Audio>
{
public:
    IMMDeviceEnumerator* m_pEnumerator = nullptr;
    IMMDevice* m_pDevice = nullptr;
    IAudioClient* m_pAudioClient = nullptr;
    WAVEFORMATEX* m_pwfx = nullptr;
    IAudioRenderClient* m_pRenderClient = nullptr;

    UINT32 bufferFrameCount = 0;

public:
    Audio()
    {
        initialize();
    };

    ~Audio()
    {
        if(m_pwfx)
        {
            CoTaskMemFree(m_pwfx);
            m_pwfx = nullptr;
        }
        if(m_pAudioClient)
        {
            m_pAudioClient->Release();
            m_pAudioClient = nullptr;
        }
        if(m_pDevice)
        {
            m_pDevice->Release();
            m_pDevice = nullptr;
        }
        if(m_pEnumerator)
        {
            m_pEnumerator->Release();
            m_pEnumerator = nullptr;
        }
        if(m_pRenderClient)
        {
            m_pRenderClient->Release();
            m_pRenderClient = nullptr;
        }
    };

    HRESULT initialize()
    {
        HRESULT hr = S_OK;

        // Create the device enumerator
        hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,__uuidof(IMMDeviceEnumerator),(void**)&m_pEnumerator);
        if (FAILED(hr))
        {
            std::cerr << "Failed to create MMDeviceEnumerator: hr = " << std::hex << hr << "\n";
        }

        // Get default audio endpoint (render example)
        hr = m_pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &m_pDevice);
        if (FAILED(hr))
        {
            std::cerr << "GetDefaultAudioEndpoint failed: hr = " << std::hex << hr << "\n";
        }

        // Activate IAudioClient
        hr = m_pDevice->Activate(__uuidof(IAudioClient),CLSCTX_ALL,nullptr,(void**)&m_pAudioClient);
        if (FAILED(hr))
        {
            std::cerr << "Device Activate IAudioClient failed: hr = " << std::hex << hr << "\n";
        }


        // Get the mix format
        hr = m_pAudioClient->GetMixFormat(&m_pwfx);
        m_pwfx->wFormatTag = WAVE_FORMAT_PCM;
        m_pwfx->wBitsPerSample = 16;
        m_pwfx->nBlockAlign = m_pwfx->nChannels * (m_pwfx->wBitsPerSample /8);
        m_pwfx->nAvgBytesPerSec = m_pwfx->nSamplesPerSec * m_pwfx->nBlockAlign;
        m_pwfx->cbSize = 0;
        if (FAILED(hr))
        {
            std::cerr << "GetMixFormat failed: hr = " << std::hex << hr << "\n";
        }

        // Initialize the audio client (shared mode, no event, etc.)
        hr = m_pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED,0,10000000,0,m_pwfx,nullptr);
        if (FAILED(hr))
        {
            std::cerr << "IAudioClient Initialize failed: hr = " << std::hex << hr << "\n";
        }

        hr = m_pAudioClient->GetService(__uuidof(IAudioRenderClient),reinterpret_cast<void**>(&m_pRenderClient));
        if (FAILED(hr))
        {
            std::cerr << "IAudioRenderClient Initialize failed: hr = " << std::hex << hr << "\n";
        }

        hr = m_pAudioClient->GetBufferSize(&bufferFrameCount);
        if(FAILED(hr))
        {
            std::cerr << "GetBufferSize Failed: hr=" << std::hex << hr << "\n";
        }

        return hr;
    };
    
    void play(std::vector<float> audioData)
    {
        size_t totalFrames = audioData.size() / m_pwfx->nChannels;
        size_t currentFrame = 0;

        m_pAudioClient->Start();

        while(currentFrame < totalFrames)
        {
            UINT32 padding = 0;
            m_pAudioClient->GetCurrentPadding(&padding);

            UINT32 framesAvailable = bufferFrameCount - padding;

            if(framesAvailable == 0)
            {
                Sleep(1);
                continue;
            }

            UINT32 framesToWrite = (UINT32)std::min<size_t>(framesAvailable, totalFrames - currentFrame);

            int16_t* pData = nullptr;

            HRESULT hr = S_OK;
            hr = m_pRenderClient->GetBuffer(framesToWrite, (BYTE**)&pData);

            if(FAILED(hr)) break;

            for(UINT32 i=0; i<framesToWrite*m_pwfx->nChannels; i++)
            {
                    float f = audioData[(currentFrame * m_pwfx->nChannels) + i];
                    if(f > 1.0f) f = 1.0f;
                    if(f < -1.0f) f = -1.0f;

                    pData[i] = static_cast<int16_t>(f * 32767.0f);
            }

            m_pRenderClient->ReleaseBuffer(framesToWrite, 0);
            currentFrame += framesToWrite;
        }

        Sleep(200);
        m_pAudioClient->Stop();
    };
};

#endif