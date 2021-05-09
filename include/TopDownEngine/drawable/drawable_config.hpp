//
// Created by Artemiy Shvedov on 30.04.21.
//

#pragma once

#include <cstdint>

namespace Engine::Drawable {

    /// Configuration for drawable objects
    class DrawableConfig {
    public:
        /// converts units to pixels
        static uint32_t pixels_per_unit;
    };
}