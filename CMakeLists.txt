cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(tetris)

if (UNIX) 
    set(CMAKE_PREFIX_PATH "/mnt/d/sfml3ub")
else()
    set(CMAKE_PREFIX_PATH "C:/SFML-3.0.0")
endif()

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window)

file(GLOB_RECURSE INCLUDE "include/*.hpp")
file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(main ${SRC} ${INCLUDE})
target_link_libraries(main PRIVATE SFML::Graphics SFML::Window) 

add_executable(tst tests/viewTests.cpp src/view.cpp include/view.hpp)
target_link_libraries(tst PRIVATE SFML::Graphics SFML::Window) 


set(FONT_FILE "${CMAKE_SOURCE_DIR}/calibri.ttf")
add_custom_command(TARGET tst POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${FONT_FILE}" "$<TARGET_FILE_DIR:tst>"
)
target_compile_features(main PRIVATE cxx_std_23)
target_compile_features(tst PRIVATE cxx_std_23)
