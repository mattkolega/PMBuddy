#include "fs.h"

#include <cerrno>
#include <filesystem>
#include <fstream>
#include <optional>
#include <system_error>
#include <vector>

#include "log.h"
#include "types.h"

std::optional<std::vector<u8>> fs::loadFileIntoBuffer(const std::filesystem::path& filepath) {
    errno = 0; // Clear errno so we don't use stale value

    std::ifstream file {filepath, std::ios::binary};
    if (!file) {
        int err = errno;
        log::err("Failed to open file: `{}` Error: {}", filepath, std::system_category().message(err));
        return std::nullopt;
    }

    file.seekg(0, std::ios::end);
    if (!file) {
        log::err("Failed to seek to end of file: `{}`", filepath);
        return std::nullopt;
    }

    auto fileSize = file.tellg();
    if (!file || fileSize < 0) {
        log::err("Failed to obtain file size: `{}`", filepath);
        return std::nullopt;
    }

    file.seekg(0, std::ios::beg);
    if (!file) {
        log::err("Failed to seek to start of file: `{}`", filepath);
        return std::nullopt;
    }

    std::vector<u8> buffer(fileSize);

    // Copy file data to buffer
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    if (!file) {
        log::err("Failed to read file: `{}`", filepath);
        return std::nullopt;
    }

    return buffer;
}
