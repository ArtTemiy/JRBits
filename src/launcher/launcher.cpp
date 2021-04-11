//
// Created by Artemiy Shvedov on 11.04.21.
//

#include <TopDownEngine/launcher/launcher.hpp>
#include <TopDownEngine/utils/fps_counter.h>

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

namespace Engine::Launcher {
    World& Launcher::Init(const Engine::Launcher::LauncherConfig &config) {
        // config
        LOG(INFO) << "Congig loading...";
        config_ = config;

        // loading resources
        LOG(INFO) << "Loading data";
        Engine::GameTilesTextureLoader::LoadData();

        // Init Game
        LOG(INFO) << "Initializing game...";
        Engine::Map map = Engine::Map::LoadMapFromFile("rsrc/maps/river_small.map");
        world_.SetMap(map);

        LOG(INFO) << "ok";

        return world_;
    }

    int Launcher::Run() {
        const uint kFPS = config_.kFPS;
        const uint kMsPF = 1000 / kFPS;

        // init window
        LOG(INFO) << "Creating window...";
        window_.create(sf::VideoMode(config_.window_width, config_.window_height), "Game.");

        std::shared_ptr<Engine::Drawable::Camera> camera(new Engine::Drawable::Camera(window_));
        world_.SetCamera(camera);

        LOG(INFO) << "Additional utilities initialization...";
        sf::Clock clock;
        Engine::Utils::FPSCounter fps_counter(window_, true);
        LOG(INFO) << "ok";

        LOG(INFO) << "";
        LOG(INFO) << "Running...";

        while (window_.isOpen()) {
            clock.restart();

            // Event process
            sf::Event event{};
            while (window_.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window_.close();
                    continue;
                }
            }

            world_.Tick(kMsPF);

            // Drawing
            window_.clear();
            world_.Draw();
            fps_counter.ShowFps(clock.getElapsedTime());
            window_.display();

            // Frame
            sf::sleep(std::max(sf::Time::Zero, sf::milliseconds(kMsPF) - clock.getElapsedTime()));
        }
        return 0;
    }
}
