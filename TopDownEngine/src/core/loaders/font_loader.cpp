//
// Created by Artemiy Shvedov on 05.08.21.
//

#include <TopDownEngine/core/loaders/font_loader.hpp>

#include <glog/logging.h>
#include <yaml-cpp/yaml.h>

namespace Engine::Loader {
    bool FontLoader::LoadData() {
        auto config = YAML::LoadFile(config_path_);
        for (auto it = config.begin(); it != config.end(); ++it) {
            auto name = it->first.as<std::string>();
            auto path = it->second.as<std::string>();
            auto font = std::make_shared<sf::Font>();
            data_[name] = font;
            if (!font->loadFromFile(path)) {
                LOG(ERROR) << "Couldn\'t load font from path " + path;
                return false;
            }
        }
        return true;
    }
}