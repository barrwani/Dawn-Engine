cmake_minimum_required(VERSION 3.27)
project(dawn-engine)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
set(SDL2_PATH "C:/Users/asood/SDL2-2.30.3/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})


add_executable(dawn-engine src/main.cpp
        src/Nodes/Node2D.cpp
        include/Nodes/Node2D.h
        src/Nodes/Node.cpp
        include/Nodes/Node.h
        src/root.cpp
        include/root.h
        src/Collision.cpp
        include/Collision.h
        src/Nodes/CollisionObject2D.cpp
        include/Nodes/CollisionObject2D.h
        src/Vector2.cpp
        include/Vector2.h
        src/Nodes/Sprite2D.cpp
        include/Nodes/Sprite2D.h
        src/Nodes/Area2D.cpp
        include/Nodes/Area2D.h
        src/Nodes/StaticBody2D.cpp
        include/Nodes/StaticBody2D.h
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})