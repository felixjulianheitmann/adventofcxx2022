#pragma once

#include <filesystem>
#include <fstream>
#include <type_traits>

#include <utils/path.hpp>

namespace utils {

    template < typename T > inline T const & answer( std::filesystem::path const & p, T const & answer )
    {
        if ( !std::filesystem::exists( utils::get_solutions_dir() ) )
            std::filesystem::create_directories( utils::get_solutions_dir() );

        using naked_T = std::remove_cvref_t< T >;

        std::ofstream ofs( utils::get_solutions_dir() / p );
        if constexpr ( std::is_same< naked_T, std::string >() ) {
            ofs << answer;
        }
        else if constexpr ( std::is_convertible< naked_T, std::string_view >() ) {
            ofs << std::string_view{ answer };
        }
        else if constexpr ( std::is_integral< naked_T >() || std::is_integral< naked_T >() ) {
            ofs << std::to_string( answer );
        }
        else {
            throw std::runtime_error( "Could not convert type to string for answer output." );
        }

        return answer;
    }

}  // namespace utils
