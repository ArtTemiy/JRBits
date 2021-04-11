//
// Created by Artemiy Shvedov on 11.04.21.
//

#include <TopDownEngine/world.hpp>

namespace Engine::Launcher {
    struct LauncherConfig {
        uint kFPS = 60;

        uint window_width = 3000;
        uint window_height = 2000;

        std::string map_source;
        bool fps_counter_show = true;
    };
}
