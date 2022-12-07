#include <puzzles.hpp>
#include <variant>

class file;
class directory;
using node = std::variant< file, directory >;

class file {
    std::string name;
    std::size_t size;
    auto        size() const -> std::size_t { return size; }
};

class directory {
    std::string         name;
    std::vector< node > subnodes;
    auto                size() -> std::size_t
    {
        std::size_t size = 0;
        for ( auto const & n : subnodes ) {
            size += std::apply( [&]( auto && n_ ) { return n_.size(); }, n );
        }
        return size;
    }

    void iter_rec_subdirs( auto & f ) const
    {
        for ( auto const & n : subnodes ) {
            if ( auto const dir = std::get_if< directory >( &n ) ) {
                f( &dir );
                dir->iter_rec_subdirs( f );
            }
        }
    }
};

void p7::puzzle( std::filesystem::path const & src_data )
{
    auto lines = utils::read_lines< std::string >( src_data );

    for ( auto const & line : lines ) {
    }

    utils::answer( "7_1", 0 );
}