cmake_minimum_required(VERSION 3.0)

project(chatonly)

file(GLOB SOURCES
	src/*.cpp
	src/*.c
)

add_executable(chatonly ${SOURCES})
target_include_directories(chatonly PRIVATE ${PROJECT_SOURCE_DIR}/include)

if (WIN32)
	target_link_libraries(chatonly ws2_32)
	target_link_options(chatonly PRIVATE -static)
endif()
