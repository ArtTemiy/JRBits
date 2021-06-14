//
// Created by Artemiy Shvedov on 14.06.21.
//

#include <TopDownEngine/interface/interface.hpp>

namespace Engine::Interface {
    void Engine::Interface::InterfaceButton::Draw(sf::RenderWindow& window) {
        window.draw(GetDrawable()->GetSprite());
    }
} // namespace Engine::Interface