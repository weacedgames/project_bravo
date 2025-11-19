#ifndef AUDIO_FILE_H
#define AUDIO_FILE_H

#include <iostream>
#include <vector>
#include <fstream>

#include <windows.h>
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <functiondiscoverykeys.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#pragma pack(push, 1)


struct RiffHeader {
    char id[4];
    uint32_t size;
    char format[4];
};

struct FmtChunkBase {
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};

#pragma pack(pop) 

struct WavInfo {
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint16_t bitsPerSample;
    uint32_t dataOffset;
    uint32_t dataSize;
};


class AudioFile
{
public:
    std::string assetFileName;
    int assetAudioID;

public:
    WavInfo audioWavInfo;
    std::vector<float> audioData;

public:
    AudioFile(std::string setFileName, int setAssetAudioID)
    { 
        assetFileName = setFileName;
        assetAudioID = setAssetAudioID;

        std::ifstream file_read(setFileName, std::ios::binary);
        
        if (!file_read)
        {
            std::cerr << "ERROR::OPENING_AUDIO_FILE" << std::endl;
        }

        RiffHeader riff;
        file_read.read(reinterpret_cast<char*>(&riff), sizeof(riff));

        if (strncmp(riff.id, "RIFF", 4) != 0 || strncmp(riff.format, "WAVE", 4) != 0)
        {
            std::cerr << "ERROR::NOT_VALID_AUDIO_FILE" << std::endl;
        }

        while(file_read) 
        {
            char chunkId[4];
            uint32_t chunkSize;

            if (!file_read.read(chunkId, 4)) break;
            if (!file_read.read(reinterpret_cast<char*>(&chunkSize), 4)) break;

            if (strncmp(chunkId, "fmt ", 4) == 0) 
            {
                FmtChunkBase fmt;
                file_read.read(reinterpret_cast<char*>(&fmt), sizeof(fmt));

                audioWavInfo.audioFormat   = fmt.audioFormat;
                audioWavInfo.numChannels   = fmt.numChannels;
                audioWavInfo.sampleRate    = fmt.sampleRate;
                audioWavInfo.bitsPerSample = fmt.bitsPerSample;

                if (chunkSize > sizeof(FmtChunkBase)) 
                    file_read.seekg(chunkSize - sizeof(FmtChunkBase), std::ios::cur);
            }

            else if (strncmp(chunkId, "data", 4) == 0) 
            {
                audioWavInfo.dataSize = chunkSize;
                audioWavInfo.dataOffset = static_cast<uint32_t>(file_read.tellg());
                break;
            }

            else 
            {
                file_read.seekg(chunkSize + (chunkSize % 2), std::ios::cur);
            }
        }

        std::vector<char> fileData(audioWavInfo.dataSize);

        file_read.seekg(audioWavInfo.dataOffset, std::ios::beg);
        file_read.read(fileData.data(), audioWavInfo.dataSize);

        if (!file_read)
        {
            std::cerr << "ERROR::FAILED_TO_READ_FULL_AUDIO_DATA" << std::endl;
        }

        if(audioWavInfo.bitsPerSample == 8)
        { 
            size_t numSamples = fileData.size();
            audioData.resize(numSamples);

            for( size_t i=0; i<numSamples; i++)
            {
                uint8_t sample8 = static_cast<uint8_t>(fileData[i]);
                int signedSample = sample8 - 128;
                audioData[i] = signedSample / 128.0f;
            }
        }

        if(audioWavInfo.bitsPerSample == 16)
        {
            size_t numSamples = fileData.size() / 2;
            audioData.resize(numSamples);

            for(size_t i=0; i<numSamples; i++)
            {
                uint8_t byteL = static_cast<uint8_t>(fileData[2 * i]);
                uint8_t byteH = static_cast<uint8_t>(fileData[2 * i + 1]);
                int16_t sample16 = byteL | (byteH << 8);
                audioData[i] = sample16 / 32768.0f;
            }
        }

        if(audioWavInfo.bitsPerSample == 32)
        {
            if(audioWavInfo.audioFormat == 3)
            {
                size_t numSamples = fileData.size() / sizeof(float);
                audioData.resize(numSamples);
                std::memcpy(audioData.data(), fileData.data(), fileData.size());
            }
            else
            {
                size_t numSamples = fileData.size() / 4;
                audioData.resize(numSamples);

                for(size_t i = 0; i < numSamples; i++)
                {
                    uint8_t b0 = static_cast<uint8_t>(fileData[4 * i]);
                    uint8_t b1 = static_cast<uint8_t>(fileData[4 * i + 1]);
                    uint8_t b2 = static_cast<uint8_t>(fileData[4 * i + 2]);
                    uint8_t b3 = static_cast<uint8_t>(fileData[4 * i + 3]);

                    int32_t sample32 = b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
                    audioData[i] = sample32 / 2147483648.0f;
                }
            }
        }
    };

    void play_audio()
    {
        PlaySoundA( assetFileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    };

};

#endif