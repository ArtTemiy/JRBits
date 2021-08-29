//
// Created by Artemiy Shvedov on 03.08.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>

#include <SFML/Graphics.hpp>

namespace Engine::Drawable::Screen {
    class Drawable : public Tickable, public Object {
        sf::Sprite sprite_;

    public:
        explicit Drawable(const Object& object) : Object(object) {}

        void SetSprite(const sf::Sprite& sprite) {
            sprite_ = sprite;
        }
        void SetSprite(const sf::Sprite& sprite, sf::RenderWindow& window) {
            sprite_ = sprite;
            SetSize(window);
        }
        virtual void Draw(sf::RenderWindow& window);
        void SetSize(const Size& size, sf::RenderWindow& window);
        void SetSize(sf::RenderWindow& window) {
            SetSize(GetCoordinates(), window);
        }

    private:
        void SetSpritePosition();
    };
} // Engine::Drawable::Screen