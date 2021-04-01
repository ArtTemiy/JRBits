add_executable(tests
        maps/tests_pathfinding.cpp
        maps/tests_map_loading.cpp
        tests_empty.cpp)

target_link_libraries(tests
        top_down_engine
        gtest gtest_main)
