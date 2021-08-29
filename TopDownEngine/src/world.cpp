//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/world/world.hpp>
#include <TopDownEngine/controller/null_controller.hpp>
#include <TopDownEngine/object/invisible_actor.hpp>

#include <glog/logging.h>


namespace Engine {

    void World::Draw() {
        camera_->UpdateView();
        for (const auto&[coordinates, tile] : map_) {
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

        // process collisions
        for (auto& dynamic_actor : dynamic_actors_) {
            for (auto& static_actor : static_actors_) {
                ProcessCollision(*dynamic_actor, *static_actor);
            }
        }

        // tick camera
        camera_->Tick(time_delta);
    }

    bool World::ProcessEvent(sf::Event& event) {
        bool event_captured = false;
        for (auto& actor : non_collision_actors_) {
            event_captured |= actor->GetController()->ProcessEvent(event);
        }
        for (auto& actor : static_actors_) {
            event_captured |= actor->GetController()->ProcessEvent(event);
        }
        for (auto& actor : dynamic_actors_) {
            event_captured |= actor->GetController()->ProcessEvent(event);
        }
        if (event_captured) {
            return true;
        }

        event_captured |= true;
        return event_captured;
    }

    void World::AddActor(const std::shared_ptr<Actor>& actor) {
        actor->SetWorld(this);
        switch (actor->GetCollisionType()) {
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

    void World::RemoveActor(const std::shared_ptr<Actor>& actor) {
        switch (actor->GetCollisionType()) {
            case DynamicObject::kDynamic:
                dynamic_actors_.erase(actor);
                break;
            case DynamicObject::kStatic:
                static_actors_.erase(actor);
                break;
            case DynamicObject::kNoCollision:
                non_collision_actors_.erase(actor);
                break;
            default:
                break;
        }
    }

    void World::ClearActors() {
        std::list<std::shared_ptr<Actor>> actors_to_remove = {};
        for (auto& actor : dynamic_actors_) {
            if (actor->IsDestroy()) {
                actors_to_remove.push_back(actor);
            }
        }
        for (auto& actor : static_actors_) {
            if (actor->IsDestroy()) {
                actors_to_remove.push_back(actor);
            }
        }
        for (auto& actor : non_collision_actors_) {
            if (actor->IsDestroy()) {
                actors_to_remove.push_back(actor);
            }
        }

        for (auto& actor : actors_to_remove) {
            RemoveActor(actor);
        }
    }

    void World::OnActorEdit(const std::shared_ptr<Actor>& actor) {
        RemoveActor(actor);
        AddActor(actor);
    }

    void World::SetMap(const Map& map) {
        map_ = map;
        if (camera_) {
            camera_->GetView().setCenter(
                    map_.GetSize()[0] * GameTile::GetTileSize()[0] / 2,
                    map_.GetSize()[1] * GameTile::GetTileSize()[1] / 2);
            // TODO why?
            // camera_->UpdateView();
        }

        // create static map objects
        for (const auto& [coordinates, tile] : map_) {
            if (tile->IsBlock()) {
                LOG(INFO) << "Add tile actor";
                InvisibleActor actor(DynamicObject(coordinates, GameTile::GetTileSize(), 0., DynamicObject::CollisionType::kStatic), this);
                actor.SetController(std::make_shared<Controller::NullController>());
                AddActor(std::move(actor));
            }
        }
    }

    World::ActorSet World::ActorsInArea(const Object& box) {
        ActorSet result = {};
        for (const auto& actor : Actors()) {
            if (box.Intersects(*actor)) {
                result.insert(actor);
            }
        }
        return result;
    }
} // namespace Engine
