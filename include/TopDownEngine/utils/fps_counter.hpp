//
// Created by Artemiy Shvedov on 04.04.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/utils/display_logger.hpp>

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

namespace Engine::Utils {
    class FPSCounter {
        static bool display;

    public:
        static void Init(bool new_display = false) {
            display = new_display;
        }

        void static WriteFps(const sf::Time& time_passed) {
            if (display) {
                DSPLOG << std::min(
                        1000000 / static_cast<int>(time_passed.asMicroseconds()),
                        999) << std::endl;
            }
        }
    };

    bool FPSCounter::display = false;
}
