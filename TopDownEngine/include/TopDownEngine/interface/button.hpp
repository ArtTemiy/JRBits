//
// Created by Artemiy Shvedov on 03.08.21.
//

#pragma once

#include <TopDownEngine/drawable/drawable_screen.hpp>
#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>

namespace Engine::Interface {

class InterfaceButton : public Object, public Drawable::WithDrawableComponent {
public:
    explicit InterfaceButton(const Object& object = Object())
            : Object(object),
              WithDrawableComponent(*static_cast<Object*>(this)) {}

    bool MouseHover(sf::RenderWindow& window) {
        auto mouse_position = ToVector(sf::Mouse::getPosition(window)) / ToVector(window.getSize());
        return PointInside(mouse_position);
    }

    // TODO - implement
    void Draw(sf::RenderWindow& window) {}
};

template <class Dependent>
class InterfaceButtonImpl : public InterfaceButton {
    Dependent* object_;

public:
    explicit InterfaceButtonImpl(Object object, Dependent* dependent = nullptr) : InterfaceButton(std::move(object)), object_(dependent) {}

    void SetObject(Dependent* object) { object_ = object; }
};

} // namespace Engine::Interface