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
        std::string directory_path_;

        std::string caption_;

    public:
        explicit TextureLoader(std::string directory_path, std::string caption = "***")
        : directory_path_(std::move(directory_path)), caption_(std::move(caption)) {
            if (directory_path_.back() != '/') {
                directory_path_ += '/';
            }
        }

        bool LoadData() override;
    };
}
