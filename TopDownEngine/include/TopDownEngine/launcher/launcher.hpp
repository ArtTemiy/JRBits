//
// Created by Artemiy Shvedov on 11.04.21.
//

#pragma once

#include <TopDownEngine/world.hpp>
#include <TopDownEngine/launcher/launch_config.hpp>

namespace Engine::Launcher {

    /// Creates and launches game according to LaunchConfig and user configured world
    class Launcher {
        LauncherConfig config_;

        Engine::World world_;
        sf::RenderWindow window_;

    public:
        Launcher() = default;

        /// Initialize world
        /// @param [in] config - general configuration
        /// @return world that can be changed by user
        World& Init(const LauncherConfig& config);

        /// Runs the world
        int Run();
    };
}
