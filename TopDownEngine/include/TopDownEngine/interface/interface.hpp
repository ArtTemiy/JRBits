//
// Created by Artemiy Shvedov on 09.05.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>

#include <unordered_set>

#include <SFML/Window/Mouse.hpp>

namespace Engine::Interface {
    class InterfaceButton : public Object, public Drawable::WithDrawableComponent {
    public:
        explicit InterfaceButton(Object object = Object())
        : Object(object),
          Drawable::WithDrawableComponent(*static_cast<Object*>(this)) {}

        bool MouseHover(sf::RenderWindow& window) {
            auto mouse_position = ToVector(sf::Mouse::getPosition(window)) / ToVector(window.getSize());
            return PointInside(mouse_position);
        }

        void Draw(sf::RenderWindow& window);
    };

    template <class CallerClass = void>
    class Interface : public Drawable::IDrawable {
        std::unordered_map<std::string, InterfaceButton> buttons_ = {};
        sf::RenderWindow& render_window_;

    public:
        explicit Interface(sf::RenderWindow& window, const std::string& config_path = "")
        : render_window_(window) {}

        bool ProcessEvent(sf::Event& event, CallerClass* caller = nullptr) {
            return false;
        };

        void Tick(double time_delta) override {
            for (auto& [name, button] : buttons_) {
                button.Tick(time_delta);
            }
        }

        void Draw(Drawable::ICamera &camera) override {
            for (auto& [name, button] : buttons_) {
                button.Draw(render_window_);
            }
        }
    };
} // namespace Engine::Interface