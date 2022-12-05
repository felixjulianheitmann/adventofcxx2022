#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <regex>
#include <vector>

namespace utils {

    template < typename T >
    concept Number = std::is_integral_v< T > || std::is_floating_point_v< T >;

    template < typename T >
    concept Number_or_String =
        std::is_integral_v< std::remove_cvref_t< T > > || std::is_floating_point_v< std::remove_cvref_t< T > > ||
        std::is_convertible_v< std::remove_cvref_t< T >, std::string > ||
        std::is_same_v< std::remove_cvref_t< T >, std::string >;

    namespace detail {
        inline auto file_to_str( std::filesystem::path const & path )
        {
            if ( !std::filesystem::exists( path ) )
                throw std::runtime_error( "The given path does not exist" );
            std::ifstream ifs{ path.string() };
            std::string   content( std::filesystem::file_size( path ), '\0' );
            ifs.read( content.data(), std::filesystem::file_size( path ) );
            return content;
        }
    }  // namespace detail

    template < Number_or_String T > inline auto transform( std::string_view const str ) -> T
    {
        if constexpr ( std::is_same< T, char >() ) {
            return str.front();
        }
        else if constexpr ( std::is_convertible< T, std::string >() ) {
            return T{ str };
        }
        else if constexpr ( std::is_integral< T >() ) {
            return static_cast< T >( std::stoll( std::string( str ) ) );
        }
        else if constexpr ( std::is_floating_point< T >() ) {
            return static_cast< T >( std::stold( std::string( str ) ) );
        }
        else {
            throw std::runtime_error( "Error during reading of input. Unimplemented string->type conversion" );
        }
    }

    template < Number_or_String T > inline auto split_as( std::string_view const line, std::regex const & regex )
    {
        auto sline = std::string( line );
        auto matches =
            std::ranges::subrange( std::sregex_iterator( sline.begin(), sline.end(), regex ), std::sregex_iterator() ) |
            std::views::transform( []( auto const match ) {
                return transform< T >( match.str()
            ); } );
        return std::vector< T >( matches.begin(), matches.end() );
    }

    template < Number_or_String T >
    inline auto split_as( std::ranges::forward_range auto const & lines, std::regex const & regex )
        -> std::vector< std::vector< T > >
    {
        std::vector< std::vector< T > > splits;
        for ( auto const & line : lines )
            splits.push_back( split_as< T >( std::string_view{ line }, regex ) );
        return splits;
    }

    template < Number_or_String T >
    inline auto split_as( std::string_view const line, std::string_view const token ) -> std::vector< T >
    {

        auto splits = line | std::views::split( token ) |
                      std::views::filter( []( auto const & split ) { return !split.empty(); } ) |
                      std::views::transform( []( auto const & s ) {
                          return transform< T >( { s.begin(), s.end() } );
                      } );
        return std::vector< T >( splits.begin(), splits.end() );
    }

    template < Number_or_String T >
    inline auto split_as( std::ranges::forward_range auto const & lines, std::string_view const token )
        -> std::vector< std::vector< T > >
    {
        std::vector< std::vector< T > > splits;
        for ( auto const & line : lines ) {
            splits.push_back( split_as< T >( std::string_view{ line }, token ) );
        }
        return splits;
    }

    template < Number_or_String T > inline auto read_lines( std::filesystem::path const & path ) -> std::vector< T >
    {
        return split_as< T >( std::string_view( detail::file_to_str( path ) ), "\n" );
    }

    template < Number_or_String T >
    inline auto read_lines_as_chunks( std::filesystem::path const & path, std::string_view const split_token )
        -> std::vector< std::vector< T > >
    {
        auto chunks = split_as< std::string >( std::string_view( detail::file_to_str( path ) ), split_token );

        std::vector< std::vector< T > > tmp;
        for ( auto const & chunk : chunks ) {
            tmp.push_back( split_as< T >( std::string_view( chunk ), "\n" ) );
        }
        return tmp;
    }

    template < Number_or_String T >
    inline auto read_lines_as_chunks( std::filesystem::path const & path, std::size_t n_lines )
        -> std::vector< std::vector< T > >
    {
        auto lines = read_lines< T >( path );

        std::vector< std::vector< T > > tmp;
        std::size_t                     rotating_idx = 0;
        for ( auto && line : lines ) {
            if ( rotating_idx++ % n_lines == 0 )
                tmp.push_back( {} );
            tmp.back().push_back( line );
        }
        return tmp;
    }

}  // namespace utils
