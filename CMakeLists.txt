cmake_minimum_required(VERSION 3.15)
project("JRBits")

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory("TopDownEngine")

add_executable(game
        Game/src/Game.cpp
        Game/src/camera/camera_target_controller.cpp
#        Game/src/camera/target_camera.cpp
        Game/src/actor_creator_helper/actor_creator_helper.cpp)

target_link_libraries(game top_down_engine)
target_include_directories(game PUBLIC Game/src)
