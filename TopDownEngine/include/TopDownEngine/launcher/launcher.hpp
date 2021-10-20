//
// Created by Artemiy Shvedov on 08.06.21.
//

#pragma once

#include "level.hpp"
#include "launcher_config.hpp"

#include <SFML/Window.hpp>

namespace Engine::Launcher {
    class Launcher {
        bool is_initialized_ = false;

        sf::RenderWindow window_;
        LauncherConfig config_;

    public:
        Launcher();

        virtual void Init(const LauncherConfig& config);

        sf::RenderWindow& GetWindow() { return window_; };
        int RunLevel(Level::Level& level);
    };
}