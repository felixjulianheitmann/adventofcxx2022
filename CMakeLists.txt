cmake_minimum_required(VERSION 3.20)

project(adventofc++)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/puzzles/1.cpp
    src/puzzles/2.cpp
    src/puzzles/3.cpp
    src/puzzles/4.cpp
    src/puzzles/5.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_compile_definitions(${PROJECT_NAME} PUBLIC AOC_ROOT_DIR_PATH="${PROJECT_SOURCE_DIR}")
