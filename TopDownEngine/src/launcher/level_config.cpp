//
// Created by Artemiy Shvedov on 29.08.21.
//

#include <TopDownEngine/launcher/level_config.hpp>

namespace Engine::Level {
    const std::string kKey_Resources = "resources";
    const std::string kKey_Resources_Map = "map";

    LevelConfig::LevelConfig(const std::string& path) {
        auto yaml_config = YAML::LoadFile(path);
        rsrc.map_source = yaml_config[kKey_Resources][kKey_Resources_Map].as<std::string>();
    }
} // namespace Engine::Level
