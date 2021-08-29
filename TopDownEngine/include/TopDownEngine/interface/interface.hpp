//
// Created by Artemiy Shvedov on 09.05.21.
//

#pragma once

#include "button.hpp"
#include "message.hpp"

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>

#include <unordered_map>
#include <unordered_set>

#include <SFML/Window/Mouse.hpp>

namespace Engine::Interface {

template <class CallerClass = void>
class Interface : public Drawable::IDrawable {
    sf::View view_;
protected:
    std::unordered_map<std::string, InterfaceButton> buttons_ = {};
    std::unordered_map<std::string, Message> messages_ = {};
    sf::RenderWindow* render_window_;

public:
    // TODO - implement creating from config_path
    explicit Interface(sf::RenderWindow* window = nullptr, const std::string& config_path = "")
    : render_window_(window) {
        if (window) {
            view_ = window->getDefaultView();
        } else {
            view_.reset(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));
        }
    }

    void UpdateView(sf::RenderWindow& render_window) {
//        render_window.setView(view_);
    }

    bool ProcessEvent(sf::Event& event, CallerClass* caller = nullptr) {
        return false;
    };

    void SetRenderWindow(sf::RenderWindow* render_window) {
        render_window_ = render_window;
    }

    void Tick(double time_delta) override {
        for (auto& [name, button] : buttons_) {
            button.Tick(time_delta);
        }
        std::unordered_set<std::string> messages_to_delete;
        for (auto& [name, message] : messages_) {
            message.Tick(time_delta);
            if (message.IsExpired()) {
                messages_to_delete.insert(name);
            }
        }
        for (auto& name : messages_to_delete) {
            messages_.erase(name);
        }
    }

    void Draw(sf::RenderWindow& render_window) {
        UpdateView(render_window);
        /*if (!render_window) {
            Utils::LogAndThrow("`render_window` is nullptr in interface");
        }*/
        for (auto&[name, button] : buttons_) {
            button.Draw(render_window);
        }
        for (auto&[name, message] : messages_) {
            message.Draw(render_window);
        }
    }

    virtual void Init(sf::RenderWindow& window) {}
};
} // namespace Engine::Interface
