#include <puzzles.hpp>

struct spot {
    spot( std::vector< std::string > grid, std::pair< std::size_t, std::size_t > pos,
          std::pair< std::size_t, std::size_t > prev )
    {
        auto max_x            = grid.front().size();
        auto max_y            = grid.size();
        auto [x, y]           = pos;
        auto [x_prev, y_prev] = prev;

        auto current = grid[y][x];
        if ( ( x + 1 != x_prev ) && ( x + 1 < max_x ) && ( current > grid[y][x + 1] - 1 ) )
            avail_dirs.push_back( std::make_pair( x + 1, y ) );
        if ( ( x - 1 != x_prev ) && ( x != 0 ) && ( current > grid[y][x - 1] - 1 ) )
            avail_dirs.push_back( std::make_pair( x - 1, y ) );
        if ( ( y + 1 != y_prev ) && ( y + 1 < max_y ) && ( current > grid[y + 1][x] - 1 ) )
            avail_dirs.push_back( std::make_pair( x, y + 1 ) );
        if ( ( y - 1 != y_prev ) && ( y != 0 ) && ( current > grid[y - 1][x] - 1 ) )
            avail_dirs.push_back( std::make_pair( x, y - 1 ) );
    }

    auto has_alternatives() const -> bool { return !avail_dirs.empty(); }

private:
    std::vector< std::pair< std::size_t, std::size_t > > avail_dirs;

}

auto find_start_end( auto grid )
{
    auto max_x = grid.front().size();
    auto max_y = grid.size();

    std::pair< std::size_t, std::size_t > s, e;

    for ( std::size_t x = 0; x < max_x; ++x ) {
        for ( std::size_t y = 0; y < max_y; ++y ) {
            if ( grid[y][x] == 'S' )
                s = std::make_pair( x, y );
            if ( grid[y][x] == 'E' )
                e = std::make_pair( x, y );
        }
    }
    return std::make_tuple( s, e );
};

void p12::puzzle( std::filesystem::path const & src_data )
{
    auto grid   = utils::read_lines< std::string >( src_data );
    auto [s, e] = find_start_end( grid );

    std::vector< std::size_t > path_lens;
    std::vector< spot >        alternatives;

    utils::answer( "12_1", path.size() );
}