cmake_minimum_required(VERSION 3.15)

project(game VERSION 1.0)

file(GLOB_RECURSE SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(glm REQUIRED)

if(UNIX)
	add_executable(game ${SRC_DIR})

	target_link_libraries(game SDL2::SDL2 GL GLEW Freetype::Freetype glm::glm)
	target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()
