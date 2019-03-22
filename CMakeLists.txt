cmake_minimum_required(VERSION 3.13)

project(impac VERSION 0.0)

set(CMAKE_CXX_STANDARD 17)

find_package(ImageMagick REQUIRED COMPONENTS Magick++)

set(IMPAC_SOURCE_FILES
    src/impac.cpp
    src/sprite.cpp
    src/sprite_sheet.cpp
    src/pack/first_fit.cpp
    )

add_executable(impac ${IMPAC_SOURCE_FILES})
target_compile_definitions(impac PRIVATE
    MAGICKCORE_HDRI_ENABLE=0
    MAGICKCORE_QUANTUM_DEPTH=16
    )
target_include_directories(impac PRIVATE ${ImageMagick_INCLUDE_DIRS})
target_link_libraries(impac ${ImageMagick_LIBRARIES})
