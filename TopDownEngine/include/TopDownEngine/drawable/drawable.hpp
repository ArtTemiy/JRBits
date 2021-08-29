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
    class IDrawable : public Tickable {
    public:
        /// Draw object on the screen using camera
        /// @param [in] camera - camera that will draw the object
        virtual void Draw(Camera& camera) {};
    };

    using IDrawablePtr = std::shared_ptr<IDrawable>;

    /// Drawable component - component that owns resources
    /// and can edit them
    class IDrawableComponent : public IDrawable {
    public:
        virtual void SetSize(const Size& size) = 0;

        virtual void SetPosition(const Coordinates &coordinates) = 0;

        /// Returns sprite that should be drawn at the moment
        /// @returns sprite to draw
        virtual const sf::Sprite& GetSprite() const = 0;
    };

    using IDrawableComponentPtr = std::shared_ptr<IDrawableComponent>;

    class WithDrawableComponent : IDrawable {
        Drawable::IDrawableComponentPtr drawable_ = nullptr;
        Object& object_;

    public:
        explicit WithDrawableComponent(Object &object) : object_(object) {}

        auto& GetDrawable() {
            return drawable_;
        }

        void SetDrawable(const Drawable::IDrawableComponentPtr &drawable) {
            drawable_ = drawable;
            drawable_->SetSize(object_.GetSize());
        }

        void Draw(Drawable::Camera& camera) override {
            if (!drawable_) {
                // throw std::runtime_error("No drawable component");
                return;
            }
            drawable_->SetPosition(object_.GetCoordinates());
            drawable_->Draw(camera);
        }

        void Tick(double time_delta) override {
            if (drawable_) {
                drawable_->Tick(time_delta);
            }
        }
    };

    /// Static drawable component
    /// has only one sprite that always displays
    class DrawableStatic : public IDrawableComponent {
        sf::Sprite sprite_;
    public:
        DrawableStatic() = default;

        explicit DrawableStatic(const sf::Texture& texture) : sprite_() {
            LoadTexture(texture);
        }

        void LoadTexture(const sf::Texture& texture) {
            sprite_.setTexture(texture);
        }

        void SetSprite(sf::Sprite sprite) {
            sprite_ = std::move(sprite);
        }

        const sf::Sprite& GetSprite() const override {
            return sprite_;
        }

        void Draw(Camera& camera) override;

        void SetSize(const Size& size) override;

        void SetPosition(const Coordinates &coordinates) override;

        void Tick(double time_delta) override {}
    };

    /// Set of sprites and times
    /// Sprite is shown for corresponding time and then changed for the next one
    /// Sprites are displayed in the loop
    class FlipBook : public IDrawableComponent {
        /// Ordered sprites
        std::vector<sf::Sprite> sprites_;

        /// Corresponding times
        std::vector<double> times_;

        /// time left from last sprite change
        double time_left_;

        /// index of current sprite
        size_t current_sprite_;

    public:
        FlipBook(std::vector<sf::Sprite> sprites, std::vector<double> times)
        : sprites_(std::move(sprites)),
          times_(std::move(times)),
          time_left_(0),
          current_sprite_(0) {
            assert(sprites.size() == times.size());
        }

        const sf::Sprite& GetSprite() const override;

        /// Set flipbook to initial state
        void Reset();

        void Tick(double time_delta) override;

        void Draw(Camera& camera) override;

        void SetSize(const Size& size) override;

        void SetPosition(const Coordinates &coordinates) override;
    };
}
