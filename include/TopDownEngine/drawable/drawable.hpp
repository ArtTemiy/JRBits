//
// Created by ArtTemiy on 28.02.2021.
//

#pragma once

#include <TopDownEngine/core.hpp>
#include <SFML/Graphics.hpp>

namespace Engine {
    class Camera : Object {
        sf::RenderWindow& window_;

    public:
        Camera(Coordinates coordinates, sf::RenderWindow &window)
        : Object(coordinates, {0, 0}),
          window_(window) {}

        void DrawSprite(sf::Sprite sprite, const Coordinates& coordinates);
    };

    class Drawable {
        virtual void Draw(const Coordinates& coordinates, const Camera& camera) = 0;
    };

    class FlipBook : public Tickable, Drawable {
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

        void Reset();

        void Tick(double time_delta) override;

        void Draw(const Engine::Coordinates &coordinates, const Engine::Camera &camera) override;
    };
}
