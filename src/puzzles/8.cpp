#include <numeric>
#include <puzzles.hpp>

void p8::puzzle( std::filesystem::path const & src_data )
{
    auto rows  = utils::read_lines< std::string >( src_data );
    auto len_x = rows.front().size();
    auto len_y = rows.size();
    auto all   = std::accumulate( rows.begin(), rows.end(), std::string{} );

    auto is_visible = [&]( std::size_t x, std::size_t y ) {
        auto current = rows[y * len_x + x];

        auto row = std::ranges::subrange( y * len_x, ( y + 1 ) * len_x );
        auto col = std::views::auto from_l =
            std::ranges::all_of( rows | std::views::take( x - 1 ), [&]( auto c ) { return c[y] < current; } );
        auto from_r = std::ranges::all_of( rows | std::views::drop( x ), [&]( auto c ) { return c[y] < current; } );
        auto from_t = std::ranges::all_of( rows[x] | std::views::drop( x ), [&]( auto c ) { return c[y] < current; } );
        if ( std )
            if ( rows[y - 1][x] < current || rows[y][x - 1] < current || rows[y][x + 1] < current ||
                 rows[y + 1][x] < current )
                return true;
        return false;
    };

    int visible_trees = 0;
    for ( std::size_t y = 1; y < rows.size() - 1; ++y ) {
        for ( std::size_t x = 1; x < rows[0].size() - 1; ++x ) {
            visible_trees += is_visible( x, y );
        }
    }
    utils::answer( "8_1", visible_trees + 2 * ( rows.size() - 1 ) + 2 * ( rows[0].size() - 1 ) );
}
