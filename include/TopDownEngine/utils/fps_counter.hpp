//
// Created by Artemiy Shvedov on 04.04.21.
//

#pragma once

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/utils/display_logger.hpp>

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

namespace Engine::Utils {
    /// Prints FPS count on the DisplayLog
    class FPSCounter {
        static bool display;

    public:
        /// Initialise counter
        static void Init(bool new_display = false) {
            display = new_display;
        }

        /// Write fps to log
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
