cmake_minimum_required(VERSION "3.22.1")

project(Mandelbrot VERSION 1.0)

include_directories(include)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

add_executable(Mandelbrot
               "source/main.cpp"
               "source/Frame.cpp")

target_link_libraries(Mandelbrot sfml-graphics sfml-audio)
