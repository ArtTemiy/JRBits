# SFML
add_subdirectory("deps/SFML")
set(SFML_LIB sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# GTEST
add_subdirectory("deps/gtest")
set(WITH_GFLAGS false)
add_subdirectory("deps/glog")

# ENGINE LIBRARY
file(GLOB src_files src/*)

add_library(top_down_engine
        src/core/core.cpp
        src/drawable/drawable.cpp
        src/map/map.cpp
        src/object/dynamic_object.cpp
        src/controller/controller.cpp
        src/object/dynamic_object.cpp
        src/object/actor.cpp
        src/world.cpp
        src/controller/player_controller.cpp
        src/physics/vector.cpp
        src/map/game_tile.cpp
        src/map/i_tile.cpp
        src/launcher/launcher.cpp
        src/core/loader.cpp
        src/core/loader_manager.cpp
        src/drawable/camera.cpp
        src/utils/display_logger.cpp
        src/launcher/level.cpp
        src/launcher/launcher.cpp
        src/interface/interface.cpp)

target_link_libraries(top_down_engine ${SFML_LIB})
target_include_directories(top_down_engine PUBLIC include)
target_link_libraries(top_down_engine glog)


# TESTS
add_subdirectory(tests)
