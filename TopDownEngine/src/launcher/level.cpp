//
// Created by Artemiy Shvedov on 11.04.21.
//

#include <TopDownEngine/launcher/level.hpp>

#include <TopDownEngine/launcher/launcher.hpp>
#include <TopDownEngine/utils/fps_counter.hpp>
#include <TopDownEngine/utils/display_logger.hpp>
#include <TopDownEngine/controller/null_controller.hpp>
#include <TopDownEngine/load_manager/loader_maneger.hpp>

#include <SFML/Graphics.hpp>
#include <glog/logging.h>


namespace Engine::Level {
    World& Level::CreateWorld(const LevelConfig &config) {
        config_ = config;

        // loading resources
        LOG(INFO) << "Loading data";
        Loader::LoaderManager::LoadData();

        // Init Game
        LOG(INFO) << "Initializing game...";
        Engine::Map map = Engine::Map::LoadMapFromFile(config_.rsrc.map_source);
        world_.SetMap(map);

        LOG(INFO) << "ok";

        is_initialized_ = true;
        return world_;
    }

    void OkOrThrow(const std::vector<std::pair<bool, const std::string>>& checks) {
        for (auto& [expr, error_message] : checks) {
            if (!expr) {
                throw std::runtime_error(error_message);
            }
        }
    }

    void Level::CheckCorrectness() {
        if (world_.GetCamera() == nullptr) {
            LOG(WARNING) << "No camera was set, so creating simple one";
            world_.SetCamera(std::make_shared<Engine::Drawable::Camera>());
            world_.GetCamera()->SetController(std::make_shared<Engine::Controller::NullController>());
        }
        for (auto& actor : world_.Actors()) {
            actor->CheckCorrectness();
        }
    }

    int Level::Run(sf::RenderWindow& window, const LevelRunningParams& level_running_params) {
        if (!is_initialized_) {
            LOG(ERROR) << "Level \"" <<  caption_ << "\" is uninitialized but was run";
            throw std::runtime_error("Level \"" +  caption_ + "\" is uninitialized but was run");
        }

        CheckCorrectness();
        world_.GetCamera()->LevelInit(&window, ToVector(world_.GetMap().GetSize()) / 2);
        if (interface_) {
            interface_->Init(window);
        }

        sf::Clock clock;
        while (window.isOpen()) {
            clock.restart();

            // Event process
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    continue;
                } else {
                    world_.ProcessEvent(event);
                }
            }

            world_.Tick(level_running_params.kSPF);
            if (interface_) {
                interface_->Tick(level_running_params.kSPF);
            }

            // Drawing
            window.clear();
            world_.Draw();
            if (interface_) {
                interface_->Draw(window);
            }
            Engine::Utils::FPSCounter::WriteFps(clock.getElapsedTime());
            Engine::Utils::DisplayLogger::Show();
            window.display();

            // Frame
            sf::sleep(std::max(sf::Time::Zero,
                               sf::milliseconds(static_cast<int32_t>(level_running_params.kSPF * 1000)) - clock.getElapsedTime()));
        }
        return 0;
    }
}
