//
// Created by ArtTemiy on 26.02.2021.
//
#pragma once

#include <vector>
#include <list>
#include <array>
#include <unordered_map>
#include <memory>

namespace Engine {
    /// Tile structure
    class Tile {
    public:
        bool GetIsBlock() const {
            return is_block;
        }

        void SetIsBlock(bool isBlock) {
            is_block = isBlock;
        }

    private:
        bool is_block = false;
    public:
    };

    using TilePtr = std::shared_ptr<Tile>;
    using uint = uint32_t;
    using TileCoordinates = std::array<uint, 2>;
    using MapSize = std::array<uint, 2>;
    using Path = std::vector<TileCoordinates>;

    /// Map contains titles, supporting pathfinding
    template <class Tile>
    class Map {
        using TilePtr = std::shared_ptr<Tile>;
        
        uint width_;
        uint height_;
        std::vector<std::vector<TilePtr>> tiles_;

    public:
        Map(uint width, uint height)
            : width_(width),
              height_(height),
              tiles_(height, std::vector<Tile>(width)) {}

        explicit Map(std::vector<std::vector<Tile>> tiles)
            : width_(tiles.size()),
              height_(!tiles.empty() ? tiles[0].size() : 0),
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