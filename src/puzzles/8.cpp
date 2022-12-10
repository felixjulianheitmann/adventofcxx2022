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

    auto get_directions = [&]( std::size_t x, std::size_t y ) {
        auto current = all[y * len_x + x];
        auto row     = all | drop( y * len_x ) | take( len_x );
        auto col     = all | drop( x ) |
                   filter( [i = 0, &len_x]( auto ) mutable { return i++ % len_x == 0; } );  // No stride available
        auto left  = row | take( x );
        auto right = row | drop( x + 1 );
        auto up    = col | take( y );
        auto down  = col | drop( y + 1 );
        return std::make_tuple( current, up, down, left, right );
    };

    auto is_visible = [&]( std::size_t x, std::size_t y ) {
        auto [current, up, down, left, right] = get_directions( x, y );
        auto comp                             = [&]( char const c ) { return c < current; };
        if ( std::ranges::all_of( up, comp ) || std::ranges::all_of( left, comp ) ||
             std::ranges::all_of( down, comp ) || std::ranges::all_of( right, comp ) ) {
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
        auto [current, up, down, left, right] = get_directions( x, y );
        auto score                            = 0;
        auto count_dist                       = [&]( auto dir ) {
            for ( auto tree : dir ) {
                if ( tree < current )
                    score += 1;
                else
                    return;
            }
        };

        count_dist( up );
        count_dist( down );
        count_dist( left );
        count_dist( right );
        return score;
    };

    // part 2
    int top_score = 0;
    for ( std::size_t y = 0; y < rows.size(); ++y ) {
        for ( std::size_t x = 0; x < rows.size(); ++x ) {
            if ( auto score = scenic_score( x, y ); score > top_score )
                top_score = score;
        }
    }

    assert( 1807 == utils::answer( "8_1", visible_trees + 2 * ( len_x ) + 2 * ( len_y - 1 ) ) );
}
