//
// Created by Artemiy Shvedov on 31.07.21.
//

#pragma once

#include "game_tile.hpp"
#include <TopDownEngine/core/loaders/loader.hpp>

namespace Engine::Loader {
    class GameTileCreator : public Loader<GameTile, char> {
        inline static const std::string kConfigPath = "configs/game_tiles.yaml";

    public:
        bool LoadData() override;
        std::shared_ptr<GameTile> MakeTile(char code);
    };
} // Engine::Loader