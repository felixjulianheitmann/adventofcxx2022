#pragma once

// common headers for every puzzle
#include <cassert>
#include <filesystem>
#include <utils/put_output.hpp>
#include <utils/read_input.hpp>

namespace p1 {
    void puzzle( std::filesystem::path const & src_data );
}  // namespace p1

namespace p2 {
    void puzzle( std::filesystem::path const & src_data );
}  // namespace p2

namespace p3 {
    void puzzle( std::filesystem::path const & src_data );
}  // namespace p3

namespace p4 {
    void puzzle( std::filesystem::path const & src_data );
}  // namespace p4
