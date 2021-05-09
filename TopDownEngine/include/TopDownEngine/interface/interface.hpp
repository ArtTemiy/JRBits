//
// Created by Artemiy Shvedov on 09.05.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>

#include <unordered_set>

namespace Engine::Interface {
    template <class ParentObject>
    class InterfaceButton : public Object, public Drawable::WithDrawableComponent {
        ParentObject* parent_object_ = nullptr;

    public:
        InterfaceButton(Object object = Object(), ParentObject* parent_object = nullptr)
        : parent_object_(parent_object),
          Object(object),
          Drawable::WithDrawableComponent(*this) {}

        void SetParent(ParentObject* parent_object) {
            parent_object_ = parent_object;
        }

        bool ProcessEvent() {}
    };

    template <class ParentObject>
    class Interface : public Drawable::IDrawable {
        std::vector<InterfaceButton<ParentObject>> buttons_ = {};
        ParentObject* parent_object_ = nullptr;

    public:
        bool ProcessEvent(sf::Event& event) {};

        void SetParent(ParentObject* parent_object) {
            parent_object_ = parent_object;
        }

        void Tick(double time_delta) override {
            for (InterfaceButton<ParentObject>& button : buttons_) {
                button.Tick(time_delta);
            }
        }

        void Draw(Drawable::ICamera &camera) override {
            for (InterfaceButton<ParentObject>& button : buttons_) {
                button.Draw(camera);
            }
        }
    };
}