//
// Created by Artemiy Shvedov on 03.08.21.
//

#include <TopDownEngine/interface/message.hpp>
#include <TopDownEngine/load_manager/loader_maneger.hpp>
#include <TopDownEngine/drawable/drawable_utils.hpp>

#include <TopDownEngine/utils/display_logger.hpp>

namespace Engine::Interface {

    void Message::Draw(sf::RenderWindow& window) {
        ::Engine::Drawable::Screen::Drawable::Draw(window);
        auto& fonts_data = Loader::LoaderManager::font_loader.GetData();
        auto font = fonts_data.begin();
        text_.setString(message_);
        text_.setFont(*font->second);
        text_.setPosition(ToSFVector2f(
                ToVector(window.getSize()) * GetCoordinates() /  100 + Engine::Drawable::GetViewOffset(window)
                + VOnes * 5));

        window.draw(text_);
    }

    void Message::Tick(double delta) {
        Tickable::Tick(delta);
    }

    void Message::SetFont(const std::string& key) {
        auto& fonts_data = Loader::LoaderManager::font_loader.GetData();
        auto& font = *(font_key_.empty() ? fonts_data.begin()->second : fonts_data.at(font_key_));

        text_.setFont(font);
    }
}