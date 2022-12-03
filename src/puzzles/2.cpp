#include <puzzles.hpp>

#include <cassert>

enum class rps {
    Undefined = -99,
    Rock      = 1,
    Paper     = 2,
    Scissors  = 3,
};

enum class game {
    Undefined = -99,
    Lose      = 0,
    Draw      = 3,
    Win       = 6,
};

auto get_rps( char in ) -> rps
{
    switch ( in ) {
    case 'A':
        return rps::Rock;
    case 'B':
        return rps::Paper;
    case 'C':
        return rps::Scissors;
    case 'X':
        return rps::Rock;
    case 'Y':
        return rps::Paper;
    case 'Z':
        return rps::Scissors;
    default:
        return rps::Undefined;
    }
}

auto get_hand_score( rps in ) -> int { return static_cast< int >( in ); }

auto get_result_score( game result ) -> int { return static_cast< int >( result ); }
auto get_result( rps me, rps other ) -> game
{
    using type = std::underlying_type_t< rps >;
    auto diff  = static_cast< type >( other ) - static_cast< type >( me );

    switch ( diff ) {
    // lose
    case 1:
    case -2:
        return game::Lose;
    // draw
    case 0:
        return game::Draw;
    // win
    case -1:
    case 2:
        return game::Win;
    default:
        return game::Undefined;
    }
}

// for part 2
auto get_game_end( char in ) -> game
{
    switch ( in ) {
    case 'X':
        return game::Lose;
    case 'Y':
        return game::Draw;
    case 'Z':
        return game::Win;
    default:
        return game::Undefined;
    }
}

auto get_target_hand( rps other, game targetted_end ) -> rps
{
    using type = std::underlying_type_t< rps >;
    switch ( targetted_end ) {
    case game::Draw:
        return other;
    case game::Lose: {
        auto my = static_cast< type >( other ) - 1;
        return my > 0 ? static_cast< rps >( my ) : static_cast< rps >( my + 3 );
    }
    case game::Win: {
        auto my = static_cast< type >( other ) + 1;
        return my < 4 ? static_cast< rps >( my ) : static_cast< rps >( my - 3 );
    }
    default:
        return rps::Undefined;
    }
}

void p2::puzzle( std::filesystem::path const & src_data )
{
    auto setups = utils::split_as< char >( utils::read_lines< std::string >( src_data ), " " );

    int score = 0;
    for ( auto const & game : setups ) {
        auto me     = get_rps( game.back() );
        auto other  = get_rps( game.front() );
        auto result = get_result( me, other );
        score += get_hand_score( me ) + get_result_score( result );
    }

    assert( ( 17189 == utils::answer( "2_1", score ) ) );

    // part 2
    score = 0;
    for ( auto const & setup : setups ) {
        auto result = get_game_end( setup.back() );
        auto other  = get_rps( setup.front() );
        auto me     = get_target_hand( other, result );
        score += get_hand_score( me ) + get_result_score( result );
    }
    utils::answer( "2_2", score );
}
