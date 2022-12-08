#pragma once

#include <filesystem>

#ifndef AOC_ROOT_DIR_PATH
#define AOC_ROOT_DIR_PATH "."
#endif

namespace utils {
    inline auto get_src_dir() -> std::filesystem::path { return std::filesystem::path( AOC_ROOT_DIR_PATH ) / "src"; }
    inline auto get_solutions_dir() -> std::filesystem::path
    {
        return std::filesystem::path( AOC_ROOT_DIR_PATH ) / "solutions";
    }
    inline auto get_input_dir() -> std::filesystem::path
    {
        return std::filesystem::path( AOC_ROOT_DIR_PATH ) / "inputs";
    }
}  // namespace utils
