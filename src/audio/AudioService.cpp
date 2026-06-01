#include "AudioService.h"

#include <iostream>

namespace tetris
{
    namespace
    {
        const char *pathString(const std::filesystem::path &path)
        {
            static thread_local std::string value;
            value = path.string();
            return value.c_str();
        }

        void logMissingAsset(const std::filesystem::path &path)
        {
            if (!FileExists(pathString(path)))
            {
                std::cerr << "Missing asset: " << path << '\n';
            }
        }
    }

    AudioService::AudioService(const ResourcePaths &resourcePaths)
    {
        InitAudioDevice();

        const auto musicPath = resourcePaths.sound("music.mp3");
        const auto rotatePath = resourcePaths.sound("rotate.mp3");
        const auto clearPath = resourcePaths.sound("clear.mp3");

        logMissingAsset(musicPath);
        logMissingAsset(rotatePath);
        logMissingAsset(clearPath);

        music_ = LoadMusicStream(pathString(musicPath));
        rotateSound_ = LoadSound(pathString(rotatePath));
        clearSound_ = LoadSound(pathString(clearPath));

        if (music_.stream.buffer == nullptr)
        {
            std::cerr << "Failed to load music: " << musicPath << '\n';
        }
        else
        {
            PlayMusicStream(music_);
        }
    }

    AudioService::~AudioService()
    {
        UnloadSound(rotateSound_);
        UnloadSound(clearSound_);
        UnloadMusicStream(music_);
        CloseAudioDevice();
    }

    void AudioService::updateMusic()
    {
        if (music_.stream.buffer != nullptr)
        {
            UpdateMusicStream(music_);
        }
    }

    void AudioService::playRotate()
    {
        PlaySound(rotateSound_);
    }

    void AudioService::playClear()
    {
        PlaySound(clearSound_);
    }
}
