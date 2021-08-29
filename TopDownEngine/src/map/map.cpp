//
// Created by ArtTemiy on 26.02.2021.
//

#include <TopDownEngine/map/map.hpp>
#include <TopDownEngine/map/game_tile_creator.hpp>
#include <TopDownEngine/load_manager/loader_maneger.hpp>

#include <glog/logging.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <filesystem>

namespace Engine {
    using Tile = Map::Tile;
    using TilePtr = Map::TilePtr;

    MapSize Map::GetSize() const {
        return { height_, width_ };
    }

    TilePtr Map::GetTile(uint row, uint column) {
        return tiles_[row][column];
    }

    TilePtr Map::GetTile(const TileCoordinates &coordinates) {
        return tiles_[coordinates[0]][coordinates[1]];
    }

    const TilePtr Map::GetTile(uint row, uint column) const {
        return tiles_[row][column];
    }

    const TilePtr Map::GetTile(const TileCoordinates &coordinates) const {
        return tiles_[coordinates[0]][coordinates[1]];
    }

    const std::vector<TilePtr>& Map::operator[](uint row) const {
        return tiles_[row];
    }

    std::vector<TilePtr>& Map::operator[](uint row) {
        return tiles_[row];
    }

    bool Map::ComputePath(const TileCoordinates &start_tile, const TileCoordinates &end_tile, Path &path) {
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
            if (next_tile->IsBlock() || visited_tiles[coordinates[0]][coordinates[1]] != kNotVisited) {
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

     Map Map::LoadMapFromFile(const std::string &path_to_map_file) {
        std::ifstream map_file(path_to_map_file);
        if (!map_file.is_open()) {
            LOG(ERROR) << "Was not able to open map source file with `" << path_to_map_file << "` in `" << std::filesystem::current_path() << "`";
            LOG(ERROR) << strerror(errno);
            throw std::runtime_error("Map loading error");
        }

        // reading map size
        unsigned int width = 0, height = 0;
        map_file >> height >> width;
        LOG(INFO) << "Loading map with size: h: " << height << ", w: " << width << std::endl;

         std::vector<std::vector<TilePtr>> tiles(height, std::vector<TilePtr>(width));

        // reading map tile
         char tile_code = 0;
         for (uint row = 0; row < height; ++row) {
            for (uint column = 0; column < width; ++column) {
                map_file >> tile_code;

                tiles[row][column] = Loader::LoaderManager::game_tile_creator.MakeTile(tile_code);
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
        LOG(INFO) << "Map loaded successfully";
        return Map(tiles);
    }

    std::ostream &operator<<(std::ostream &os, const Map::Iterator &iterator) {
        os << "row_: " << iterator.row_ << " column_: " << iterator.column_;
        return os;
    }
}