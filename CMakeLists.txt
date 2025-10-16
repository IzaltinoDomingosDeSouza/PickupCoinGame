cmake_minimum_required(VERSION 3.28)
project(PickupCoinGame3D CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)

set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad)
set(GLAD_SRC ${GLAD_DIR}/src/glad.c)

add_library(engine_lib)

target_sources(engine_lib PUBLIC 
    FILE_SET CXX_MODULES FILES
    engine/window_context.cxx
)

target_sources(engine_lib PRIVATE ${GLAD_SRC})
target_include_directories(engine_lib PUBLIC ${GLAD_DIR}/include)

add_executable(${PROJECT_NAME} game/game.cxx)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    engine_lib
    glad
    glfw
    OpenGL
)
