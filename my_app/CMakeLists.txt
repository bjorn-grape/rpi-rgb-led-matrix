cmake_minimum_required(VERSION 3.10)


project(raspi_led)

include_directories(../include)
add_library(rpi_rgb_led_matrix SHARED
	../lib/bdf-font.cc 
	../lib/led-matrix-c.cc
	../lib/content-streamer.cc  
	../lib/multiplex-mappers.cc
	../lib/framebuffer.cc       
	../lib/options-initialize.cc
	../lib/gpio.cc              
	../lib/pixel-mapper.cc
	../lib/graphics.cc          
	../lib/thread.cc
	../lib/led-matrix.cc
	../lib/hardware-mapping.c
	)

add_executable(raspi_led main.cpp)

target_link_libraries(raspi_led rpi_rgb_led_matrix pthread rt m)
