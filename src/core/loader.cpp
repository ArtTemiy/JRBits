//
// Created by Artemiy Shvedov on 18.04.21.
//

#include <TopDownEngine/core/loader.hpp>

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

namespace Engine {

    bool TextureLoader::LoadData() {
        if (data_loaded_) {
            return true;
        }
        data_ = {};
        if (path_prefix_.back() != '/') {
            path_prefix_ += '/';
        }
        for (auto& file_name : files_list_) {
            std::shared_ptr<sf::Texture> texture(new sf::Texture());
            if (!texture->loadFromFile(path_prefix_ + file_name + ".png")) {
                LOG(WARNING) << "Wasn't able to load texture: " << file_name;
                return false;
            }
            data_[file_name] = texture;
        }
        LOG(INFO) << "`" << caption_ << "`" << " Texture loader: textures loaded successfully";
        data_loaded_ = true;
        return true;
    }
}