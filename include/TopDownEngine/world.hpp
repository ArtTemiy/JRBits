//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>
#include <TopDownEngine/map/map.hpp>
#include <TopDownEngine/object/actor.hpp>

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <memory>

namespace Engine {
    class World : public Tickable, IDrawable {
        Map map_;
        std::shared_ptr<Camera> camera_;

    public:
        World() : map_(0, 0), camera_(nullptr) {}

        const Map& GetMap() const {
            return map_;
        }

        void SetMap(const Map &map) {
            map_ = map;
            camera_->GetView().setCenter(
                    map_.GetSize()[0] * GameTile::GetTileSize() / 2,
                    map_.GetSize()[1] * GameTile::GetTileSize() / 2);
            camera_->UpdateView();
        }

        std::shared_ptr<Camera> &GetCamera() {
            return camera_;
        }

        void SetCamera(const std::shared_ptr<Camera> &camera) {
            camera_ = camera;
        }

        void Draw(const Coordinates &coordinates, Camera &camera) override {}

        void Draw();

        void SetSize(uint height, uint width) override {}

        void Tick(double time_delta) override;
    };
}
