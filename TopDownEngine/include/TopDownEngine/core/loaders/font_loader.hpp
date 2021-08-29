//
// Created by Artemiy Shvedov on 05.08.21.
//

#pragma once

#include "loader.hpp"

#include <SFML/Graphics/Font.hpp>
#include <utility>

namespace Engine::Loader {
    class FontLoader : public Loader<sf::Font> {
        std::string config_path_;
    public:
        explicit FontLoader(std::string  config_path_, std::string  caption = "***") : config_path_(std::move(config_path_)),
                                                                                       Loader<sf::Font>(std::move(caption)) {}

        bool LoadData() override;
    };
}