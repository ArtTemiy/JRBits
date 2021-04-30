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
    game_config.map_source = "rsrc/maps/full_big.map";

    auto& world = launcher.Init(game_config);
    auto player = std::make_shared<Engine::Actor>(
            Engine::DynamicObject(
                    Engine::Object({2, 2}, {1, 1}),
                    300),
            Engine::Controller::ControllerPtr(new Engine::Controller::PlayerController()));
    player->SetDrawable(
            Engine::Drawable::IDrawablePtr(new Engine::Drawable::DrawableStatic(
                    *Engine::LoaderManager::actor_textures_loader.GetData().at("circle"))
    ));
    world.AddObject(player);

    auto return_code = launcher.Run();

    return return_code;
}