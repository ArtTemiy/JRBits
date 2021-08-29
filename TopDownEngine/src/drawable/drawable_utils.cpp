//
// Created by Artemiy Shvedov on 05.08.21.
//

#include <TopDownEngine/drawable/drawable_utils.hpp>

namespace Engine::Drawable {
    void SetSpriteSize(sf::Sprite& sprite, const Size& size) {
        if (sprite.getTexture()) {
            sprite.setScale(
                    static_cast<float>(size[1]) / static_cast<float>(sprite.getTexture()->getSize().x),
                    static_cast<float>(size[0]) / static_cast<float>(sprite.getTexture()->getSize().y)
            );
        }
    }

    Vector GetViewOffset(sf::RenderWindow& window) {
        return ToVector(window.getView().getCenter()) - ToVector(window.getView().getSize()) / 2;
    }
}
