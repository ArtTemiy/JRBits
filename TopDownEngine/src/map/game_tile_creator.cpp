//
// Created by Artemiy Shvedov on 31.07.21.
//

#include <TopDownEngine/map/game_tile_creator.hpp>
#include <TopDownEngine/load_manager/loader_maneger.hpp>

#include <yaml-cpp/yaml.h>

namespace Engine::Loader {
    bool GameTileCreator::LoadData() {
        auto config = YAML::LoadFile(kConfigPath);
        for (YAML::const_iterator it = config.begin(); it != config.end(); ++it) {
            auto name = it->first.as<std::string>();
            auto& description = it->second;
            auto is_block = description["block"].as<bool>();
            auto code = description["code"].as<char>();
            auto texture_name = description["texture"].as<std::string>();
            auto tile = std::make_shared<GameTile>();
            tile->SetIsBlock(is_block);
            tile->SetSprite(sf::Sprite(*LoaderManager::game_tile_textures_loader.GetData().at(texture_name)));
            tile->SetSize(GameTile::GetTileSize());
            data_[code] = tile;
        }
        return true;
    }

    std::shared_ptr<GameTile> GameTileCreator::MakeTile(char code) {
        auto it = data_.find(code);
        if (it == data_.end()) {
            LOG(ERROR) << "No tile for code " << code << " aka " << static_cast<int>(code) << ". (Return empty tile)";
            return std::make_shared<GameTile>();
        }
        return std::make_shared<GameTile>(*it->second);
    }
} // Engine::Loader