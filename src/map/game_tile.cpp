//
// Created by Artemiy Shvedov on 02.04.21.
//

#include <TopDownEngine/map/game_tile.h>

#include <glog/logging.h>

namespace Engine {
    uint GameTile::tile_size = 128;

    bool GameTilesTextureLoader::data_loaded = false;

    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> GameTilesTextureLoader::textures = {};
    std::unordered_map<char, std::string> GameTilesTextureLoader::bindings = {
            {'.', "grass"},
            {'x', "mountain"},
            {'#', "dirt"}
    };

    bool GameTilesTextureLoader::LoadData() {
        std::string rsrc_dir = "rsrc/textures/tile/";
        std::vector<std::string> file_names = {"grass", "dirt", "mountain"};
        for (auto& file_name : file_names) {
            std::shared_ptr<sf::Texture> texture(new sf::Texture());
            if (!texture->loadFromFile(rsrc_dir + file_name + ".png")) {
                LOG(WARNING) << "Wasn't able to load texture: " << file_name;
                return false;
            }
            textures[file_name] = texture;
        }
        LOG(INFO) << "GameTile textures loaded successfully";
        data_loaded = true;
        return true;
    }

    const std::unordered_map<std::string, std::shared_ptr<sf::Texture>>& GameTilesTextureLoader::GetTextures() {
        return textures;
    }

    std::shared_ptr<GameTile> GameTilesTextureLoader::MakeTile(char c) {
        if (!GetDataLoaded()) {
            LoadData();
        }

        auto tile = std::make_shared<GameTile>();
        switch (c) {
            case '.':
                tile->LoadSprite(*textures.at("grass"));
                tile->SetType(GameTile::kGrass);
                break;
            case 'x':
                tile->LoadSprite(*textures.at("mountain"));
                tile->SetType(GameTile::kMountain);
                tile->SetIsBlock(true);
                break;
            case '#':
                tile->LoadSprite(*textures.at("dirt"));
                tile->SetType(GameTile::kDirt);
                break;
            default:
                throw std::runtime_error(&"Unknown char: " [ c]);
        }
        tile->SetSize(GameTile::GetTileSize(), GameTile::GetTileSize());
        return tile;
    }
}
