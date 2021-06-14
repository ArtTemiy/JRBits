//
// Created by Artemiy Shvedov on 11.04.21.
//

#pragma once

namespace Engine::Launcher {
    /// Configuration for launcher
    struct LauncherConfig {
        /// Frames per second
        uint kFPS = 60;

        /// window settings
        uint window_width = 3000;
        uint window_height = 2000;

        /// if DisplayLogger should show logs
        bool display_logger_show = true;
    };
}
