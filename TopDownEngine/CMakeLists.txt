# SFML
add_subdirectory("deps/SFML")
set(SFML_LIB sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# GTEST, GLOG
add_subdirectory("deps/gtest")
set(WITH_GFLAGS false)
add_subdirectory("deps/glog")

# YAML
add_subdirectory("deps/yaml-cpp")

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
        src/core/loaders/loader.cpp
        src/core/loaders/texture_loader.cpp
        src/core/loader_manager.cpp
        src/drawable/camera.cpp
        src/drawable/drawable_utils.cpp
        src/utils/display_logger.cpp
        src/launcher/level.cpp
        src/launcher/launcher.cpp
        src/interface/interface.cpp
        src/map/game_tile_creator.cpp
        src/interface/message.cpp
        src/drawable/drawable_screen.cpp
        src/core/loaders/font_loader.cpp src/launcher/level_config.cpp src/launcher/launcher_config.cpp)

target_include_directories(top_down_engine PUBLIC include)
target_link_libraries(top_down_engine ${SFML_LIB})
target_link_libraries(top_down_engine glog)
target_link_libraries(top_down_engine yaml-cpp)


# TESTS
add_subdirectory(tests)
