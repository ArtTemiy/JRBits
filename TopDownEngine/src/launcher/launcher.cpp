//
// Created by Artemiy Shvedov on 08.06.21.
//

#include <TopDownEngine/launcher/launcher.hpp>
#include <TopDownEngine/utils/display_logger.hpp>
#include <TopDownEngine/utils/fps_counter.hpp>

namespace Engine::Launcher {
    void Launcher::Init(const LauncherConfig &config) {
        // config
        LOG(INFO) << "Congig loading...";
        config_ = config;

        // init window
        LOG(INFO) << "Creating window...";
        window_.create(sf::VideoMode(config_.window_width, config_.window_height), "Game.");


        LOG(INFO) << "Additional utilities initialization...";
        Engine::Utils::DisplayLogger::Init(&window_, config_.display_logger_show);
        Engine::Utils::FPSCounter::Init(true);
        LOG(INFO) << "ok";
        LOG(INFO) << "";

        is_initialized_ = true;
    }

    int Launcher::RunLevel(Level::Level &level) {
        if (!is_initialized_) {
            throw std::runtime_error("Launcher wasn\'t initialized");
        }

        Level::LevelRunningParams level_running_params(config_.kFPS);
        LOG(INFO) << "Running...";

        level.Run(window_, level_running_params);

        return 0;
    }
}