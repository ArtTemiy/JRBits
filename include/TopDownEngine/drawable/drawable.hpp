//
// Created by ArtTemiy on 28.02.2021.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include "camera.hpp"

#include <SFML/Graphics.hpp>

#include <utility>

namespace Engine::Drawable {
    /// Interface for object that can be displayed on the screen
    class IDrawable {
    public:
        /// Draw object on the screen using camera
        /// @param [in] camera - camera that will draw the object
        virtual void Draw(ICamera& camera) = 0;
    };

    using IDrawablePtr = std::shared_ptr<IDrawable>;

    /// Drawable component - component that owns resources
    /// and can edit them
    class IDrawableComponent : public IDrawable {
    public:
        virtual void SetSize(const Size& size) = 0;

        virtual void SetPosition(const Coordinates &coordinates) = 0;
    };

    using IDrawableComponentPtr = std::shared_ptr<IDrawableComponent>;

    class DrawableStatic : public IDrawableComponent {
        sf::Sprite sprite_;
    public:
        DrawableStatic() = default;

        explicit DrawableStatic(const sf::Texture& texture) {
            LoadSprite(texture);
        }

        void LoadSprite(const sf::Texture& texture) {
            sprite_.setTexture(texture);
        }

        void SetSprite(sf::Sprite sprite) {
            sprite_ = std::move(sprite);
        }

        auto& GetSprite() {
            return sprite_;
        }

        void Draw(ICamera& camera) override;

        void SetSize(const Size& size) override;

        void SetPosition(const Coordinates &coordinates) override;
    };

    class FlipBook : public Tickable, IDrawableComponent {
        std::vector<sf::Sprite> sprites_;
        std::vector<double> times_;
        double time_left_;
        size_t current_sprite_;

    public:
        FlipBook(std::vector<sf::Sprite> sprites, std::vector<double> times)
        : sprites_(std::move(sprites)),
          times_(std::move(times)),
          time_left_(0),
          current_sprite_(0) {
            if (sprites.size() != times.size()) {
                throw  std::length_error("Size and sprites lengths arn\'t equal");
            }
        }

        const sf::Sprite& GetSprite() const;

        /// Set flipbook to initial state
        void Reset();

        void Tick(double time_delta) override;

        void Draw(ICamera& camera) override;

        void SetSize(const Size& size) override;

        void SetPosition(const Coordinates &coordinates) override;
    };
}
