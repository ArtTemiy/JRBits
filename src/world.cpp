//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/world.hpp>

#include <glog/logging.h>

namespace Engine {

    void World::Draw() {
        for (const auto& [coordinates, tile] : map_) {
            tile->SetPosition(ToVector(coordinates));
            tile->Draw(*camera_);
        }

        for (auto& actor : actors_) {
            actor->Draw(*camera_);
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
            event_captured|=actor->GetController().ProcessEvent(event);
        }

        event_captured |= true;
        return event_captured;
    }
}
