//
// Created by Artemiy Shvedov on 18.04.21.
//

#pragma once

#include <TopDownEngine/map/game_tile_creator.hpp>
#include <TopDownEngine/core/loaders/texture_loader.hpp>
#include <TopDownEngine/core/loaders/font_loader.hpp>

#include <glog/logging.h>

namespace Engine::Loader {
    struct LoaderManager {
        inline static TextureLoader actor_textures_loader     { "rsrc/textures/actors",    "Actor Texture Loader"     };
        inline static TextureLoader game_tile_textures_loader { "rsrc/textures/tiles",     "Game Tile Texture Loader" };
        inline static TextureLoader interface_loader          { "rsrc/textures/interface", "Interface Texture Loader" };
        inline static FontLoader    font_loader               { "configs/fonts.yaml",      "Fonts Loader"             };

        inline static GameTileCreator game_tile_creator{};

        static bool LoadData() {
            LOG(INFO) << "Loading all data:";
            auto success = actor_textures_loader.LoadData() &&
                           game_tile_textures_loader.LoadData() &&
                           game_tile_creator.LoadData() &&
                           interface_loader.LoadData() &&
                           font_loader.LoadData() &&
                           true;
            LOG(INFO) << "Attempt to load data finished " << (success ? "successfully" : "with some errors");
            return success;
        }
    };
} // namespace Engine::Loader