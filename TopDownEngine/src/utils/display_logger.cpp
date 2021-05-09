//
// Created by Artemiy Shvedov on 05.05.21.
//

#include <TopDownEngine/utils/display_logger.hpp>

namespace Engine::Utils {
    std::stringstream DisplayLogger::content_{};
    bool DisplayLogger::display_ = false;
    sf::Font DisplayLogger::font_{};
    sf::RenderWindow* DisplayLogger::window_ = nullptr;
}