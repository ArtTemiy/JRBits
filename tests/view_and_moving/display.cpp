//
// Created by Artemiy Shvedov on 02.04.21.
//

#include <SFML/Graphics.hpp>
#include <glog/logging.h>
#include <TopDownEngine/world.hpp>
#include <TopDownEngine/utils/fps_counter.h>

int main() {
    // Config
    LOG(INFO) << "Congig loading...";
    const uint kFPS = 60;
    const uint kMsPF = 1000 / kFPS;
    LOG(INFO) << "ok";

    // init window
    LOG(INFO) << "Creating window...";
    int window_width = 2000;
    int window_height = 2000;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Game.");
    LOG(INFO) << "ok";

    // Load resources
    LOG(INFO) << "Loading resources...";
    Engine::GameTilesTextureLoader::LoadData();
    LOG(INFO) << "ok";

    // Init Game
    LOG(INFO) << "Initializing game...";
//    Engine::Map map = Engine::Map::LoadMapFromFile("rsrc/maps/full_small.map");
    Engine::Map map = Engine::Map::LoadMapFromFile("rsrc/maps/river_small.map");
    std::shared_ptr<Engine::Camera> camera(new Engine::Camera(window));
    Engine::World world;
    world.SetCamera(camera);
    world.SetMap(map);
    LOG(INFO) << "ok";

    LOG(INFO) << "Additional utilities initialization...";
    sf::Clock clock;
    Engine::Utils::FPSCounter fps_counter(window, true);
    LOG(INFO) << "ok";

    LOG(INFO) << "";
    LOG(INFO) << "Running...";
    // Game loop
    while (window.isOpen()) {
        clock.restart();

        // Event process
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }

        world.Tick(kMsPF);

        // Drawing
        window.clear();
        world.Draw();
        fps_counter.ShowFps(clock.getElapsedTime());
        window.display();

        // Frame
        sf::sleep(std::max(sf::Time::Zero, sf::milliseconds(kMsPF) - clock.getElapsedTime()));
    }
    return 0;
}