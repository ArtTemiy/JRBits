//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/world.hpp>

#include <glog/logging.h>

namespace Engine {

    void World::Draw() {
//        for (auto [coordinates, tile] : map_) {
        for (auto it = map_.begin(); it != map_.end(); ++it) {
            auto [coordinates, tile] = *it;
            tile->Draw(
            {
                static_cast<double>(coordinates[0] * GameTile::GetTileSize()),
                static_cast<double>(coordinates[1] * GameTile::GetTileSize())
                },
            *camera_
            );
        }
    }

    void World::Tick(double time_delta) {
        camera_->Tick(time_delta);
    }
}
