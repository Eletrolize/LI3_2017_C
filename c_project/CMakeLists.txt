
cmake_minimum_required(VERSION 2.8)

PROJECT(program)

find_package(LIBXML2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})
link_directories(${LIBXML2_LIBRARIES})
add_definitions(${LIBXML2_DEFINITIONS})
if(NOT LIBXML2_FOUND)
	message(ERROR "Libxml2 not found!")
endif(NOT LIBXML2_FOUND)

set( CMAKE_C_FLAGS "-Wall -m64 -O3 -g -O0" )

add_executable(${PROJECT_NAME} program.c src/avl.c src/catalogo.c interface.c src/parser.c src/revisao.c src/utils.c src/catartigos.c src/catartigos.c src/catcontribuidores.c src/contribuidor.c src/set.c)

target_link_libraries(${PROJECT_NAME} ${LIBXML2_LIBRARIES})
