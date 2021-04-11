//
// Created by Artemiy Shvedov on 11.04.21.
//

#pragma once

#include <TopDownEngine/world.hpp>
#include <TopDownEngine/launcher/launch_config.hpp>

namespace Engine::Launcher {
    class Launcher {
        LauncherConfig config_;

        Engine::World world_;
        sf::RenderWindow window_;

    public:
        Launcher() = default;

        World& Init(const LauncherConfig& config);

        int Run();
    };
}
