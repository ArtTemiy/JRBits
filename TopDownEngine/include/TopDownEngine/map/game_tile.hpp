//
// Created by Artemiy Shvedov on 02.04.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>
#include <TopDownEngine/map/i_tile.hpp>

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <memory>

namespace Engine {
    /// Tile with DrawableComponent
    class GameTile : public Engine::Drawable::DrawableStatic, public ITile {
        /// size of all tile
        static Size tile_size;

    public:
        GameTile() = default;
        GameTile(const GameTile& other) = default;

        static const auto GetTileSize() {
            return tile_size;
        }

        void Draw(Drawable::Camera &camera) override;
    };
} // Engine
