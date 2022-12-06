#include <puzzles.hpp>

#include <numeric>

void p1::puzzle( std::filesystem::path const & src_data )
{
    using cal  = std::size_t;
    auto input = utils::read_lines_as_chunks< cal >( src_data, "\n\n" );

    std::vector< cal > elves;
    for ( auto const & elve_chunk : input ) {
        elves.push_back( std::accumulate( elve_chunk.begin(), elve_chunk.end(), 0 ) );
    }

    std::sort( elves.begin(), elves.end() );

    assert( 69281 == utils::answer( "1_1", elves.back() ) );
    assert( 201524 == utils::answer( "1_2", std::accumulate( elves.end() - 3, elves.end(), 0 ) ) );
}
