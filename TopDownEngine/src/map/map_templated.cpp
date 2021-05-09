//
// Created by ArtTemiy on 26.02.2021.
//

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <filesystem>

#include <glog/logging.h>

#include <TopDownEngine/map/map.hpp>

namespace Engine {
    template <class Tile>
    MapSize Map<Tile>::GetSize() const {
        return { height_, width_ };
    }

    template <class Tile>
    std::shared_ptr<Tile> Map<Tile>::GetTile(uint row, uint column) {
        return tiles_[row][column];
    }

    template <class Tile>
    std::shared_ptr<Tile> Map<Tile>::GetTile(const TileCoordinates &coordinates) {
        return tiles_[coordinates[0]][coordinates[1]];
    }

    template <class Tile>
    const std::shared_ptr<Tile> Map<Tile>::GetTile(uint row, uint column) const {
        return tiles_[row][column];
    }

    template <class Tile>
    const std::shared_ptr<Tile> Map<Tile>::GetTile(const TileCoordinates &coordinates) const {
        return tiles_[coordinates[0]][coordinates[1]];
    }

    template <class Tile>
    const std::vector<std::shared_ptr<Tile>>& Map<Tile>::operator[](uint row) const {
        return tiles_[row];
    }

    template <class Tile>
    std::vector<std::shared_ptr<Tile>>& Map<Tile>::operator[](uint row) {
        return tiles_[row];
    }

    template <class Tile>
    bool Map<Tile>::ComputePath(const TileCoordinates &start_tile, const TileCoordinates &end_tile, Path &path) {
        // Enum for path restoring
        enum DirectionRecover {
            kNotVisited,
            kLeft,
            kRight,
            kUp,
            kDown,
            kEndTile
        };
        // visited tile
        std::vector<std::vector<DirectionRecover>> visited_tiles(
                height_, std::vector<DirectionRecover>(width_, kNotVisited));

        // queue for visiting tile
        std::queue<std::pair<TileCoordinates, DirectionRecover>> tiles_queue;
        tiles_queue.push({end_tile, kEndTile});
        bool search_finished = false;

        while (!tiles_queue.empty()) {
            auto[coordinates, direction] = tiles_queue.front();
            tiles_queue.pop();
            auto next_tile = GetTile(coordinates);
            if (next_tile.GetIsBlock() || visited_tiles[coordinates[0]][coordinates[1]] != kNotVisited) {
                continue;
            }
            visited_tiles[coordinates[0]][coordinates[1]] = direction;

            if (coordinates == start_tile) {
                search_finished = true;
                break;
            }

            // Add next tile into queue
            if (coordinates[0] > 0 && visited_tiles[coordinates[0] - 1][coordinates[1]] == kNotVisited) {
                tiles_queue.push({{coordinates[0] - 1, coordinates[1]}, kDown});
            }
            if (coordinates[0] < height_ - 1 && visited_tiles[coordinates[0] + 1][coordinates[1]] == kNotVisited) {
                tiles_queue.push({{coordinates[0] + 1, coordinates[1]}, kUp});
            }
            if (coordinates[1] > 0 && visited_tiles[coordinates[0]][coordinates[1] - 1] == kNotVisited) {
                tiles_queue.push({{coordinates[0], coordinates[1] - 1}, kRight});
            }
            if (coordinates[1] < width_ - 1 && visited_tiles[coordinates[0]][coordinates[1] + 1] == kNotVisited) {
                tiles_queue.push({{coordinates[0], coordinates[1] + 1}, kLeft});
            }
        }
        if (!search_finished) {
            return false;
        }

        // path restoring
        auto tile = start_tile;
        path = {};
        while (tile != end_tile) {
            path.push_back(tile);
            switch (visited_tiles[tile[0]][tile[1]]) {
                case kLeft:
                    tile = {tile[0], tile[1] - 1};
                    break;
                case kRight:
                    tile = {tile[0], tile[1] + 1};
                    break;
                case kDown:
                    tile = {tile[0] + 1, tile[1]};
                    break;
                case kUp:
                    tile = {tile[0] - 1, tile[1]};
                    break;
                default:
                    // if my code sucks
                    LOG(ERROR) << "My code sucks!";
                    throw std::runtime_error("Direction for tile not specified");
            }
        }
        path.push_back(end_tile);
        return true;
    }

    template <class Tile>
     Map<Tile> Map<Tile>::LoadMapFromFile(const std::string &path_to_map_file) {
        std::ifstream map_file(path_to_map_file);
        if (!map_file.is_open()) {
            LOG(ERROR) << "Was not able to open map source file with `" << path_to_map_file << "` in `" << std::filesystem::current_path() << "`";
            LOG(ERROR) << strerror(errno);
            throw std::runtime_error("Map loading error");
        }

        // reading map size
        unsigned int width = 0, height = 0;
        map_file >> width >> height;
        LOG(INFO) << "Loading map with size: h: " << height << ", w: " << width << std::endl;

         std::vector<std::vector<Tile>> tiles(height, std::vector<Tile>(width));

        // reading map tile
        for (uint row = 0; row < height; ++row) {
            for (uint column = 0; column < width; ++column) {
                char tile_code = 0;
                Tile tile;
                map_file >> tile_code;
                switch (tile_code) {
                    case '.':
                        tile.SetIsBlock(false);
                        break;
                    case 'x':
                        tile.SetIsBlock(true);
                        break;
                    default:
                        throw std::runtime_error("unknown tile code");
                }
                tiles[row][column] = tile;
            }
        }
        map_file.get();
        if (!map_file.eof()) {
            LOG(ERROR) << "End of file was not reached" << std::endl;
            std::string last_characters;
            while (!map_file.eof()) {
                char c;
                map_file >> c;
                last_characters += std::to_string(static_cast<int>(c)) + " ";
            }
            LOG(INFO) << last_characters;
        }
        return Map(tiles);
    }
}