cmake_minimum_required(VERSION 3.25)
project (dawn-engine)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR C://libs/sdl2/include)
set(SDL2_LIB_DIR C://libs/sdl2/lib/x86)
set(SDL2_IMAGES_DIR C://libs/sdl2_image/include)
set(SDL2_IMAGES_LIB_DIR C://libs/sdl2_image/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_IMAGES_DIR})
link_directories(${SDL2_IMAGES_LIB_DIR})


add_executable(dawn-engine src/main.cpp
        src/Nodes/Node2D.cpp
        include/Nodes/Node2D.h
        src/Nodes/Node.cpp
        include/Nodes/Node.h
        src/root.cpp
        include/root.h
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
        src/Nodes/CharacterBody2D.cpp
        include/Nodes/CharacterBody2D.h
        src/QuadTree.cpp
        include/QuadTree.h
)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 )
target_link_libraries(${PROJECT_NAME} SDL2_image SDL2)
