//
// Created by ArtTemiy on 06.03.2021.
//

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include <TopDownEngine/map.hpp>

namespace Engine::Tests::PathFinding {
    struct TestData {
        TileCoordinates start_coord;
        TileCoordinates end_coord;
        bool found;
        size_t path_length;
    };

    class PatFindingTextFixture : public ::testing::Test {
    protected:
        static std::string map_files_prefix;
        static Map small_full_map;
        static Map big_full_map;
        static Map small_wall_map;
        static Map small_box_map;
        static Map small_river_map;
    };

    std::string PatFindingTextFixture::map_files_prefix = "tests/maps/map_resources/";
    Map PatFindingTextFixture::small_full_map(map_files_prefix + "full_small.map");
    Map PatFindingTextFixture::small_wall_map(map_files_prefix + "wall_small.map");
    Map PatFindingTextFixture::small_box_map(map_files_prefix + "box_small.map");
    Map PatFindingTextFixture::small_river_map(map_files_prefix + "river_small.map");

    void CheckPath(const Map& map, const std::vector<TileCoordinates>& coordinates) {
        auto map_size = map.GetSize();
        for (auto& coordinate : coordinates) {
            ASSERT_LT(coordinate[0], map_size[0]);
            ASSERT_LT(coordinate[1], map_size[1]);
            ASSERT_GE(coordinate[0], 0);
            ASSERT_GE(coordinate[1], 0);
            ASSERT_EQ(map.GetTile(coordinate).is_block, false);
        }
        for (size_t i = 0; i < coordinates.size() - 1; ++i) {
            bool step_correct = false;
            auto& coord1 = coordinates[i];
            auto& coord2 = coordinates[i + 1];
            ASSERT_EQ(
                    std::max(coord1[0], coord2[0]) - std::min(coord1[0], coord2[0]) +
                            std::max(coord1[1], coord2[1]) - std::min(coord1[1], coord2[1]),
                    1);
        }
    }

    void RunTestsOnTestData(Map& map, const std::vector<TestData>& test_data) {
        Path path;
        for (auto& test_data_element : test_data) {
            auto path_found = map.ComputePath(test_data_element.start_coord, test_data_element.end_coord, path);
            ASSERT_EQ(path_found, test_data_element.found);
            if (test_data_element.found) {
                ASSERT_EQ(path.size(), test_data_element.path_length);
                ASSERT_EQ(path.front(), test_data_element.start_coord);
                ASSERT_EQ(path.back(), test_data_element.end_coord);
                CheckPath(map, path);
            }
        }
    }


    TEST_F(PatFindingTextFixture, StraightLineSmall) {
        const std::vector<TestData> test_data = {
                { {1, 1}, {4, 1}, true, 4 },
                { {1, 1}, {1, 2}, true, 2 },
                { {1, 1}, {1, 1}, true, 1 },
                { {0, 0}, {0, 5}, true, 6 },
        };
        RunTestsOnTestData(small_full_map, test_data);
    }

    TEST_F(PatFindingTextFixture, SimpleTurnSmall) {
        const std::vector<TestData> test_data = {
                { {1, 1}, {2, 2}, true, 3 },
                { {0, 0}, {5, 5}, true, 11 }
        };
        RunTestsOnTestData(small_full_map, test_data);
    }

    TEST_F(PatFindingTextFixture, WallSmall) {
        const std::vector<TestData> test_data = {
                { {1, 2}, {4, 2}, true, 8 },
                { {1, 3}, {4, 3}, true, 8 }
        };
        RunTestsOnTestData(small_wall_map, test_data);
    }

    TEST_F(PatFindingTextFixture, BoxSmall) {
        const std::vector<TestData> test_data = {
                { {3, 2}, {0, 0}, false, 0 }
        };
        RunTestsOnTestData(small_box_map, test_data);
    }

    TEST_F(PatFindingTextFixture, RiverSmall) {
        const std::vector<TestData> test_data = {
                { {1, 3}, {4, 4}, false, 0 }
        };
        RunTestsOnTestData(small_river_map, test_data);
    }
}