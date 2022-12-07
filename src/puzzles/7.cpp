#include <puzzles.hpp>
#include <unordered_map>
#include <variant>

class file;
class directory;
using node = std::variant< file, directory >;

struct file {
    std::string name;
    std::size_t size;
};

struct directory {
    std::string                             name;
    std::unordered_map< std::string, node > subnodes;
    directory *                             parent;

    auto size() const -> std::size_t
    {
        std::size_t size = 0;
        for ( auto const & [name, n] : subnodes ) {
            if ( file const * f = std::get_if< file >( &n ) )
                size += f->size;
            else if ( directory const * dir = std::get_if< directory >( &n ) )
                size += dir->size();
        }
        return size;
    }

    void iter_rec_subdirs( auto const f ) const
    {
        for ( auto const & [name, n] : subnodes ) {
            if ( auto const dir = std::get_if< directory >( &n ) ) {
                f( *dir );
                dir->iter_rec_subdirs( f );
            }
        }
    }
};

void p7::puzzle( std::filesystem::path const & src_data )
{
    auto lines = utils::read_lines< std::string >( src_data );

    directory root{
        .name     = "/",
        .subnodes = {},
        .parent   = nullptr,
    };
    directory * current_dir = &root;
    for ( auto const & line : lines | std::views::drop( 1 ) ) {
        if ( line.starts_with( "$ cd" ) ) {
            auto sub_path = line.substr( 5 );
            if ( sub_path == ".." ) {
                current_dir = current_dir->parent;
            }
            else {
                current_dir = std::get_if< directory >( &current_dir->subnodes[sub_path] );
            }
        }
        else if ( line.starts_with( "$ ls" ) ) {
            continue;
        }
        else {
            if ( line.starts_with( "dir " ) ) {
                auto sub_path = line.substr( 4 );

                current_dir->subnodes[sub_path] = directory{
                    .name     = sub_path,
                    .subnodes = {},
                    .parent   = current_dir,
                };
            }
            else {
                auto split                          = utils::split_as< std::string >( std::string_view( line ), " " );
                current_dir->subnodes[split.back()] = file{ .name = split.back(), .size = std::stoul( split.front() ) };
            }
        }
    }

    // part 1
    std::size_t counter = 0;
    root.iter_rec_subdirs( [&]( directory const & dir ) {
        if ( auto size = dir.size(); size < 100000 ) {
            counter += size;
        }
    } );

    assert( 1555642 == utils::answer( "7_1", counter ) );
}