//
// Created by Artemiy Shvedov on 02.04.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>
#include <TopDownEngine/map/i_tile.hpp>
#include <TopDownEngine/core/loader_maneger.hpp>

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <memory>

namespace Engine {
    class GameTile : public Drawable::DrawableStatic, public ITile {
    public:
        enum Type {
            kGrass,
            kDirt,
            kMountain,

            kNone
        };

    private:
        /// size of all tile
        static Size tile_size;

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

        void Draw(Drawable::ICamera &camera) override;
    };

    class GameTilesTextureLoader {
        static std::unordered_map<char, std::string> bindings;

    public:
        static std::shared_ptr<GameTile> MakeTile(char c);
    };
}
