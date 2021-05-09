//
// Created by Artemiy Shvedov on 02.04.21.
//

#include <TopDownEngine/map/game_tile.hpp>

#include <glog/logging.h>

namespace Engine {
    Size GameTile::tile_size = {1, 1};

    void GameTile::Draw(Drawable::ICamera &camera) {
        DrawableStatic::Draw(camera);
    }

    std::unordered_map<char, std::string> GameTilesTextureLoader::bindings = {
            {'.', "grass"},
            {'x', "mountain"},
            {'#', "dirt"}
    };

    std::shared_ptr<GameTile> GameTilesTextureLoader::MakeTile(char c) {
        const std::unordered_map<std::string, std::shared_ptr<sf::Texture>>&
            textures = LoaderManager::game_tile_textures_loader.GetData();

        auto tile = std::make_shared<GameTile>();
        tile->LoadTexture(*textures.at(bindings.at(c)));
        tile->SetSize(GameTile::GetTileSize());
        return tile;
    }
}
