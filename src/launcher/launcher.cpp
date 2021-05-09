//
// Created by Artemiy Shvedov on 11.04.21.
//

#include <TopDownEngine/launcher/launcher.hpp>
#include <TopDownEngine/utils/fps_counter.hpp>
#include <TopDownEngine/utils/display_logger.hpp>
#include <TopDownEngine/controller/null_controller.hpp>

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

namespace Engine::Launcher {
    World& Launcher::Init(const Engine::Launcher::LauncherConfig &config) {
        // config
        LOG(INFO) << "Congig loading...";
        config_ = config;

        // loading resources
        LOG(INFO) << "Loading data";
        Engine::LoaderManager::LoadData();

        // Init Game
        LOG(INFO) << "Initializing game...";
        Engine::Map map = Engine::Map::LoadMapFromFile(config.map_source);
        world_.SetMap(map);

        LOG(INFO) << "ok";

        return world_;
    }

    int Launcher::Run() {
        const uint kFPS = config_.kFPS;
        /// seconds per frame
        const double kSPF = 1. / static_cast<double>(kFPS);

        // init window
        LOG(INFO) << "Creating window...";
        window_.create(sf::VideoMode(config_.window_width, config_.window_height), "Game.");

        auto camera = std::make_shared<
                Engine::Drawable::Camera<Engine::Controller::NullController>>(
                        window_, ToVector(world_.GetMap().GetSize()) / 2);
        world_.SetCamera(camera);

        LOG(INFO) << "Additional utilities initialization...";
        sf::Clock clock;
        Engine::Utils::DisplayLogger::Init(&window_, config_.display_logger_show);
        Engine::Utils::FPSCounter::Init(true);
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
                } else {
                    world_.ProcessEvent(event);
                }
            }

            world_.Tick(kSPF);

            // Drawing
            window_.clear();
            world_.Draw();
            Engine::Utils::FPSCounter::WriteFps(clock.getElapsedTime());
            Engine::Utils::DisplayLogger::Show();
            window_.display();

            // Frame
            sf::sleep(std::max(sf::Time::Zero, sf::milliseconds(static_cast<int32_t>(kSPF * 1000)) - clock.getElapsedTime()));
        }
        return 0;
    }
}
