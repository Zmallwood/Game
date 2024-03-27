cmake_minimum_required (VERSION 3.5)
project (Game)
set (CMAKE_CXX_STANDARD 20)
find_package(TGUI 1 REQUIRED)
set(TGUI_STATIC_LIBRARIES TRUE)

IF (WIN32)
    set(CMAKE_CXX_FLAGS "-static-libstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,-Bdynamic,--no-whole-archive")
ENDIF()

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SRC_FILES_MATTER ${PROJECT_SOURCE_DIR}/../../matter/*.cpp)
file(GLOB_RECURSE SRC_FILES_DYNAMIC_DATA ${PROJECT_SOURCE_DIR}/../../dynamic_data/*.cpp)
file(GLOB_RECURSE SRC_FILES_WORLD_STRUCTURE ${PROJECT_SOURCE_DIR}/../../world_structure/*.cpp)
file(GLOB_RECURSE SRC_FILES_WORLD_GENERATION ${PROJECT_SOURCE_DIR}/../../world_generation/*.cpp)
add_executable(Game ${SRC_FILES} ${SRC_FILES_MATTER} ${SRC_FILES_DYNAMIC_DATA} ${SRC_FILES_WORLD_STRUCTURE} ${SRC_FILES_WORLD_GENERATION})

IF (WIN32)
    target_link_libraries(Game tgui sfml-graphics opengl32 glu32 glew32)
ELSE()
    target_link_libraries(Game tgui sfml-graphics GL GLU GLEW)
ENDIF()

target_include_directories(Game PUBLIC "src")
set(PCH_FILES
    "stdafx/stdafx.h"
)
target_precompile_headers(Game PRIVATE ${PCH_FILES})
