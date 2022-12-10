#include <iostream>

#include <puzzles.hpp>

#include <utils/path.hpp>

auto main() -> int
{
    try {
        // p1::puzzle( utils::get_input_dir() / "1_input.txt" );
        // p2::puzzle( utils::get_input_dir() / "2_input.txt" );
        // p3::puzzle( utils::get_input_dir() / "3_input.txt" );
        // p4::puzzle( utils::get_input_dir() / "4_input.txt" );
        // p5::puzzle( utils::get_input_dir() / "5_input.txt" );
        // p6::puzzle( utils::get_input_dir() / "6_input.txt" );
        // p7::puzzle( utils::get_input_dir() / "7_input.txt" );
        // p8::puzzle( utils::get_input_dir() / "8_input.txt" );
        p9::puzzle( utils::get_input_dir() / "9_input.txt" );
    }
    catch ( std::exception const & e ) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}