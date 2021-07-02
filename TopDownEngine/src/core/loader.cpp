//
// Created by Artemiy Shvedov on 18.04.21.
//

#include <TopDownEngine/core/loader.hpp>

#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <glog/logging.h>

namespace Engine {

    bool TextureLoader::LoadData() {
        if (data_loaded_) {
            return true;
        }
        data_ = {};
        auto config = YAML::LoadFile(directory_path_ + "/textures.yaml");
        try {
            for (YAML::const_iterator it = config.begin(); it != config.end(); ++it) {
                const auto texture_name = it->first.as<std::string>();
                const auto texture_file = it->second.as<std::string>();

                auto load_path = directory_path_ + texture_file;

                std::shared_ptr<sf::Texture> texture(new sf::Texture());
                if (!texture->loadFromFile(load_path)) {
                    LOG(WARNING) << "Wasn't able to load texture: " << load_path;
                    return false;
                }
                data_[texture_name] = texture;
            }
            LOG(INFO) << "`" << caption_ << "`" << " Texture loader: textures loaded successfully";
            data_loaded_ = true;
            return true;
        } catch (std::exception& e) {
            LOG(ERROR) << "The exception was occurred while loading textures in `" << caption_ << "` texture loader:" << e.what();
            return false;
        }
    }
}