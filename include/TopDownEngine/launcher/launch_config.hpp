//
// Created by Artemiy Shvedov on 11.04.21.
//

#include <TopDownEngine/world.hpp>

namespace Engine::Launcher {
    /// Configuration for launcher
    struct LauncherConfig {
        /// Frames per second
        uint kFPS = 60;

        /// window settings
        uint window_width = 3000;
        uint window_height = 2000;

        /// map for loading
        std::string map_source;

        /// if DisplayLogger should show logs
        bool display_logger_show = true;
    };
}
