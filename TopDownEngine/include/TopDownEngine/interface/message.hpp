//
// Created by Artemiy Shvedov on 03.08.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable_screen.hpp>

#include <SFML/System/Time.hpp>

namespace Engine::Interface {

class Message : public Drawable::Screen::Drawable {
    std::string message_;
    std::string font_key_;

    sf::Text text_;

    sf::Time expire_time_;
    sf::Clock clock_;

public:
    explicit Message(const Object& object) : Drawable(object) {
        expire_time_ = sf::seconds(0);
        SetFont();
    }

    sf::Text& GetText() { return text_; }

    void Draw(sf::RenderWindow &window) override;
    void SetFont(const std::string& key = "");
    void SetMessage(const std::string& message) { message_ = message; }
    void SetExpireTime(float seconds) {
        expire_time_ = sf::seconds(seconds);
        clock_.restart();
    }
    bool IsExpired() const {
        return clock_.getElapsedTime() > expire_time_;
    }

    void StartClock() { clock_.restart(); }

    void Tick(double delta) override;
};

} // namespace Engine::Interface