//
// Created by Artemiy Shvedov on 05.08.21.
//

#include <TopDownEngine/core/loaders/texture_loader.hpp>

#include <yaml-cpp/yaml.h>
#include <glog/logging.h>

namespace Engine::Loader {
    bool TextureLoader::LoadData() {
        if (data_loaded_) {
            return true;
        }
        data_ = {};
        auto config = YAML::LoadFile(directory_path_ + "/textures.yaml");
        try {
            for (auto it = config.begin(); it != config.end(); ++it) {
                auto texture_name = it->first.as<std::string>();
                auto texture_file = it->second.as<std::string>();

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