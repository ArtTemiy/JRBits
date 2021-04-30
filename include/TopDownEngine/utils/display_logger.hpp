//
// Created by Artemiy Shvedov on 24.04.21.
//

#pragma once
#include <TopDownEngine/core/core.hpp>

#include <SFML/Graphics/Text.hpp>

#include <sstream>

namespace Engine::Utils {

    /// !Singleton!
    /// Class "prints" text to the screen
    /// Can be used to see some informaion that should be displayed/updated
    /// every frame. Log draws last, so it is always seen.
    class DisplayLoger {
        /// stream with the content
        static std::stringstream content_;

        /// if log should be displayed
        static bool display_;

        /// loaded font
        static sf::Font font_;

        /// window to print log
        static sf::RenderWindow* window_;

    public:
        /// Initialize logger
        /// @param display If text should be printed
        /// @param window window to print the text on
        static void Init(sf::RenderWindow* window, bool display = false) {
            window_ = window;
            display_ = display;
            if (!font_.loadFromFile("rsrc/fonts/NexusFPS.otf")) {
                LOG(ERROR) << "Wasn't able to load font";
            }
        }

        static void Show() {
            if (display_) {
                sf::Text text;
                text.setFont(font_);
                text.setString(content_.str());
                text.setPosition(window_->getView().getCenter().x - window_->getView().getSize().x / 2,
                                  window_->getView().getCenter().y - window_->getView().getSize().y / 2);
                window_->draw(text);
            }
            content_.str("");
        }

        static auto& GetStream() {
            return content_;
        }
    };

    std::stringstream DisplayLoger::content_{};
    bool DisplayLoger::display_ = false;
    sf::Font DisplayLoger::font_{};
    sf::RenderWindow* DisplayLoger::window_ = nullptr;
}

#define DSPLOG Engine::Utils::DisplayLoger::GetStream()