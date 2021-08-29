//
// Created by Artemiy Shvedov on 11.04.21.
//

#include <glog/logging.h>

#include <TopDownEngine/launcher/launcher.hpp>
#include <TopDownEngine/controller/player_controller.hpp>
#include <TopDownEngine/load_manager/loader_maneger.hpp>

int main() {
    Engine::Launcher::LauncherConfig game_config;
    Engine::Launcher::Launcher launcher;

    Engine::Level::LevelConfig level_config;
    level_config.rsrc.map_source = "rsrc/maps/3types_tiles.map";

    Engine::Level::Level level;
    auto& world = level.CreateWorld(level_config);

    auto player = std::make_shared<Engine::Actor>(
            Engine::DynamicObject(
                    Engine::Object({1, 2}, {1, 1}),
                    10));
    player->SetController(std::make_shared<Engine::Controller::PlayerController>());

    player->SetDrawable(
            std::make_shared<Engine::Drawable::DrawableStatic>(
                    *Engine::Loader::LoaderManager::actor_textures_loader.GetData().at("circle"))
    );
    world.AddActor(player);

    launcher.Init(game_config);

    auto return_code = launcher.RunLevel(level);

    return return_code;
}