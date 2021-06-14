//
// Created by Artemiy Shvedov on 09.05.21.
//

#include <TopDownEngine/launcher/launcher.hpp>
#include <TopDownEngine/controller/null_controller.hpp>

int main() {
    Engine::Launcher::LauncherConfig game_config = {};
    Engine::Launcher::Launcher launcher;
    game_config.map_source = "TopDownEngine/rsrc/maps/full_big.map";

    auto& world = launcher.Init(game_config);

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
    world.AddObject(player);
    world.AddObject(obj1);

    auto return_code = launcher.Run();

    return return_code;
}