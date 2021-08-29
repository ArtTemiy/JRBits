//
// Created by ArtTemiy on 28.02.2021.
//

#include <TopDownEngine/drawable/drawable.hpp>
#include <TopDownEngine/drawable/drawable_config.hpp>
#include <TopDownEngine/drawable/drawable_utils.hpp>

namespace Engine::Drawable {
    void SetSpritePosition(sf::Sprite& sprite, const Coordinates& coordinates) {
        sprite.setPosition(coordinates[1] * DrawableConfig::pixels_per_unit, coordinates[0] * DrawableConfig::pixels_per_unit);
    }

    void FlipBook::Draw(Camera &camera) {
        camera.DrawSprite(sprites_[current_sprite_]);
    }

    void DrawableStatic::Draw(Camera& camera) {
        camera.DrawSprite(sprite_);
    }

    void DrawableStatic::SetSize(const Size& size) {
        SetSpriteSize(sprite_, size * DrawableConfig::pixels_per_unit);
    }

    void DrawableStatic::SetPosition(const Coordinates &coordinates) {
        SetSpritePosition(sprite_, coordinates);
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

    void FlipBook::SetSize(const Size& size) {
        for (auto& sprite : sprites_) {
            SetSpriteSize(sprite, size);
        }
    }

    void FlipBook::SetPosition(const Coordinates &coordinates) {
        SetSpritePosition(sprites_[current_sprite_], coordinates);
    }
}

