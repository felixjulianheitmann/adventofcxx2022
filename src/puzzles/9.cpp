#include <iostream>
#include <puzzles.hpp>
#include <set>
#include <utility>

using pos = std::pair< int, int >;

void p9::puzzle( std::filesystem::path const & src_data )
{
    auto moves = utils::split_as< char >( utils::read_lines< std::string >( src_data ), " " );

    std::set< pos > locations;
    pos             head, tail;
    locations.insert( tail );
    for ( auto const & move : moves ) {
        auto dist = move.back() - '0';
        switch ( move.front() ) {
        case 'R':
            head.first += dist;
            break;
        case 'L':
            head.first -= dist;
            break;
        case 'U':
            head.second += dist;
            break;
        case 'D':
            head.second -= dist;
            break;
        }

        while ( std::abs( head.first - tail.first ) > 1 || std::abs( head.second - tail.second ) > 1 ) {
            if ( head.first > tail.first )
                ++tail.first;
            else if ( head.first < tail.first )
                --tail.first;
            if ( head.second > tail.second )
                ++tail.second;
            else if ( head.second < tail.second )
                --tail.second;
            locations.insert( tail );
        }
    }

    utils::answer( "9_1", locations.size() );
}