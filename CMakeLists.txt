<<<<<<< HEAD
cmake_minimum_required(VERSION 2.8)
cmake_minimum_required(VERSION 3.13)

project(impac VERSION 0.0)

set(CMAKE_CXX_STANDARD 17)

find_package(ImageMagick REQUIRED COMPONENTS Magick++)

add_executable(impac src/impac.cpp)
target_compile_definitions(impac PRIVATE
    MAGICKCORE_HDRI_ENABLE=0
    MAGICKCORE_QUANTUM_DEPTH=16
    )
target_include_directories(impac PRIVATE ${ImageMagick_INCLUDE_DIRS})
target_link_libraries(impac ${ImageMagick_LIBRARIES})
