add_executable(gtests
        maps/tests_pathfinding.cpp
        maps/tests_map_loading.cpp
        tests_empty.cpp)

target_link_libraries(gtests
        top_down_engine
        gtest
        gtest_main)

macro(add_exec_test TEST_NAME TEST_SRC)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME}
            top_down_engine
            ${SFML_LIB})
endmacro()

add_exec_test(test_view_display
        view_and_moving/display.cpp)

add_exec_test(test_view_player_actor_moving
        view_and_moving/player_actor_moving.cpp)

add_exec_test(test_view_collision
        view_and_moving/collision_blocks_moving.cpp)

add_exec_test(test_interface_message interface/message.cpp)