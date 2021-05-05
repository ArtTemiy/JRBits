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

        for (auto& actor : non_collision_actors_) {
            actor->Draw(*camera_);
        }
        for (auto& actor : static_actors_) {
            actor->Draw(*camera_);
        }
        for (auto& actor : dynamic_actors_) {
            actor->Draw(*camera_);
        }
    }

    void World::Tick(double time_delta) {
        // tick all the actors
        for (auto& actor : non_collision_actors_) {
            actor->Tick(time_delta);
        }
        for (auto& actor : static_actors_) {
            actor->Tick(time_delta);
        }
        for (auto& actor : dynamic_actors_) {
            actor->Tick(time_delta);
        }

        for (auto& dynamic_actor : dynamic_actors_) {
            for(auto& static_actor : static_actors_) {
                ProcessCollision(*dynamic_actor, *static_actor);
            }
        }

        // tick camera
        camera_->Tick(time_delta);

        // process collisions
    }

    bool World::ProcessEvent(sf::Event &event) {
        bool event_captured = false;
        for (auto& actor : non_collision_actors_) {
            event_captured|=actor->GetController().ProcessEvent(event);
        }
        for (auto& actor : static_actors_) {
            event_captured|=actor->GetController().ProcessEvent(event);
        }
        for (auto& actor : dynamic_actors_) {
            event_captured|=actor->GetController().ProcessEvent(event);
        }

        event_captured |= true;
        return event_captured;
    }

    void World::AddObject(const std::shared_ptr<IActor> &actor) {
        switch (actor->GetCollisionDynamic()) {
            case DynamicObject::kDynamic:
                dynamic_actors_.insert(actor);
                break;
            case DynamicObject::kStatic:
                static_actors_.insert(actor);
                break;
            case DynamicObject::kNoCollision:
                non_collision_actors_.insert(actor);
                break;
            default:
                throw std::runtime_error("What the fuck with the collision type?");
        }
    }
}
