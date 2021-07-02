//
// Created by Artemiy Shvedov on 18.04.21.
//

#include <TopDownEngine/core/loader_maneger.hpp>

namespace Engine {
    TextureLoader LoaderManager::actor_textures_loader("rsrc/textures/actors",  "Actor Texture Loader");
    TextureLoader LoaderManager::game_tile_textures_loader("rsrc/textures/tiles", "Game Tile Texture Loader");
}