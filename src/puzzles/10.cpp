#include <puzzles.hpp>

void p10::puzzle( std::filesystem::path const & src_data )
{
    auto cmds = utils::read_lines< std::string >( src_data );

    auto X               = 1;
    auto signal_strength = 0;
    int  cycle           = 1;

    std::string pixels;

    auto tick = [&] {
        // part 1
        if ( cycle % 40 == 20 ) {
            signal_strength += cycle * X;
        }

        // part 2
        auto pos = cycle % 40;
        if ( pos == X || pos == X + 1 || pos == X + 2 )
            pixels.push_back( '#' );
        else
            pixels.push_back( '.' );
        if ( cycle % 40 == 0 )
            pixels.push_back( '\n' );

        ++cycle;
    };

    for ( size_t i = 0; i < cmds.size(); i++ ) {
        auto const & cmd = cmds[i];
        if ( cmd == "noop" )
            tick();
        else if ( cmd.starts_with( "addx" ) ) {
            tick();
            tick();
            X += std::stol( cmd.substr( 5 ) );
        }
    }

    assert( 16880 == utils::answer( "10_1", signal_strength ) );
    utils::answer( "10_2", pixels );
}