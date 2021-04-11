//
// Created by ArtTemiy on 28.02.2021.
//

#include <TopDownEngine/drawable/drawable.hpp>
#include <TopDownEngine/physics/vector.hpp>

namespace Engine::Drawable {
    void SetSpriteSize(sf::Sprite& sprite, uint height, uint width) {
        sprite.setScale(
                static_cast<float>(width) / sprite.getTexture()->getSize().x,
                static_cast<float>(height) / sprite.getTexture()->getSize().y
        );
    }

    void Camera::DrawSprite(sf::Sprite& sprite, const Coordinates& coordinates) {
        sprite.setPosition(coordinates[1], coordinates[0]);
        window_.draw(sprite);
    }

    void FlipBook::Draw(const Engine::Coordinates &coordinates, Camera &camera) {
        camera.DrawSprite(sprites_[current_sprite_], coordinates);
    }

    void DrawableStatic::Draw(const Coordinates &coordinates, Camera& camera) {
        camera.DrawSprite(sprite_, coordinates);
    }

    void DrawableStatic::SetSize(uint height, uint width) {
        SetSpriteSize(sprite_, height, width);
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

    void FlipBook::SetSize(uint height, uint width) {
        for (auto& sprite : sprites_) {
            SetSpriteSize(sprite, height, width);
        }
    }
}

