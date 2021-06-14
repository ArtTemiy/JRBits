add_executable(gtests
        maps/tests_pathfinding.cpp
        maps/tests_map_loading.cpp
        tests_empty.cpp)

target_link_libraries(gtests
        top_down_engine
        gtest
        gtest_main)

add_executable(test_display
        view_and_moving/display.cpp)

target_link_libraries(test_display
        top_down_engine
        ${SFML_LIB})

add_executable(test_player_actor_moving
        view_and_moving/player_actor_moving.cpp)

target_link_libraries(test_player_actor_moving
        top_down_engine
        ${SFML_LIB})

add_executable(test_collision
        view_and_moving/collision_blocks_moving.cpp)

target_link_libraries(test_collision
        top_down_engine
        ${SFML_LIB})