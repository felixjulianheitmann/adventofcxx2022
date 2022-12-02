#include <puzzles/p1/1.hpp>

namespace p1 {

    void puzzle( std::filesystem::path const & src_data )
    {
        using cal  = std::size_t;
        auto input = utils::read_lines< cal >( src_data );

        std::vector< cal > elves;
        cal                calories = 0;

        for ( auto const c : input ) {
            if ( c )
                calories += c.value();
            else {
                elves.push_back( calories );
                calories = 0;
            }
        }

        std::sort( elves.begin(), elves.end() );

        utils::answer( "1_1", elves.back() );
        utils::answer( "1_2", std::accumulate( elves.end() - 3, elves.end(), 0 ) );
    }

}  // namespace p1
