//
// Created by ArtTemiy on 28.02.2021.
//

#include <TopDownEngine/drawable/drawable.hpp>

namespace Engine {
    void Camera::DrawSprite(sf::Sprite sprite, const Coordinates& coordinates) {
        sprite.setPosition(coordinates[0], coordinates[1]);
        window_.draw(sprite);
    }

    const sf::Sprite& FlipBook::GetSprite() const {
        return sprites_[current_sprite_];
    }

    void FlipBook::Reset() {
        time_left_ = 0;
        current_sprite_ = 0;
    }

    void FlipBook::Tick(double time_delta) {
        time_left_ += time_delta;
        while (time_left_ >= times_[current_sprite_]) {
            time_left_ -= times_[current_sprite_];
            current_sprite_ = (current_sprite_ + 1) % sprites_.size();
        }
    }

    void FlipBook::Draw(const Engine::Coordinates &coordinates, const Engine::Camera &camera) {

    }
}

