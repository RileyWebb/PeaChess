cmake_minimum_required(VERSION 3.21)

project(peachess C)

set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)

include_directories(include)

add_subdirectory(ext)

if (WIN32)
    set(PLATFORM_LIBS mingw32)
endif()

file(GLOB GENERAL_SOURCES src/*.c)
file(GLOB CHESS_SOURCES src/chess/*.c)
file(GLOB UI_SOURCES src/ui/*.c)
file(GLOB SERVER_SOURCES src/server/*.c)

file(GLOB_RECURSE CLIENT_SOURCES src/client/*.c)

add_executable(client ${GENERAL_SOURCES} ${CHESS_SOURCES} ${SERVER_SOURCES} ${CLIENT_SOURCES})

target_link_libraries(client PRIVATE ${PLATFORM_LIBS} uv SDL2main libglew_static stb cimgui cimplot)
target_link_libraries(client PUBLIC SDL2)

target_compile_options(client PRIVATE
        $<$<CONFIG:Debug>:
        #-pedantic
        #-Wall
        -Wextra
        -Wconversion
        -Wundef
        #-Werror
        -Wno-unused-parameter
        -Wno-unused-variable
        -Wno-unused-but-set-variable
        >
        )

add_custom_target(copy_info
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/LICENCE
        ${CMAKE_CURRENT_SOURCE_DIR}/CREDITS
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_custom_target(copy_data
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/data/
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/data/)

add_dependencies(client copy_data copy_info)
