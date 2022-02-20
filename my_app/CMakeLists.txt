
cmake_minimum_required(VERSION 3.10)


project(raspi_led
        VERSION 1.0
        LANGUAGES CXX)

target_include_directories(my_program ../include)
add_executable(raspi_led main.cpp)