//
// Created by Artemiy Shvedov on 11.04.21.
//

#include <glog/logging.h>

#include <TopDownEngine/launcher/launcher.hpp>
#include <TopDownEngine/controller/player_controller.hpp>

int main() {
    Engine::Launcher::LauncherConfig game_config;
    Engine::Launcher::Launcher launcher;

    Engine::Level::LevelConfig level_config;
    level_config.map_source = "rsrc/maps/3types_tiles.map";

    Engine::Level::Level level;
    auto& world = level.Init(level_config);

    auto player = std::make_shared<Engine::Actor<Engine::Controller::PlayerController>>(
            Engine::DynamicObject(
                    Engine::Object({0, 0}, {1, 1}),
                    10));
    player->SetDrawable(
            std::make_shared<Engine::Drawable::DrawableStatic>(
                    *Engine::LoaderManager::actor_textures_loader.GetData().at("circle"))
    );
    world.AddObject(player);

    launcher.Init(game_config);

    auto return_code = launcher.RunLevel(level);

    return return_code;
}