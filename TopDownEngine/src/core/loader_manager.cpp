//
// Created by Artemiy Shvedov on 18.04.21.
//

#include <TopDownEngine/core/loader_maneger.hpp>

namespace Engine {
    TextureLoader LoaderManager::actor_textures_loader("rsrc/textures/actors/", {
            "circle"
        }, "Actor Texture Loader");
    TextureLoader LoaderManager::game_tile_textures_loader("rsrc/textures/tile", {
            "dirt",
            "grass",
            "mountain"
        }, "Game Tile Texture Loader");
}