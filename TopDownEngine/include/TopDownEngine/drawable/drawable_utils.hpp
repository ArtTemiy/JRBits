//
// Created by Artemiy Shvedov on 25.08.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>

#include <SFML/Graphics.hpp>

namespace Engine::Drawable {
    void SetSpriteSize(sf::Sprite& sprite, const Size& size);
    Vector GetViewOffset(sf::RenderWindow& window);
}
