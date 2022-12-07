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

    auto size() -> std::size_t
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

    auto access_path = []( node & root, std::ranges::forward_range auto const & path ) {
        auto n = &root;
        for ( auto const & p : path ) {
            n = &std::get_if< directory >( &n )->subnodes[p];
        }
        return *n;
    };

    std::vector< std::string > path;

    directory root{
        .name     = "/",
        .subnodes = {},
        .parent   = nullptr,
    };
    directory * current_dir = &root;
    for ( auto const & line : lines ) {
        if ( line.starts_with( "$ cd" ) ) {
            auto sub_path = line.substr( 5 );
            if ( sub_path == ".." ) {
                path.pop_back();
                current_dir = current_dir->parent;
            }
            else {
                current_dir->subnodes[sub_path] = directory{
                    .name     = sub_path,
                    .subnodes = {},
                    .parent   = current_dir,
                };
                path.push_back( sub_path );
                current_dir = &current_dir->subnodes[sub_path];
            }
        }
        else if ( line.starts_with( "$ ls" ) ) {
            continue;
        }
        else {
            auto split                          = utils::split_as< std::string >( std::string_view( line ), " " );
            current_dir->subnodes[split.back()] = file { .name = split.back(), .size = std::stol( split.front() ); };
        }
    }

    utils::answer( "7_1", 0 );
}