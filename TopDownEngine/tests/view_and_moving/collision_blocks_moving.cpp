//
// Created by Artemiy Shvedov on 04.05.21.
//

#include <TopDownEngine/launcher/launcher.hpp>

#include <TopDownEngine/controller/null_controller.hpp>

int main() {
    Engine::Launcher::LauncherConfig game_config;
    Engine::Launcher::Launcher launcher;

    Engine::Level::LevelConfig level_config;
    level_config.map_source = "rsrc/maps/full_big.map";

    Engine::Level::Level level("Test level");
    auto& world = level.CreateWorld(level_config);

    auto player = std::make_shared<Engine::Actor<Engine::Controller::PlayerController>>(
            Engine::DynamicObject(
                    Engine::Object({0, 0}, {1, 1}),
                    10, Engine::DynamicObject::kDynamic));
    player->SetDrawable(
            std::make_shared<Engine::Drawable::DrawableStatic>(
                    *Engine::LoaderManager::actor_textures_loader.GetData().at("circle"))
    );

    auto obj1 = std::make_shared<Engine::Actor<Engine::Controller::NullController>>(
            Engine::DynamicObject(
                    Engine::Object({1.5, 2}, {2, 2}),
                    10, Engine::DynamicObject::kStatic));
    obj1->SetDrawable(
            std::make_shared<Engine::Drawable::DrawableStatic>(
                    *Engine::LoaderManager::actor_textures_loader.GetData().at("circle"))
    );
    world.AddActor(player);
    world.AddActor(obj1);

    launcher.Init(game_config);

    auto return_code = launcher.RunLevel(level);

    return return_code;
}