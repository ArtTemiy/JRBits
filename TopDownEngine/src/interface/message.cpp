//
// Created by Artemiy Shvedov on 03.08.21.
//

#include <TopDownEngine/interface/message.hpp>
#include <TopDownEngine/load_manager/loader_maneger.hpp>

#include <TopDownEngine/utils/display_logger.hpp>

namespace Engine::Interface {

    void Message::Draw(sf::RenderWindow& window) {
        ::Engine::Drawable::Screen::Drawable::Draw(window);
        auto& fonts_data = Loader::LoaderManager::font_loader.GetData();
        auto& font = *(font_key_.empty() ? fonts_data.begin()->second : fonts_data.at(font_key_));
        sf::Text text(message_, font);
        text.setPosition(ToSFVector2f(
                         GetCoordinates() / 100 * ToVector(window.getSize())));
        window.draw(text);
    }

    void Message::Tick(double delta) {
        Tickable::Tick(delta);
    }
}