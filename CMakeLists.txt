cmake_minimum_required(VERSION 3.15)
project(TopDownEngine)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# SFML
add_subdirectory("deps/SFML")
set(SFML_LIB sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# GTEST
add_subdirectory("deps/gtest")
set(WITH_GFLAGS false)
add_subdirectory("deps/glog")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# ENGINE LIBRARY
set(HEADER_LIST
        include/TopDownEngine/Core.h
        include/TopDownEngine/Drawable.hpp
        include/TopDownEngine/Map.h
        include/TopDownEngine/controller/controller.h
        include/TopDownEngine/object/dynamic_object.h
        include/TopDownEngine/object/actor.h)

add_library(top_down_engine
        ${HEADER_LIST}
        src/Core.cpp
        src/Drawable.cpp
        src/Map.cpp
        src/object/dynamic_object.cpp
        src/controller/controller.cpp
        src/object/dynamic_object.cpp
        src/object/actor.cpp)

target_link_libraries(top_down_engine ${SFML_LIB})
target_include_directories(top_down_engine PUBLIC include)
target_link_libraries(top_down_engine glog)


# TESTS
add_subdirectory(tests)
target_link_libraries(tests gtest gtest_main)
