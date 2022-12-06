#include <puzzles.hpp>

void p4::puzzle( std::filesystem::path const & src_data )
{
    auto lines   = utils::read_lines< std::string >( src_data );
    auto matches = 0;

    auto seq_from_line = []( auto const & line ) {
        auto areas      = utils::split_as< std::string >( std::string_view( line ), "," );
        auto start_end0 = utils::split_as< int >( std::string_view( areas[0] ), "-" );
        auto start_end1 = utils::split_as< int >( std::string_view( areas[1] ), "-" );
        return std::make_tuple( std::views::iota( start_end0.front(), start_end0.back() + 1 ),
                                std::views::iota( start_end1.front(), start_end1.back() + 1 ) );
    };

    for ( auto const & line : lines ) {
        auto [seq0, seq1] = seq_from_line( line );
        if ( std::search( seq0.begin(), seq0.end(), seq1.begin(), seq1.end() ) != seq0.end() ||
             std::search( seq1.begin(), seq1.end(), seq0.begin(), seq0.end() ) != seq1.end() )
            ++matches;
    }
    assert( 605 == utils::answer( "4_1", matches ) );

    matches = 0;
    for ( auto const & line : lines ) {
        auto [seq0, seq1] = seq_from_line( line );
        if ( std::ranges::find_first_of( seq0, std::array< int, 2 >{ seq1.front(), seq1.back() } ) != seq0.end() ||
             std::ranges::find_first_of( seq1, std::array< int, 2 >{ seq0.front(), seq0.back() } ) != seq1.end() )
            ++matches;
    }

    assert( 914 == utils::answer( "4_2", matches ) );
}
