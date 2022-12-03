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

    utils::answer( "3_1", score );
}
