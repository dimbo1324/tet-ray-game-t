#include "ResourcePaths.h"

#include <iostream>

namespace tetris
{
    namespace
    {
        bool hasAssets(const std::filesystem::path &path)
        {
            return std::filesystem::exists(path / "fonts") && std::filesystem::exists(path / "sounds");
        }
    }

    ResourcePaths::ResourcePaths(const char *executablePath)
        : assetRoot_(resolveAssetRoot(executablePath))
    {
        if (!hasAssets(assetRoot_))
        {
            std::cerr << "Asset root is incomplete or missing: " << assetRoot_ << '\n';
        }
    }

    const std::filesystem::path &ResourcePaths::assetRoot() const
    {
        return assetRoot_;
    }

    std::filesystem::path ResourcePaths::font(std::string_view relativeName) const
    {
        return assetRoot_ / "fonts" / relativeName;
    }

    std::filesystem::path ResourcePaths::sound(std::string_view relativeName) const
    {
        return assetRoot_ / "sounds" / relativeName;
    }

    std::filesystem::path ResourcePaths::resolveAssetRoot(const char *executablePath)
    {
        const std::filesystem::path executable(executablePath ? executablePath : "");
        const std::filesystem::path executableDir = executable.has_parent_path()
                                                        ? std::filesystem::absolute(executable).parent_path()
                                                        : std::filesystem::current_path();

        const std::filesystem::path candidates[] = {
            executableDir / "assets",
            std::filesystem::current_path() / "assets",
            std::filesystem::current_path() / ".." / ".." / "assets",
        };

        for (const auto &candidate : candidates)
        {
            std::error_code error;
            const auto normalized = std::filesystem::weakly_canonical(candidate, error);
            const auto &path = error ? candidate : normalized;
            if (hasAssets(path))
            {
                return path;
            }
        }

        return candidates[0];
    }
}
