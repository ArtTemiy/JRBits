//
// Created by Artemiy Shvedov on 02.04.21.
//

#include <TopDownEngine/map/game_tile.hpp>

#include <glog/logging.h>

namespace Engine {
    uint GameTile::tile_size = 100;

    std::unordered_map<char, std::string> GameTilesTextureLoader::bindings = {
            {'.', "grass"},
            {'x', "mountain"},
            {'#', "dirt"}
    };

    std::shared_ptr<GameTile> GameTilesTextureLoader::MakeTile(char c) {
        const std::unordered_map<std::string, std::shared_ptr<sf::Texture>>&
            textures = LoaderManager::game_tile_textures_loader.GetData();

        auto tile = std::make_shared<GameTile>();
        tile->LoadSprite(*textures.at(bindings.at(c)));
        tile->SetSize(GameTile::GetTileSize(), GameTile::GetTileSize());
        return tile;
    }
}
