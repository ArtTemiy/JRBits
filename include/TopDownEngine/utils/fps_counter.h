//
// Created by Artemiy Shvedov on 04.04.21.
//

#pragma once

#include <TopDownEngine/core.hpp>

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

namespace Engine::Utils {
    class FPSCounter {
        bool display_;
        sf::Font font_;
        sf::Text text_;
        sf::RenderWindow& window_;

    public:
        FPSCounter(sf::RenderWindow& window, bool display = false) : window_(window), display_(display) {
            if (!font_.loadFromFile("rsrc/fonts/NexusFPS.otf")) {
                LOG(ERROR) << "Wasn't able to load font";
            }
            text_.setFont(font_);
        }

        void ShowFps(const sf::Time& time_passed) {
            if (display_) {
                text_.setString(std::to_string(std::min(
                        1000000 / static_cast<int>(time_passed.asMicroseconds()),
                        999)));
                text_.setPosition(window_.getView().getCenter().x - window_.getView().getSize().x / 2,
                                  window_.getView().getCenter().y - window_.getView().getSize().y / 2);
                window_.draw(text_);
            }
        }
    };
}
