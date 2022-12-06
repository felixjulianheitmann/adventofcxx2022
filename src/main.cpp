#include <iostream>

#include <puzzles.hpp>

#include <utils/path.hpp>

auto main() -> int
{
    try {
        p1::puzzle( utils::get_src_dir() / "puzzles" / "1_input.txt" );
        p2::puzzle( utils::get_src_dir() / "puzzles" / "2_input.txt" );
        p3::puzzle( utils::get_src_dir() / "puzzles" / "3_input.txt" );
        p4::puzzle( utils::get_src_dir() / "puzzles" / "4_input.txt" );
        p5::puzzle( utils::get_src_dir() / "puzzles" / "5_input.txt" );
        p6::puzzle( utils::get_src_dir() / "puzzles" / "6_input.txt" );
    }
    catch ( std::exception const & e ) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}