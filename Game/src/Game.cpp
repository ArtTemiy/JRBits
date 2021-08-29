//
// Created by Artemiy Shvedov on 09.05.21.
//

#include <TopDownEngine/launcher/launcher.hpp>
#include <TopDownEngine/controller/null_controller.hpp>
#include <camera/camera_target_controller.hpp>
#include <TopDownEngine/controller/null_controller.hpp>
#include <TopDownEngine/load_manager/loader_maneger.hpp>


int main() {
    Engine::Launcher::LauncherConfig game_config;
    Engine::Launcher::Launcher launcher;

    Engine::Level::LevelConfig level_config;
    level_config.rsrc.map_source = "rsrc/maps/default.map";

    Engine::Level::Level level("Main level");
    auto& world = level.CreateWorld(level_config);

    auto player = std::make_shared<Engine::Actor>(
            Engine::DynamicObject(
                    Engine::Object({5, 5}, {1, 1}),
                    10, Engine::DynamicObject::kDynamic));
    player->SetDrawable(
            std::make_shared<Engine::Drawable::DrawableStatic>(
                    *Engine::Loader::LoaderManager::actor_textures_loader.GetData().at("circle")));
    player->SetController(std::make_shared<Engine::Controller::PlayerController>());

    auto camera_controller = std::make_shared<Controllers::CameraTargetController>();
    camera_controller->SetTarget(player);
    auto camera = std::make_shared<Engine::Drawable::Camera>();
    camera->SetController(camera_controller);
    camera->SetCoordinates({500, 500});

//    auto obj1 = std::make_shared<Engine::Actor>(
//            Engine::DynamicObject(
//                    Engine::Object({1.5, 2}, {2, 2}),
//                    10, Engine::DynamicObject::kStatic));
//    obj1->SetDrawable(
//            std::make_shared<Engine::Drawable::DrawableStatic>(
//                    *Engine::Loader::LoaderManager::actor_textures_loader.GetData().at("circle")));
    world.AddActor(player);
//    world.AddActor(obj1);

    world.SetCamera(camera);

    launcher.Init(game_config);

    auto return_code = launcher.RunLevel(level);

    return return_code;
}