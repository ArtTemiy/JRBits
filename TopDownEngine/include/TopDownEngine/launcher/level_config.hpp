//
// Created by Artemiy Shvedov on 08.06.21.
//

#pragma once

#include <TopDownEngine/controller/controller.hpp>
#include <TopDownEngine/controller/null_controller.hpp>
#include <TopDownEngine/drawable/camera.hpp>
#include <TopDownEngine/world/world.hpp>

#include <yaml-cpp/yaml.h>

#include <string>
#include <functional>

namespace Engine::Level {
    class LevelConfig {
    public:
        struct Resources {
            /// map for loading
            std::string map_source;
        } rsrc;
        LevelConfig() = default;
        explicit LevelConfig(const std::string& path);

//        std::function<Drawable::CameraPtr(sf::RenderWindow&, World&)> make_camera = [](sf::RenderWindow& window, World& world) {
//            return std::make_shared<Drawable::Camera<Controller::NullController>>(window, ToVector(world.GetMap().GetSize()) / 2);
//        };
    };

    /*
    class LevelConfigCreatorHelper {
    public:
        template<class ControllerClass>
        static auto GenCameraControllerFunction() {
            return [](sf::RenderWindow& window, World& world) {
                return std::make_shared<Drawable::Camera<ControllerClass>>(window,
                                                                           ToVector(world.GetMap().GetSize()) / 2);
            };
        }
        template<class CameraClass>
        static auto GenCameraFunction() {
            return [](sf::RenderWindow& window, World& world) {
                return std::make_shared<CameraClass>(window, ToVector(world.GetMap().GetSize()) / 2);
            };
        }
    };
    */
}
