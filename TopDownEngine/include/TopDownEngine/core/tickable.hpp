//
// Created by Artemiy Shvedov on 06.05.21.
//

#pragma once
namespace Engine {
    /// Class with tick function that called every frame
    class Tickable {
    public:
        /// called every frame
        /// @param [in] time_delta - Time passed form precious frame (in seconds)
        virtual void Tick(double time_delta) {};
        virtual ~Tickable() = default;
    };
}