//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/world/world_fwd.hpp>

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>
#include <TopDownEngine/map/map.hpp>
#include <TopDownEngine/object/actor.hpp>
#include <TopDownEngine/interface/interface.hpp>

#include <SFML/Window.hpp>

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <memory>

namespace Engine {
    class World : public Tickable {
        using Camera = Drawable::ICamera;

        Map map_;
        std::shared_ptr<Camera> camera_;
        std::unordered_set<std::shared_ptr<IActor>> static_actors_;
        std::unordered_set<std::shared_ptr<IActor>> dynamic_actors_;
        std::unordered_set<std::shared_ptr<IActor>> non_collision_actors_;

    public:
        World() : map_(0, 0), camera_(nullptr) {}

        const Map& GetMap() const {
            return map_;
        }

        void SetMap(const Map &map) {
            map_ = map;
            if (camera_) {
                camera_->GetView().setCenter(
                        map_.GetSize()[0] * GameTile::GetTileSize()[0] / 2,
                        map_.GetSize()[1] * GameTile::GetTileSize()[1] / 2);
                camera_->UpdateView();
            }
        }

        std::shared_ptr<Camera> &GetCamera() {
            return camera_;
        }

        void SetCamera(const std::shared_ptr<Camera> &camera) {
            camera_ = camera;
            camera_->GetView().setCenter(
                    map_.GetSize()[0] * GameTile::GetTileSize()[0] / 2,
                    map_.GetSize()[1] * GameTile::GetTileSize()[1] / 2);
            camera_->UpdateView();
        }

        void AddObject(const std::shared_ptr<IActor>& actor);

        void Draw();

        void Tick(double time_delta) override;

        bool ProcessEvent(sf::Event& event);
    };
}
