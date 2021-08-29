//
// Created by Artemiy Shvedov on 02.04.21.
//

#include <TopDownEngine/map/game_tile.hpp>

#include <glog/logging.h>

namespace Engine {
    Size GameTile::tile_size = {1, 1};

    void GameTile::Draw(Drawable::Camera &camera) {
        DrawableStatic::Draw(camera);
    }
} // Engine
