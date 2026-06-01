#ifndef TETRIS_AUDIO_AUDIO_SERVICE_H
#define TETRIS_AUDIO_AUDIO_SERVICE_H

#include "assets/ResourcePaths.h"

#include <raylib.h>

namespace tetris
{
    class AudioService
    {
    public:
        explicit AudioService(const ResourcePaths &resourcePaths);

        ~AudioService();

        AudioService(const AudioService &) = delete;
        AudioService &operator=(const AudioService &) = delete;

        void updateMusic();

        void playRotate();

        void playClear();

    private:
        Music music_{};
        Sound rotateSound_{};
        Sound clearSound_{};
    };
}

#endif
