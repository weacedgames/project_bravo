#ifndef AUDIO_FILE_H
#define AUDIO_FILE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

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
    AudioFile(std::string setFileName, int setAssetAudioID);
    void play_audio();
};

#endif