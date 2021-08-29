//
// Created by Artemiy Shvedov on 11.04.21.
//

#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <utility>

namespace Engine::Loader {

    template <class DataType, class KeyType = std::string>
    class Loader {
    protected:
        std::unordered_map<KeyType, std::shared_ptr<DataType>> data_;
        bool data_loaded_;
        std::string caption_;

    public:
        explicit Loader(std::string  caption = "***") : caption_(std::move(caption)) {}

        virtual bool LoadData() = 0;

        bool DataLoaded() const {
            return data_loaded_;
        }

        const std::unordered_map<KeyType, std::shared_ptr<DataType>>& GetData() {
            if (!data_loaded_ && !LoadData()) {
                throw std::runtime_error("Tried to get data that wasn\'t loaded before "
                                         "and wasn\'t able to load now.");
            }
            return data_;
        }
    };
} // namespace Engine::Loader
