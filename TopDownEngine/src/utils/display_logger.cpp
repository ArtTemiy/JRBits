//
// Created by Artemiy Shvedov on 05.05.21.
//

#include <TopDownEngine/utils/display_logger.hpp>
#include <TopDownEngine/drawable/drawable_utils.hpp>

namespace Engine::Utils {
    std::stringstream DisplayLogger::content_{};
    bool DisplayLogger::display_ = false;
    sf::Font DisplayLogger::font_{};
    sf::RenderWindow* DisplayLogger::window_ = nullptr;

    void DisplayLogger::Show() {
        if (display_) {
            sf::Text text;
            text.setFont(font_);
            text.setString(content_.str());
//                text.setPosition(window_->getView().getCenter().x - window_->getView().getSize().x / 2,
//                                  window_->getView().getCenter().y - window_->getView().getSize().y / 2);
            text.setPosition(ToSFVector2f(Engine::Drawable::GetViewOffset(*window_)));
            window_->draw(text);
        }
        content_.str("");
    }
}