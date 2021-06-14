//
// Created by Artemiy Shvedov on 02.04.21.
//

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

#include <TopDownEngine/launcher/launcher.hpp>

int main() {
    Engine::Launcher::LauncherConfig game_config;
    Engine::Launcher::Launcher launcher;

    Engine::Level::LevelConfig level_config;
    level_config.map_source = "rsrc/maps/3types_tiles.map";

    Engine::Level::Level level;
    auto& world = level.Init(level_config);

    launcher.Init(game_config);

    auto return_code = launcher.RunLevel(level);

    return return_code;
}