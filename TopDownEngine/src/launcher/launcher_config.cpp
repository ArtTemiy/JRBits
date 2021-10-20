//
// Created by Artemiy Shvedov on 09.09.21.
//

#include <TopDownEngine/launcher/launcher_config.hpp>

#include <yaml-cpp/yaml.h>

namespace Engine::Launcher {
    LauncherConfig::LauncherConfig(const std::string& path) {
        auto yaml_config = YAML::LoadFile(path);
        kFPS = yaml_config["fps"].as<uint>();
        window_width = yaml_config["width"].as<uint>();
        window_height = yaml_config["height"].as<uint>();
        display_logger_show = yaml_config["show-logs"].as<bool>();
    }
}
