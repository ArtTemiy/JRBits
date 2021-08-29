//
// Created by Artemiy Shvedov on 05.08.21.
//

#include <TopDownEngine/drawable/drawable_screen.hpp>
#include <TopDownEngine/drawable/drawable_utils.hpp>

namespace Engine::Drawable::Screen {
    void Drawable::Draw(sf::RenderWindow& window) {
        sprite_.setPosition(ToSFVector2f(
                ToVector(window.getSize()) * GetCoordinates() /  100 + GetViewOffset(window)));
        window.draw(sprite_);
    }

    void Drawable::SetSize(const Size& size, sf::RenderWindow& window) {
        SetSpriteSize(sprite_, ToVector(window.getSize()) * GetSize() /  100);
    }

    void Drawable::SetSpritePosition() {
    }
}