//
// Created by Artemiy Shvedov on 24.04.21.
//

#pragma once
#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable_utils.hpp>

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

#include <sstream>

namespace Engine::Utils {

    /// !Singleton!
    /// Class "prints" text to the screen
    /// Can be used to see some informaion that should be displayed/updated
    /// every frame. Log draws last, so it is always seen.
    class DisplayLogger {
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

        /// Show log on the screen
        static void Show();

        static auto& GetStream() {
            return content_;
        }
    };
}

#define DSPLOG Engine::Utils::DisplayLogger::GetStream()