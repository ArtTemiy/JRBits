//
// Created by Artemiy Shvedov on 25.08.21.
//

#pragma once

#include <TopDownEngine/interface/interface.hpp>
#include <TopDownEngine/interface/message.hpp>
#include <TopDownEngine/load_manager/loader_maneger.hpp>
#include <TopDownEngine/world/world.hpp>

class MessageInterface : public Engine::Interface::Interface<Engine::World> {
    sf::RenderWindow* window_;
    double time_passed_ = 0;
    double time_to_start = 1;
    bool message_created_ = false;

    void CreateMessages() {
        const double kSpaceWidth = 10.;
        std::vector<int> times = {1, 2, 5, 10};

        assert(kSpaceWidth < 100. / times.size());

        double mess_width = (100 - times.size() * kSpaceWidth) / times.size();
        auto& background_texture = *Engine::Loader::LoaderManager::interface_loader.GetData().at("message_bg");
        for (int i = 0; i < times.size(); ++i) {
            Engine::Interface::Message message(Engine::Object(
                    {5, kSpaceWidth / 2 + i * (mess_width + kSpaceWidth)}, {10, mess_width}));
            message.SetSprite(sf::Sprite(background_texture), *window_);
            message.SetExpireTime(times[i]);
            messages_.insert({ "message" + std::to_string(i), message });
        }
        message_created_ = true;
    }

public:

    void Init(sf::RenderWindow& window) override {
        window_ = &window;
        CreateMessages();
    }
    void Tick(double time_delta) override {
        Interface::Tick(time_delta);
    }
};