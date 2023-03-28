cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(Example)

if(WIN32 OR MSVC OR MSYS OR MINGW)
	set(IS_WINDOWS TRUE)
elseif(UNIX AND NOT APPLE)
	set(IS_LINUX TRUE)
endif()


file(GLOB_RECURSE srcs RELATIVE ${CMAKE_CURRENT_BINARY_DIR} *.c *.cpp *.h *.hpp *.cc)
string(REGEX REPLACE "CMakeFiles/[^;]+;?" "" srcs "${srcs}")

if(IS_LINUX)
	string(REGEX REPLACE "(\\.\\.\\/|\\/)[a-zA-Z0-9_\\.\\/]+_windows\\.[a-zA-Z0-9_]+(;|\\n|$)" "" srcs "${srcs}")
elseif(IS_WINDOWS)
	string(REGEX REPLACE "(\\.\\.\\/|\\/)[a-zA-Z0-9_\\.\\/]+_linux\\.[a-zA-Z0-9_]+(;|\\n|$)" "" srcs "${srcs}")
endif()

add_executable(Example ${srcs})




