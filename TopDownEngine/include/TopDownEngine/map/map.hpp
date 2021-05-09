//
// Created by ArtTemiy on 26.02.2021.
//
#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/map/game_tile.hpp>

#include <vector>
#include <list>
#include <array>
#include <unordered_map>
#include <memory>
#include <ostream>

namespace Engine {
    using TileCoordinates = std::array<uint, 2>;
    using MapSize = std::array<uint, 2>;
    using Path = std::vector<TileCoordinates>;

    /// Map contains titles, supporting pathfinding
    class Map {
    public:
        using Tile = GameTile;
        using TilePtr = std::shared_ptr<Tile>;

        class Iterator {
            Map* map_;
            uint row_, column_;

        public:
            /// Iterator for tiles - contains coordinates and tele itself
            Iterator(Map* map, size_t row, size_t column) : map_(map), row_(row), column_(column) {}

            bool operator==(const Iterator& other) const {
                return (row_ == other.row_) && (column_ == other.column_);
            }

            bool operator!=(const Iterator& other) const {
                return !(*this == other);
            }

            std::pair<TileCoordinates, Map::TilePtr> operator*() const {
                return {{row_, column_}, map_->GetTile(row_, column_)};
            }

            Iterator& operator++() {
                if (row_ >= map_->GetSize()[0]) {
                    return *this;
                }
                ++column_;
                if (column_ == map_->GetSize()[1]) {
                    column_ = 0;
                    ++row_;
                }
                return *this;
            }

            friend std::ostream &operator<<(std::ostream &os, const Iterator &iterator);
        };

    private:
        uint height_;
        uint width_;
        std::vector<std::vector<TilePtr>> tiles_;

    public:
        Map(uint height, uint width)
            : height_(height),
              width_(width),
              tiles_(height, std::vector<TilePtr>(width)) {}

        explicit Map(std::vector<std::vector<TilePtr>> tiles)
            : height_(tiles.size()),
              width_(!tiles.empty() ? tiles[0].size() : 0),
              tiles_(std::move(tiles)) {}

        explicit Map(const std::string& path_to_map_file) {
            *this = LoadMapFromFile(path_to_map_file);
        }

        MapSize GetSize() const;

        TilePtr GetTile(uint row, uint column);

        TilePtr GetTile(const TileCoordinates& coordinates);

        const TilePtr GetTile(uint row, uint column) const;

        const TilePtr GetTile(const TileCoordinates& coordinates) const;

        std::vector<TilePtr>& operator[](uint row);

        const std::vector<TilePtr>& operator[](uint row) const;

        Iterator begin() {
            return Iterator(this, 0, 0);
        }

        Iterator end() {
            return Iterator(this, height_, 0);
        }

        /// Computes path between given tile
        /// @param [in] start_tile Start tile
        /// @param [in] end_tile End tile
        /// @param [out] path Path between tile
        /// @return Path was found
        bool ComputePath(const TileCoordinates& start_tile, const TileCoordinates& end_tile, Path& path);

        /// Loads map from file
        static Map LoadMapFromFile(const std::string& path_to_map_file);
    };
}