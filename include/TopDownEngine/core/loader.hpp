//
// Created by Artemiy Shvedov on 11.04.21.
//

#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <utility>

namespace Engine {

    template <class DataType>
    class Loader {
    protected:
        std::unordered_map<std::string, DataType> data_;
        bool data_loaded_;

    public:
        virtual bool LoadData() = 0;

        bool DataLoaded() const {
            return data_loaded_;
        }

        const auto& GetData() {
            if (!data_loaded_ && !LoadData()) {
                throw std::runtime_error("Tried to get data that wasn\'t loaded before "
                                         "and wasn\'t able to load now.");
            }
            return data_;
        }
    };

    class TextureLoader : public Loader<std::shared_ptr<sf::Texture>> {
        std::string path_prefix_;
        std::vector<std::string> files_list_;

        std::string caption_;

    public:
        TextureLoader(std::string path_prefix, std::vector<std::string> files_list, std::string caption)
        : path_prefix_(std::move(path_prefix)),
          files_list_(std::move(files_list)),
          caption_(std::move(caption)) {}

        bool LoadData() override;
    };
}
