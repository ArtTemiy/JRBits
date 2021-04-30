//
// Created by Artemiy Shvedov on 02.04.21.
//

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

#include <TopDownEngine/launcher/launcher.hpp>

int main() {
    Engine::Launcher::LauncherConfig game_config;
    Engine::Launcher::Launcher launcher;
    game_config.map_source = "rsrc/maps/3types_tiles.map";

    auto& world = launcher.Init(game_config);

    auto return_code = launcher.Run();

    return return_code;
}