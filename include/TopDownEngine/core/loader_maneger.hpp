//
// Created by Artemiy Shvedov on 18.04.21.
//

#pragma once

#include "TopDownEngine/core/loader.hpp"

#include <glog/logging.h>

namespace Engine {
    struct LoaderManager {
        static TextureLoader actor_textures_loader;
        static TextureLoader game_tile_textures_loader;

        static bool LoadData() {
            LOG(INFO) << "Loading all data:";
            auto success = actor_textures_loader.LoadData() &&
                           game_tile_textures_loader.LoadData() &&
                           true;
            LOG(INFO) << "Attempt to load data finished " << (success ? "successfully" : "with some errors");
            return success;
        }
    };
}