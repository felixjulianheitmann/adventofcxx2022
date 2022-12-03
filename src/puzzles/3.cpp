#include <puzzles.hpp>

#include <ranges>

auto item_priority( char item ) -> int
{
    if ( item < 'a' )
        return item - 'A' + 27;
    else
        return item - 'a' + 1;
}

void p3::puzzle( std::filesystem::path const & src_data )
{
    auto rucksacks = utils::read_lines< std::string >( src_data );
    auto score     = 0;
    for ( auto & rucksack : rucksacks ) {
        auto split = rucksack.size() / 2;
        auto left  = rucksack | std::views::take( split );
        auto right = rucksack | std::views::drop( split );
        std::sort( left.begin(), left.end() );
        std::sort( right.begin(), right.end() );
        std::string common;
        std::set_intersection( left.begin(), left.end(), right.begin(), right.end(), std::back_inserter( common ) );
        score += item_priority( common.front() );
    }

    assert( ( 7821 == utils::answer( "3_1", score ) ) );

    auto groups = utils::read_lines_as_chunks< std::string >( src_data, 3 );
    score       = 0;
    for ( auto & group : groups ) {
        std::string common12;
        std::string common123;
        for ( auto & elf : group )
            std::sort( elf.begin(), elf.end() );
        std::set_intersection( group[0].begin(), group[0].end(), group[1].begin(), group[1].end(),
                               std::back_inserter( common12 ) );
        std::set_intersection( common12.begin(), common12.end(), group[2].begin(), group[2].end(),
                               std::back_inserter( common123 ) );
        score += item_priority( common123.front() );
    }

    assert( ( 2752 == utils::answer( "3_2", score ) ) );
}
