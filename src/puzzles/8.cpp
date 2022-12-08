#include <numeric>
#include <puzzles.hpp>

#include <iostream>

using namespace std::views;

void p8::puzzle( std::filesystem::path const & src_data )
{
    auto rows  = utils::read_lines< std::string >( src_data );
    auto len_x = rows.front().size();
    auto len_y = rows.size();
    auto all   = std::accumulate( rows.begin(), rows.end(), std::string{} );

    auto get_iterators = [&]( std::size_t x, std::size_t y ) {
        auto current = all[y * len_x + x];
        auto row     = all | drop( y * len_x ) | take( len_x );
        auto col     = all | drop( x ) |
                   filter( [i = 0, &len_x]( auto ) mutable { return i++ % len_x == 0; } );  // No stride available
        return std::make_tuple( current, row, col );
    };

    auto is_visible = [&]( std::size_t x, std::size_t y ) {
        auto [current, row, col] = get_iterators( x, y );
        auto comp                = [&]( char const c ) { return c < current; };
        if ( std::ranges::all_of( row | take( x ), comp ) || std::ranges::all_of( row | drop( x + 1 ), comp ) ||
             std::ranges::all_of( col | take( y ), comp ) || std::ranges::all_of( col | drop( y + 1 ), comp ) ) {
            return true;
        }
        return false;
    };

    // part 1
    int visible_trees = 0;
    for ( std::size_t y = 1; y < rows.size() - 1; ++y ) {
        for ( std::size_t x = 1; x < rows[0].size() - 1; ++x ) {
            visible_trees += is_visible( x, y );
        }
    }

    auto scenic_score = [&]( std::size_t x, std::size_t y ) {
        auto [current, row, col] = get_iterators( x, y );
    };

    // part 2
    int top_score = 0;
    for ( std::size_t y = 0; y < rows.size(); ++y ) {
        for ( std::size_t x = 0; x < rows.size(); ++x ) {
            if ( auto score = scenic_score( x, y ); score > top_score )
                top_score = score;
        }
    }

    assert( 1807 0 = utils::answer( "8_1", visible_trees + 2 * ( rows.size() - 1 ) + 2 * ( rows[0].size() - 1 ) ) );
}
