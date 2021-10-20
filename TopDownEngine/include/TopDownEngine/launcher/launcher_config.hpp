//
// Created by Artemiy Shvedov on 11.04.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <string>

namespace Engine::Launcher {
    /// Configuration for launcher
    struct LauncherConfig {
        /// Frames per second
        uint kFPS = 60;

        /// window settings
        uint window_width = 800;
        uint window_height = 600;

        /// if DisplayLogger should show logs
        bool display_logger_show = true;

        explicit LauncherConfig(const std::string& path);
        LauncherConfig() = default;
    };
}
