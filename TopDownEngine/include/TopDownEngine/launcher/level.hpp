//
// Created by Artemiy Shvedov on 11.04.21.
//

#pragma once

#include "level_config.hpp"

#include <TopDownEngine/world.hpp>
#include <TopDownEngine/launcher/launcher_config.hpp>

#include <utility>

namespace Engine::Level {
    struct LevelRunningParams {
        const uint kFPS;
        const double kSPF;

        explicit LevelRunningParams(const uint FPS) : kFPS(FPS), kSPF(1. / static_cast<double>(kFPS)) {}
    };

    /// Creates and launches game according to LaunchConfig and user configured world
    class Level {
        std::string caption_ = "Unknown level";
        bool is_initialized_ = false;

        LevelConfig config_;

        Engine::World world_;
        sf::RenderWindow window_;
        std::shared_ptr<Interface::Interface<Engine::World>> interface_;

    public:
        explicit Level(std::string caption = "") : caption_(std::move(caption)) {}

        /// Initialize world
        /// @param [in] config - level configuration
        /// @return world that can be changed by user
        World& Init(const LevelConfig& config);

        /// Runs the world
        int Run(sf::RenderWindow& window, const LevelRunningParams& level_running_params);
    };
}
