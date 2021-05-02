//
// Created by Artemiy Shvedov on 30.04.21.
//

#include <TopDownEngine/drawable/camera.hpp>
#include <TopDownEngine/drawable/drawable_config.hpp>

namespace Engine::Drawable {
    void ICamera::DrawSprite(sf::Sprite& sprite) {
        window_.draw(sprite);
    }

    ICamera::ICamera(sf::RenderWindow &window, const Coordinates &coordinates)
            : DynamicObject(coordinates, {0, 0}, 1),
              window_(window),
              view_({0, 0}, sf::Vector2f(
                      window_.getSize().x, window_.getSize().y)) {
        UpdateView();
    }

    void ICamera::UpdateView() {
        view_.setCenter(sf::Vector2f(
                Object::GetCoordinates()[0] * DrawableConfig::pixels_per_unit,
                Object::GetCoordinates()[1] * DrawableConfig::pixels_per_unit));
        window_.setView(view_);
    }
}