#ifndef TETRIS_ASSETS_RESOURCE_PATHS_H
#define TETRIS_ASSETS_RESOURCE_PATHS_H

#include <filesystem>
#include <string_view>

namespace tetris
{
    class ResourcePaths
    {
    public:
        explicit ResourcePaths(const char *executablePath);

        const std::filesystem::path &assetRoot() const;

        std::filesystem::path font(std::string_view relativeName) const;

        std::filesystem::path sound(std::string_view relativeName) const;

    private:
        static std::filesystem::path resolveAssetRoot(const char *executablePath);

        std::filesystem::path assetRoot_;
    };
}

#endif
