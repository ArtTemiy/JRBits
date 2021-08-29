//
// Created by Artemiy Shvedov on 30.04.21.
//

#include <TopDownEngine/drawable/camera.hpp>
#include <TopDownEngine/drawable/drawable_config.hpp>

namespace Engine::Drawable {
    void Camera::DrawSprite(sf::Sprite& sprite) {
        window_->draw(sprite);
    }

    void Camera::LevelInit(sf::RenderWindow* window, const Coordinates &coordinates) {
        SetCoordinates(coordinates);
        window_ = window;
        view_.setCenter({0, 0});
        view_.setSize(sf::Vector2f(window_->getSize().x, window_->getSize().y));
        UpdateView();
    }

    void Camera::UpdateView() {
        view_.setCenter(ToSFVector2f(Object::GetCoordinates() * DrawableConfig::pixels_per_unit));
        window_->setView(view_);
    }
}