//
// Created by Artemiy Shvedov on 11.04.21.
//

#pragma once

#include "level_config.hpp"

#include <TopDownEngine/world/world.hpp>
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
        using WorldInterfacePtr = std::shared_ptr<Interface::Interface<Engine::World>>;

        std::string caption_ = "Unknown level";
        bool is_initialized_ = false;

        LevelConfig config_;

        Engine::World world_;
        WorldInterfacePtr interface_;

    public:
        explicit Level(std::string caption = "") : caption_(std::move(caption)) {}

        /// Initialize world
        /// @param [in] config - level configuration
        /// @return world that can be changed by user
        World& CreateWorld(const LevelConfig& config);

        void SetInterface(const WorldInterfacePtr & interface) { interface_ = interface; }

        void CheckCorrectness();

        /// Runs the world
        int Run(sf::RenderWindow& window, const LevelRunningParams& level_running_params);
    };
}
