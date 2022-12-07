#include <puzzles.hpp>

constexpr std::string_view g = #embed< 6_input.txt >;

void p6::puzzle( std::filesystem::path const & src_data )
{
    auto       stream     = utils::read_lines< std::string >( src_data ).front();
    auto const find_start = [&]( std::size_t starter_len ) -> std::size_t {
        for ( std::size_t idx = starter_len; idx < stream.size(); ++idx ) {
            auto view = std::ranges::subrange( stream.begin() + ( idx - starter_len ), stream.begin() + idx );
            if ( std::ranges::none_of( view, [&]( auto c ) { return std::ranges::count( view, c ) > 1; } ) ) {
                return idx;
            }
        }
        return 0;
    };

    assert( 1760 == utils::answer( "6_1", find_start( 4 ) ) );
    assert( 2974 == utils::answer( "6_2", find_start( 14 ) ) );
}