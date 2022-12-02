#include <iostream>

#include <puzzles/p1/1.hpp>
#include <utils/path.hpp>

auto main() -> int
{
    try {
        p1::puzzle( utils::get_src_dir() / "puzzles" / "p1" / "input.txt" );
    }
    catch ( std::exception const & e ) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}