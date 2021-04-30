//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/world.hpp>

#include <glog/logging.h>

namespace Engine {

    void World::Draw() {
//        for (auto [coordinates, tile] : map_) {
        for (auto it : map_) {
            const auto& [coordinates, tile] = it;
            tile->Draw(
            {
                static_cast<double>(coordinates[0] * GameTile::GetTileSize()),
                static_cast<double>(coordinates[1] * GameTile::GetTileSize())
                },
            *camera_
            );
        }

        for (auto& actor : actors_) {
            actor->Draw(actor->GetCoordinates(), *camera_);
        }
    }

    void World::Tick(double time_delta) {
        camera_->Tick(time_delta);
        for (auto& actor : actors_) {
            actor->Tick(time_delta);
        }
    }

    bool World::ProcessEvent(sf::Event &event) {
        bool event_captured = false;
        for (auto& actor : actors_) {
            event_captured|=actor->GetController()->ProcessEvent(event);
        }

        event_captured |= true;
        return event_captured;
    }
}
