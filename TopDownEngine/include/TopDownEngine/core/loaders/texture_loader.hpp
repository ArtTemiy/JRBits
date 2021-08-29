//
// Created by Artemiy Shvedov on 05.08.21.
//

#pragma once

#include "loader.hpp"

#include <SFML/Graphics.hpp>

namespace Engine::Loader {
    class TextureLoader : public Loader<sf::Texture> {
        std::string directory_path_;

    public:
        explicit TextureLoader(std::string directory_path, std::string caption = "***")
                : directory_path_(std::move(directory_path)), Loader(std::move(caption)) {
            if (directory_path_.back() != '/') {
                directory_path_ += '/';
            }
        }

        bool LoadData() override;
    };
}