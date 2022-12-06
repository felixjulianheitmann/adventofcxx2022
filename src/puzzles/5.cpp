#include <puzzles.hpp>

#include <numeric>
#include <stack>

void p5::puzzle( std::filesystem::path const & src_data )
{
    auto chunks   = utils::read_lines_as_chunks< std::string >( src_data, "\n\n" );
    auto n_stacks = utils::split_as< int >( std::string_view( chunks[0].back() ), " " ).back();
    std::vector< std::stack< char > > stacks( n_stacks );
    chunks.front().pop_back();
    for ( auto const & line : chunks.front() | std::views::reverse ) {
        std::size_t stack_idx = 0;
        auto        char_idx  = stack_idx * 4 + 1;
        while ( char_idx < line.size() ) {
            if ( line[char_idx] != ' ' ) {
                stacks[stack_idx].push( line[char_idx] );
            }
            stack_idx++;
            char_idx = stack_idx * 4 + 1;
        }
    }

    auto stacks2 = stacks;
    // Part one
    for ( auto const & cmd : chunks.back() ) {
        auto const splits = utils::split_as< std::string >( std::string_view( cmd ), " " );
        auto const count  = std::stol( splits[1] );
        auto const from   = std::stol( splits[3] );
        auto const to     = std::stol( splits[5] );
        for ( auto i = 0; i < count; ++i ) {
            stacks[to - 1].push( stacks[from - 1].top() );
            stacks[from - 1].pop();
        }
    }

    assert( "HNSNMTLHQ" == utils::answer( "5_1", std::accumulate( stacks.begin(), stacks.end(), std::string{},
                                                                  []( auto const & str, auto const & stack ) {
                                                                      return str + stack.top();
                                                                  } ) ) );

    // Part two
    for ( auto const & cmd : chunks.back() ) {
        auto const        splits = utils::split_as< std::string >( std::string_view( cmd ), " " );
        auto const        count  = std::stol( splits[1] );
        auto const        from   = std::stol( splits[3] );
        auto const        to     = std::stol( splits[5] );
        std::stack< int > tmp;
        for ( auto i = 0; i < count; ++i ) {
            tmp.push( stacks2[from - 1].top() );
            stacks2[from - 1].pop();
        }
        while ( !tmp.empty() ) {
            stacks2[to - 1].push( tmp.top() );
            tmp.pop();
        }
    }

    assert( "RNLFDJMCT" == utils::answer( "5_2", std::accumulate( stacks2.begin(), stacks2.end(), std::string{},
                                                                  []( auto const & str, auto const & stack ) {
                                                                      return str + stack.top();
                                                                  } ) ) );
}
