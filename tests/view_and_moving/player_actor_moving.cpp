//
// Created by Artemiy Shvedov on 11.04.21.
//

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

#include <TopDownEngine/launcher/launcher.hpp>
#include <TopDownEngine/controller/player_controller.hpp>

int main() {
    Engine::Launcher::LauncherConfig game_config;
    Engine::Launcher::Launcher launcher;
    game_config.map_source = "rsrc/maps/3types_tiles.map";

    auto& world = launcher.Init(game_config);

    Engine::Actor<Engine::Controller::PlayerController> act(
            Engine::DynamicObject(Engine::Object({0, 0}, {1, 1}), 1)
            );

    auto player = std::make_shared<Engine::Actor<Engine::Controller::PlayerController>>(
            Engine::DynamicObject(
                    Engine::Object({0, 0}, {1, 1}),
                    10));
    player->SetDrawable(
            std::make_shared<Engine::Drawable::DrawableStatic>(
                    *Engine::LoaderManager::actor_textures_loader.GetData().at("circle"))
    );
    world.AddObject(player);

    auto return_code = launcher.Run();

    return return_code;
}