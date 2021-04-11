//
// Created by Artemiy Shvedov on 02.04.21.
//

#pragma once

#include <TopDownEngine/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>
#include <TopDownEngine/map/i_tile.h>

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <memory>

namespace Engine {
    class GameTile : public DrawableStatic, public ITile {
    public:
        enum Type {
            kGrass,
            kDirt,
            kMountain,

            kNone
        };

    private:
        /// size of all tile
        static uint tile_size;

        Type type_ = kNone;

    public:
        static const auto GetTileSize() {
            return tile_size;
        }

        Type GetType() const {
            return type_;
        }

        void SetType(Type type) {
            type_ = type;
        }
    };

    class GameTilesTextureLoader {
        static bool data_loaded;
        static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
        static std::unordered_map<char, std::string> bindings;

    public:
        static bool GetDataLoaded() {
            return data_loaded;
        }

        static bool LoadData();

        static const std::unordered_map<std::string, std::shared_ptr<sf::Texture>>& GetTextures();

        static std::shared_ptr<GameTile> MakeTile(char c);
    };
}
