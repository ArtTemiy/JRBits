//
// Created by ArtTemiy on 28.02.2021.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <SFML/Graphics.hpp>
#include <utility>

namespace Engine::Drawable {

    /// Camera for world. Only objects that are inside camera borders
    /// will be drawn on the screen
    class Camera : public Tickable {
        /// Game window
        sf::RenderWindow& window_;

        /// View to set
        sf::View view_;

    public:
        explicit Camera(sf::RenderWindow &window)
        : window_(window),
          view_(sf::Vector2f(0, 0), sf::Vector2f(
                  window_.getSize().x, window_.getSize().y)) {
            UpdateView();
        }

        sf::View& GetView() {
            return view_;
        }

        void UpdateView() {
            window_.setView(view_);
        }

        /// Draws sprite in given coordinates
        void DrawSprite(sf::Sprite& sprite, const Coordinates& coordinates);

        void Tick(double time_delta) override {
            UpdateView();
        }
    };

    class IDrawable {
    public:
        // TODO - change signatre to void(Camera& camera)
        virtual void Draw(const Coordinates& coordinates, Camera& camera) = 0;

        virtual void SetSize(uint height, uint width) = 0;
    };

    using IDrawablePtr = std::shared_ptr<IDrawable>;

    class DrawableStatic : public IDrawable {
        sf::Sprite sprite_;
    public:
        DrawableStatic() {}

        DrawableStatic(const sf::Texture& texture) {
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

        void Draw(const Coordinates &coordinates, Camera& camera) override;

        void SetSize(uint height, uint width) override;
    };

    class FlipBook : public Tickable, IDrawable {
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

        void Draw(const Engine::Coordinates &coordinates, Engine::Drawable::Camera& camera) override;

        void SetSize(uint height, uint width) override;
    };
}
