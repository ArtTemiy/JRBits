//
// Created by ArtTemiy on 24.03.2021.
//


#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include <TopDownEngine/map/map.hpp>

namespace Engine::Tests::MapLoading {
    TEST(MapLoading, SmallFull) {
        auto map = Map::LoadMapFromFile("rsrc/maps/full_small.map");
        MapSize expected_size{6, 6};
        EXPECT_EQ(map.GetSize(), expected_size);
        for (size_t i = 0; i < map.GetSize()[0]; ++i) {
            for (size_t j = 0; j < map.GetSize()[1]; ++j) {
                EXPECT_EQ(map.GetTile(i, j)->GetIsBlock(), false);
            }
        }
    }
}
