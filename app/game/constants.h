#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace tetris
    {
        constexpr int kCellSize = 30;
        constexpr int kNumCols = 10;
        constexpr int kNumRows = 20;

        constexpr int kExtraPixels = 11;
        constexpr int kWindowWidth = 500;
        constexpr int kWindowHeight = 620;

        constexpr int kTargetFPS = 60;
        constexpr double kGameSpeedSeconds = 0.3;

        constexpr int kXUiTextPosition = kCellSize * 350 / kCellSize;
        constexpr int kYUiTextPosition = kCellSize * 15 / kCellSize;
        constexpr int kFontSizeUiText = kCellSize / 1.5;

        constexpr const char *kMusicFile = "sounds/music.mp3";
        constexpr const char *kRotateSoundFile = "sounds/rotate.mp3";
        constexpr const char *kClearSoundFile = "sounds/clear.mp3";
        constexpr const char *kFontFile =
                "fonts/Press_Start_2P/PressStart2P-Regular.ttf";
    }

#endif
