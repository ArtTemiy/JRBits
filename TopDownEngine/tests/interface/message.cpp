//
// Created by Artemiy Shvedov on 25.08.21.
//

#include <glog/logging.h>

#include <TopDownEngine/launcher/launcher.hpp>
#include "message_interface.hpp"

int main() {
    Engine::Launcher::LauncherConfig game_config;
    Engine::Launcher::Launcher launcher;

    Engine::Level::LevelConfig level_config;
    level_config.rsrc.map_source = "rsrc/maps/3types_tiles.map";

    Engine::Level::Level level;
    auto& world = level.CreateWorld(level_config);
    level.SetInterface(std::make_shared<MessageInterface>());

    launcher.Init(game_config);

    auto return_code = launcher.RunLevel(level);

    return return_code;
}