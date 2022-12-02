#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <vector>

namespace utils {

    template < typename T >
    inline auto read_lines( std::filesystem::path const & path ) -> std::vector< std::optional< T > >
    {
        if ( !std::filesystem::exists( path ) )
            throw std::runtime_error( "The given path does not exist" );
        std::ifstream ifs{ path.string() };
        std::string   content( std::filesystem::file_size( path ), '\0' );
        ifs.read( content.data(), std::filesystem::file_size( path ) );

        auto transformer = []( auto const line_split ) -> std::optional< T > {
            auto line = std::string{ line_split.begin(), line_split.end() };
            if ( line.empty() )
                return std::nullopt;
            else {
                if constexpr ( std::is_convertible< T, std::string >() ) {
                    return T{ line };
                }
                else if constexpr ( std::is_integral< T >() ) {
                    return static_cast< T >( std::stoll( line ) );
                }
                else if constexpr ( std::is_floating_point< T >() ) {
                    return static_cast< T >( std::stold( line ) );
                }
                else {
                    throw std::runtime_error( "Error during reading of input. Unimplemented string->type conversion" );
                }
                return std::nullopt;
            }
        };
        auto lines = content | std::views::split( '\n' ) | std::views::transform( transformer );

        std::vector< std::optional< T > > vec;
        std::ranges::copy( lines, std::back_inserter( vec ) );
        return vec;
    }

}  // namespace utils
