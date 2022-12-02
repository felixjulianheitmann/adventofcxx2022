#pragma once

#include <filesystem>

#ifndef AOC_SRC_DIR_PATH
#define AOC_SRC_DIR_PATH "."
#endif

namespace utils {
    inline auto get_src_dir() -> std::filesystem::path { return AOC_SRC_DIR_PATH; }
    inline auto get_solutions_dir() -> std::filesystem::path
    {
        return std::filesystem::path( AOC_SRC_DIR_PATH ) / "solutions";
    }
}  // namespace utils
