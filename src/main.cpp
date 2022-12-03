#include <iostream>

#include <puzzles/1.hpp>
#include <puzzles/2.hpp>
#include <utils/path.hpp>

auto main() -> int
{
    try {
        p1::puzzle( utils::get_src_dir() / "puzzles" / "1_input.txt" );
        p2::puzzle( utils::get_src_dir() / "puzzles" / "2_input.txt" );
    }
    catch ( std::exception const & e ) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}